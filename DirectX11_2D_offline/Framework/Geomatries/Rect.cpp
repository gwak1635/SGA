#include "Framework.h"
#include "Rect.h"

Rect::Rect(Vector3 position, Vector3 size, float rotation)
    : position(position), size(size), rotation(rotation)
{
    // Vertices
    {
        // vector.assign �� ������ ũ�⸦ �缳��
        vertices.assign(4, VertexColor());

        // �� �ϴ�
        vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
        vertices[0].color = Color(1, 0, 0, 1); // R, G, B , A

        // �� ���
        vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
        vertices[1].color = Color(1, 0, 0, 1);

        // �� �ϴ�
        vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
        vertices[2].color = Color(1, 0, 0, 1);

        // �� ���
        vertices[3].position = Vector3(-0.5f, 0.5f, 0.0f);
        vertices[3].color = Color(1, 0, 0, 1);
    }

    // VertexBuffer
    {
        vb = new VertexBuffer();
        vb->Create(vertices, D3D11_USAGE_DYNAMIC);
    }

    // IndexBuffer
    {
        indices = { 0,1,2,0,3,1 };

        ib = new IndexBuffer();
        ib->Create(indices, D3D11_USAGE_IMMUTABLE);
    }   

    // VertexShader
    {
        vs = new VertexShader();

        // ���̴���� + ���� ��ų ���̴� ���� �̸�, ������ �Լ� �̸�
        vs->Create(ShaderPath + L"VertexColor.hlsl", "VS");
    }

    // InputLayout
    {
        il = new InputLayout();
        il->Create(VertexColor::descs, VertexColor::count,
            vs->GetBlob());
    }

    // PixelShader
    {
        ps = new PixelShader();
        ps->Create(ShaderPath + L"VertexColor.hlsl", "PS");
    }

    // WolrdBuffer
    {
        wb = new WorldBuffer();
    }

    // Collision
    {
        edge = new RectEdge();
        collision = new BoundingBox();

        // ���� ��ġ ����
        for (int i = 0; i < 4; i++)
            verticesPosition[i] = vertices[i].position;
    }


}

Rect::~Rect()
{
    SAFE_DELETE(collision);
    SAFE_DELETE(edge);

    SAFE_DELETE(wb);

    SAFE_DELETE(ps);
    SAFE_DELETE(il);
    SAFE_DELETE(vs);

    SAFE_DELETE(ib);
    SAFE_DELETE(vb);
}

void Rect::Update()
{   // ������Ʈ���� �ַ� �� ��ü�� �� �����Ӹ��� �� �ൿ���� ����д�
    // Move();         // �� ��ü�� �����ϲ���
    UpdateWorld();  // ����� ��ġ�� ���̴�.

    // �浹 �ڽ��� ������ ����
    collision->UpdateCollisionData(world, verticesPosition);
}

void Rect::Render()
{
    vb->SetIA();
    ib->SetIA();
    il->SetIA();
    // �ﰢ���� ��� �׸��� �����ִ� �Լ�
    DC->IASetPrimitiveTopology(
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    vs->SetShader();
    wb->SetVSBuffer(0);

    ps->SetShader();

    // ���������� �׸��� �׸��� �ڵ�
    DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void Rect::Move()
{
    float mSpd = 100;

    // Ű����� W�� ������ ���� ���
    // Get()->Down == �������� �ѹ���
    // Get()->Up == ������ ������ �ѹ���
    if (Keyboard::Get()->Press('W'))
    {
        // Time::Get()->Delta()�� �����Ӱ� ������ ������ �ð��� ��ȯ
        // �� ���� ��� ������ 1�� �ƴٸ� 1�ʰ� �����ٴ� �̾߱�
        position.y += mSpd * Time::Delta();

        // ���Է����� S�� �־����� Ȯ��
        // �����ٸ�
        if (Keyboard::Get()->Press('S') && moveD == false)
        {
            // �̵����� 2��� ������
            // ���� �ִ� ������ ���� ������� �Ʒ��� ����.
            position.y -= (mSpd * 2) * Time::Delta();
        }
    }    
    else if (Keyboard::Get()->Press('S'))
    {
        moveD = true;
        position.y -= mSpd * Time::Delta();
    }

    if (Keyboard::Get()->Up('S')) moveD = false;

    if (Keyboard::Get()->Press('A'))
    {
        position.x -= mSpd * Time::Delta();
        if (Keyboard::Get()->Press('D') && !moveR)
        {
            position.x += (mSpd * 2) * Time::Delta();
        }
    }
    else if (Keyboard::Get()->Press('D'))
    {
        moveR = true;
        position.x += mSpd * Time::Delta();
    }

    if (Keyboard::Get()->Up('D')) moveR = false;

    // Ű����� �����̽��ٸ� ������ ���
    // �Ϲ����� ���ĺ� Ű�� ' ' ���ڷ� �����ϰ�
    // �׿��� �پ��� Ű�� (F1 , SAPCE, CTRL) ������ VK ����Ű�� �����Ѵ�.
    if (Keyboard::Get()->Down(VK_SPACE))
    {
        /*
        ��� ������ �⺻������ bool���� �̿���
        �����̽��ٸ� ��������� �ش� bool���� true�� �ٲٸ�
        �ش� bool���� true�϶� ���� �̵��� �����ϴ°��� �⺻���� �д�.

        ����, ������ �������ִµ��� ������ ���̰� ���� �����ϴ� �����
        ������ �����ʹٸ� bool���� ������� �ʾƵ� �ȴ�.

        ���� ����¹� 1. ���� �ð� �̿��ϱ� 
        // ������ �ð��� ���� ���� ���� 
        1. �����̽��ٸ� ��������� �����ð� ���� ���� ����.
        (Time::Delta�� ��� �������ٰ� 1�� �Ǹ� 1�ʰ� �����ܰ���)
        2. ���� �ð��� ������ �ٽ� �����ִ� ������ õõ�� �����´�.

        ���� ����¹� 2. �߷� �̿��ϱ� 
        // ���Ӱ����� ���� ���� ���� ����
        1. �����̽��ٸ� ��������� �߷°���ŭ �̵��� �����ϱ�
        2. �߷°��� ó���� +���ٰ� �ð��� �������� ���� -�� �ٲ��.

        ���� ����¹� 3. Ư�� �Ÿ����� �̵��ϱ� 
        // ������ ������ ���� ���� ���� ����
        1. �����̽��ٸ� ��������� ���� �ڽ��� ��ġ���� Ư�� ��ǥ����
        ������ �̵�
        2. �ش� ��ǥ ���޽� �ٽ� õõ�� ������
        */
    }

}

void Rect::GUI()
{
    // ImGui�� �̿��� UI�� ������ ��ɰ� �ڵ��
    
    // ImGui �ڵ���� �̿��� UI�� ��������� ���� �����ؾ��ϴ� �Լ�
    ImGui::Begin("Rect", &bOpen);
    {
        ImGui::Text(MakeLabel("Rect").c_str());
        ImGui::SliderFloat2(MakeLabel("Pos").c_str(), position,0, WinMaxWidth);
        ImGui::SliderFloat2(MakeLabel("Size").c_str(), size, 0, WinMaxWidth);
        ImGui::SliderAngle(MakeLabel("Rot").c_str(), &rotation,
            0, 360.0f);

        // Ư�� UI����� �۵��ߴٸ� Ư�� �Լ��� �����ϰ� �Ҽ��� ����
        if (ImGui::ColorPicker4(MakeLabel("Color").c_str(), color))
            UpdateColor();
    }
    // ImGui�� UI����°� �����ٴ°��� �˷��� �Լ�
    ImGui::End();
}

void Rect::UpdateColor()
{
    D3D11_MAPPED_SUBRESOURCE subResource;
    DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0,
        &subResource);
    { // �������� ����
        for (VertexColor& v : vertices)
        {
            // vertices���ٰ� ����� color���� �־��ְ�
            v.color = color;
        }

        // ����� color���� vertices���ٰ� �־��ش�.
        memcpy(subResource.pData, vertices.data(),
            vb->GetCount() * vb->GetStride());
    }
    DC->Unmap(vb->GetResource(), 0);
}

string Rect::MakeLabel(string label)
{
    // �ڱ� �ڽ��� �ּҸ� �Ű� ������ ���� �� �ڿ� ����ִ´�.
    string Label = label + "##" + to_string((uint)this);
    return Label;
}

void Rect::UpdateWorld()
{
    // ���� ũ�⸦ ����� ũ��� ����
    D3DXMatrixScaling(&S, size.x, size.y, size.z);
    // ���� ȸ������ ����� ȸ�������� ����
    D3DXMatrixRotationZ(&R, rotation);
    // ���� ��ġ�� ����� ��ġ�� ����
    D3DXMatrixTranslation(&T, position.x, position.y, position.z);

    // SRT������ �ƴϸ� ���������� ������ ����
    world = S * R * T;
    wb->SetWorld(world);
}

void Rect::SetColor(Color color)
{
    this->color = color;
    UpdateColor();
}
