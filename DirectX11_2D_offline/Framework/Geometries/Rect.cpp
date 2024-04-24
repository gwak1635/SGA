#include "Framework.h"
#include "Rect.h"

Rect::Rect(Vector3 position, Vector3 size, float rotation)
    : position(position), size(size), rotation(rotation)
{
    // Vertices
    {
        // vertices ũ�� ���Ҵ�
        vertices.assign(4, VertexColor());

        // �� �ϴ�
        vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
        vertices[0].color = color;

        // �� ���
        vertices[1].position = Vector3(+0.5f, +0.5f, 0.0f);
        vertices[1].color = color;

        // �� �ϴ�
        vertices[2].position = Vector3(+0.5f, -0.5f, 0.0f);
        vertices[2].color = color;

        // �� ���
        vertices[3].position = Vector3(-0.5f, +0.5f, 0.0f);
        vertices[3].color = color;
    }

    // VertexBuffer
    {
        vb = new VertexBuffer();
        vb->Create(vertices, D3D11_USAGE_DYNAMIC);
    }

    // Indices // IndexBuffer
    {
        indices = { 0,1,2,0,3,1 };

        ib = new IndexBuffer();
        ib->Create(indices, D3D11_USAGE_IMMUTABLE);
    }

    // VertexShader
    {
        vs = new VertexShader();

        // ���̴� ��� + ���� �̸� , ������ ���̴� �Լ� �̸�
        vs->Create(ShaderPath + L"VertexColor.hlsl", "VS");
    }

    // PixelShader
    {
        ps = new PixelShader();

        // ���̴� ��� + ���� �̸� , ������ ���̴� �Լ� �̸�
        ps->Create(ShaderPath + L"VertexColor.hlsl", "PS");
    }

    // InputLayout
    {
        il = new InputLayout();

        il->Create(VertexColor::descs, VertexColor::count,
            vs->GetBlob());
    }

    // WorldBuffer
    {
        wb = new WorldBuffer();
    }

    // Collision
    {
        collision = new BoundingBox();
        edge = new RectEdge();

        for (int i = 0; i < 4; i++)
            verticesPosition[i] = vertices[i].position;
    }
}

Rect::~Rect()
{
    SAFE_DELETE(edge);
    SAFE_DELETE(collision);

    SAFE_DELETE(wb);

    SAFE_DELETE(il);

    SAFE_DELETE(ps);
    SAFE_DELETE(vs);

    SAFE_DELETE(ib);
    SAFE_DELETE(vb);
}

void Rect::Update()
{
    // Update�Լ��� �ַ� �� ��ü�� �� �����Ӹ��� �� �ൿ�� ����д�.
    // ���⿡ ���� ����� �� ��ü�� �ݵ�� ������ ����̶� ���̴�.

    UpdateWorld();  // ����� �� ��ü�� ��ġ��Ų��.

}

void Rect::Render()
{
    vb->SetIA();
    ib->SetIA();
    il->SetIA();
    // �ﰢ���� ��� �׸��� ���� �Լ�
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    vs->SetShader();
    wb->SetVSBuffer(0);

    ps->SetShader();

    // �׸��� �׸��� �Լ�
    DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void Rect::GUI()
{
    // ImGui�� �̿��� ����ȯ�濡 ���� UI�� ����� �κ�

    // ImGui�� ����� ���� ���� ���� ����Ǿ��ϴ� �ڵ�
    ImGui::Begin("Rect", &bOpen);
    {
        ImGui::Text(MakeLabel("Rect").c_str());
        ImGui::SliderFloat2(MakeLabel("Pos").c_str(), position,
            0, WinMaxWidth);
        ImGui::SliderFloat2(MakeLabel("Size").c_str(), size,
            0, WinMaxWidth);
        ImGui::SliderAngle(MakeLabel("Rot").c_str(), &rotation,
            0, 360);

        // Gui��ɿ� if�� ������� �ش� Gui�� ���۵����� ������ �Լ���
        // �����ϴ°��� �����ϴ�.
        if (ImGui::ColorPicker3(MakeLabel("Color").c_str(), color))
            UpdateColor();
    }
    // ImGui���� Gui�ڵ尡 �����ٴ°��� �˷��� �Լ�
    ImGui::End(); // �̰� �������� ����
}

void Rect::UpdateColor()
{
    D3D11_MAPPED_SUBRESOURCE subRe;
    DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subRe);
    {
        for (VertexColor& v : vertices)
        {
            v.color = this->color;
        }

        memcpy(subRe.pData, vertices.data(),
            vb->GetCount() * vb->GetStride());
    }
    DC->Unmap(vb->GetResource(), 0);
}

void Rect::SetColor(Color color)
{
    this->color = color;
    UpdateColor();
}

string Rect::MakeLabel(string label)
{
    string Label = label + "##" + to_string((UINT)this);
    return Label;
}

void Rect::UpdateWorld()
{
    // ���� ũ�⸦ ����� ũ��� ��ȯ
    D3DXMatrixScaling(&S, size.x, size.y, size.z);
    // ���� ȸ������ ����� ȸ�������� ��ȯ
    D3DXMatrixRotationZ(&R, rotation);
    // ���� ��ġ�� ����� ��ġ�� ��ȯ
    D3DXMatrixTranslation(&T, position.x, position.y, position.z);

    // SRT ������ �ƴϸ� ���������� ����� �ȵ�
    world = S * R * T;
    wb->SetWorld(world);

    collision->UpdateData(world, verticesPosition);
}

void Rect::Move()
{
    float mSpd = 100.0f;

    if (bJump) Jump();

    if (Keyboard::Get()->Press('W'))
    {
        // rect�� �������� �̵��ǰ�
        position.y += mSpd * Time::Delta();
        if (Keyboard::Get()->Press('S') && moveD == false)
        {
            position.y -= (mSpd * 2) * Time::Delta();
        }
    }
    else if (Keyboard::Get()->Press('S'))
    {
        // rect�� �Ʒ������� �̵��ǰ�
        position.y -= mSpd * Time::Delta();
        moveD = true;
    }

    if (Keyboard::Get()->Up('S')) moveD = false;

    if (Keyboard::Get()->Press('A'))
    {
        // rect�� �������� �̵��ǰ�s
        position.x -= mSpd * Time::Delta();
        if (Keyboard::Get()->Press('D') && !moveR)
        {
            position.x += (mSpd * 2) * Time::Delta();
        }
    }
    else if (Keyboard::Get()->Press('D'))
    {
        // rect�� ���������� �̵��ǰ�
        position.x += mSpd * Time::Delta();
        moveR = true;
    }

    if (Keyboard::Get()->Up('D')) moveR = false;

    if (Keyboard::Get()->Down(VK_SPACE) && !bJump)
    {
        bJump = true;
        jumpStartY = position.y;
    }
}

void Rect::Jump()
{
    /*
    ��� ������ �⺻������ bool���� �̿��� Ư�� Ű�� ������ ���
    �ش� bool���� true�� �ٲٸ� �ش� bool���� true�϶� ���� �̵���
    �����ϴ� ���� �⺻���� �д�.

    ����, ������ �������ִµ��� ������ ���̰� ������ �������� ����� ������
    �����ϰ� �ʹٸ� bool���� ������� �ʾƵ� �ȴ�.

    ������ ����¹� 1. ���� �ð� �̿��ϱ�
    // ������ �ð��� ���� ���� ����
    1. �����̽��ٸ� ��������� ��� ���� �ð� ���� ���� �����Ѵ�.
    (Time::Delta()�� ��� ���ϴٰ� 1�� �Ǹ� 1�ʰ� ������)
    2. ���� �ð��� ������ �ٽ� �����ִ� ������ õõ�� �����´�.
    (�����ö��� �ö� �ð���ŭ �������� �ȴ�.)

    ������ ����¹� 2. �߷� �̿��ϱ�
    // ���Ӱ����� ���� ���� ���� ����
    1. �����̽��ٸ� ��������� Ư�� ����ŭ �̵��� �����ϱ�
    2. Ư�� ���� ó���� +���ٰ� �ð��� �������� ���������� ���� ������
    3. Ư�� ���� ��� �����ϴ� -���� �����Ұ�� �϶��ϱ� ����

    ���� ����¹� 3. Ư�� �Ÿ����� �̵��ϱ�
    // ������ ������ ���� ���� ���� ����
    1. �����̽��ٸ� ��������� ���� �ڽ��� ���̰����� Ư�� ���� ���� �̵�
    2. �ش� ���� ���޽� �ٽ� ó�� ���̰����� �̵�
    */

    // �����
    if (bFall == false)
    {
        // ���� ������ �ð��� �ִ� �ð��� �Ѿ��ٸ�
        if (curJumpT >= maxJumpT) // �ϰ� �غ�
        {
            curJumpT = 0.0f;
            bFall = true;
        }
        else // ���� �����
        {
            curJumpSpd -= 10.0f * Time::Delta();

            position.y += curJumpSpd;

            // Time::Delta�� ������ �ð��� �˷��ֱ� ������
            // ��� �������� 1�� �� ������ 1�ʰ� ���� �����̴�.
            curJumpT += Time::Delta();
        }
    }
    else // �ϰ� ��
    {
        // ���� ������ �ð��� �ִ� �ð��� �Ѿ��ٸ�
        if (curJumpT >= maxJumpT) // ���� ��
        {
            curJumpT = 0.0f;

            curJumpSpd = maxJumpSpd;

            bJump = false;
            bFall = false;

            position.y = jumpStartY;
            jumpStartY = 0;
        }
        else // ���� �ϰ���
        {
            curJumpSpd += 10.0f * Time::Delta();

            position.y -= curJumpSpd;

            curJumpT += Time::Delta();
        }
    }
}
