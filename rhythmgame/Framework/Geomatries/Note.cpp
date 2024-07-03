#include "Framework.h"
#include "Note.h"

Note::Note(Vector3 position, Vector3 size, float rotation, int p_lane)
    : TextureRect(position,size,rotation)
{
    wstring path;

    lane = p_lane;

    switch (lane)
    {
    case 0:
        path = TexturePath + L"150p30\\Blue.png";
        break;
    case 1:
    case 2:
        path = TexturePath + L"150p30\\Red.png";
        break;
    case 3:
        path = TexturePath + L"150p30\\Blue.png";
        break;
    case 4:
    case 5:
        path = TexturePath + L"150p30\\Twin.png";
        break;
    default:
        break;
    }


    // Vertices
    {
        // vector.assign �� ������ ũ�⸦ �缳��
        vertices.assign(4, VertexTexture());

        // �� �ϴ�
        vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
        vertices[0].uv = Vector2(0, 1);

        // �� ���
        vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
        vertices[1].uv = Vector2(1, 0);

        // �� �ϴ�
        vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
        vertices[2].uv = Vector2(1, 1);

        // �� ���
        vertices[3].position = Vector3(-0.5f, 0.5f, 0.0f);
        vertices[3].uv = Vector2(0, 0);
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
        vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");
    }

    // InputLayout
    {
        il = new InputLayout();
        il->Create(VertexTexture::descs, VertexTexture::count,
            vs->GetBlob());
    }

    // PixelShader
    {
        ps = new PixelShader();
        ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");
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

    // Rasterizer State
    // �����Ͷ������� ���ؽ� ���̴��� ���� �������� ���̿� ���θ�
    // ä���ִ� �����̴�.
    // �̰� �ȸ���� �⺻������ �־��ְ� ����� ����� �־���
    {
        D3D11_RASTERIZER_DESC desc;
        ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));

        // CullMode : �׸��� ���� �κ� ����
        // d3d11_cull_back == �޸� ����ڴ�. (�ݽð� ���� �ȱ׸�)
        desc.CullMode = D3D11_CULL_BACK;

        // FillMode : ü��� ��� ����
        // d3d11_fill_solid == ���� ü��ڴ�. (����� �ȸ����)
        desc.FillMode = D3D11_FILL_SOLID;

        // �ð���� ���� (false == �ð� ���� // true == �� �ð� ����)
        desc.FrontCounterClockwise = false;

        HRESULT hr = DEVICE->CreateRasterizerState(&desc, &rs);
        CHECK(hr);
    }

    // SRV ���� // �׸� ������ ����
    {
        HRESULT hr = D3DX11CreateShaderResourceViewFromFile
        (
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