#include "Framework.h"
#include "TextureRect.h"

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation)
    : position(position), size(size), rotation(rotation)
{
    // Vertices
    {
        // vertices ũ�� ���Ҵ�
        vertices.assign(4, VertexTexture());

        // �� �ϴ�
        vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
        vertices[0].uv = Vector2(0,1);

        // �� ���
        vertices[1].position = Vector3(+0.5f, +0.5f, 0.0f);
        vertices[1].uv = Vector2(1, 0);

        // �� �ϴ�
        vertices[2].position = Vector3(+0.5f, -0.5f, 0.0f);
        vertices[2].uv = Vector2(1, 1);

        // �� ���
        vertices[3].position = Vector3(-0.5f, +0.5f, 0.0f);
        vertices[3].uv = Vector2(0, 0);
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
        vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");
    }

    // PixelShader
    {
        ps = new PixelShader();

        // ���̴� ��� + ���� �̸� , ������ ���̴� �Լ� �̸�
        ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");
    }

    // InputLayout
    {
        il = new InputLayout();

        il->Create(VertexTexture::descs, VertexTexture::count,
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

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation, wstring path)
    : position(position), size(size), rotation(rotation)
{
    {
        // Vertices
        {
            // vertices ũ�� ���Ҵ�
            vertices.assign(4, VertexTexture());

            // �� �ϴ�
            vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
            vertices[0].uv = Vector2(0, 1);

            // �� ���
            vertices[1].position = Vector3(+0.5f, +0.5f, 0.0f);
            vertices[1].uv = Vector2(1, 0);

            // �� �ϴ�
            vertices[2].position = Vector3(+0.5f, -0.5f, 0.0f);
            vertices[2].uv = Vector2(1, 1);

            // �� ���
            vertices[3].position = Vector3(-0.5f, +0.5f, 0.0f);
            vertices[3].uv = Vector2(0, 0);
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
            vs->Create(ShaderPath + L"VertexShader.hlsl", "VS");
        }

        // PixelShader
        {
            ps = new PixelShader();

            // ���̴� ��� + ���� �̸� , ������ ���̴� �Լ� �̸�
            ps->Create(ShaderPath + L"VertexShader.hlsl", "PS");
        }

        // InputLayout
        {
            il = new InputLayout();

            il->Create(VertexTexture::descs, VertexTexture::count,
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

        //Rasterizer State
        {
            D3D11_RASTERIZER_DESC desc;
            ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));

            //�ø��: �׸��� ���� �κ�(�޸� �ڸ��ڴ�.)
            desc.CullMode = D3D11_CULL_BACK;

            //FillMode : ä��� ��� ����
            //FILL_SOLID = �� ä���
            //FILL_WIREFRAME = ���� �׸��ڴ�.

            desc.FillMode = D3D11_FILL_SOLID;

            //�ݽð� ��� ����( false= �ð����)
            desc.FrontCounterClockwise = false;

            HRESULT hr = DEVICE->CreateRasterizerState(&desc, &rs);
            CHECK(hr);

        }

        // SRV ���� // �׸� ������ ����
        {
            HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
                DEVICE,
                path.c_str(),
                nullptr,
                nullptr,
                &srv,
                nullptr
            );
            CHECK(hr);
        }
    }
}

TextureRect::~TextureRect()
{
    SAFE_RELEASE(srv);
    SAFE_RELEASE(rs);

    SAFE_DELETE(edge);
    SAFE_DELETE(collision);

    SAFE_DELETE(wb);

    SAFE_DELETE(il);

    SAFE_DELETE(ps);
    SAFE_DELETE(vs);

    SAFE_DELETE(ib);
    SAFE_DELETE(vb);
}

void TextureRect::Update()
{
    UpdateWorld();
}

void TextureRect::Render()
{

    vb->SetIA();
    ib->SetIA();
    il->SetIA();
    // �ﰢ���� ��� �׸��� ���� �Լ�
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    vs->SetShader();
    wb->SetVSBuffer(0);

    ps->SetShader();

    DC->PSSetShaderResources(0, 1, &srv);
    DC->RSSetState(rs);

    // �׸��� �׸��� �Լ�
    DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void TextureRect::GUI()
{
}

void TextureRect::UpdateColor()
{
}

void TextureRect::SetColor(Color color)
{
}

string TextureRect::MakeLabel(string label)
{
	return string();
}

void TextureRect::UpdateWorld()
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

void TextureRect::Move()
{
}

void TextureRect::AutoMove()
{
}

void TextureRect::RevercemoveWS()
{
}

void TextureRect::RevercemoveAD()
{
}

void TextureRect::Jump()
{
}

void TextureRect::GotoBegin()
{
}

void TextureRect::SetShader(wstring shaderPath)
{
    vs->Clear();//�Ҹ���. ������ �ٽø����)
    ps->Clear();

    vs->Create(shaderPath, "VS");
    ps->Create(shaderPath, "PS");
}

void TextureRect::SetImage(wstring imagePath)
{
    SAFE_RELEASE(srv);

    HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
        DEVICE,
        imagePath.c_str(),
        nullptr,
        nullptr,
        &srv,
        nullptr
    );
    CHECK(hr);
}
