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
        // vector.assign 은 벡터의 크기를 재설정
        vertices.assign(4, VertexTexture());

        // 좌 하단
        vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
        vertices[0].uv = Vector2(0, 1);

        // 우 상단
        vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
        vertices[1].uv = Vector2(1, 0);

        // 우 하단
        vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
        vertices[2].uv = Vector2(1, 1);

        // 좌 상단
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

        // 쉐이더경로 + 실행 시킬 쉐이더 파일 이름, 실행할 함수 이름
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

        // 정점 위치 전달
        for (int i = 0; i < 4; i++)
            verticesPosition[i] = vertices[i].position;
    }

    // Rasterizer State
    // 레스터라이저는 버텍스 쉐이더로 찍은 정점들의 사이와 내부를
    // 채워주는 역할이다.
    // 이거 안만들면 기본값으로 넣어주고 만들면 만든거 넣어줌
    {
        D3D11_RASTERIZER_DESC desc;
        ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));

        // CullMode : 그리지 않을 부분 설정
        // d3d11_cull_back == 뒷면 지우겠다. (반시계 방향 안그림)
        desc.CullMode = D3D11_CULL_BACK;

        // FillMode : 체우는 방식 설정
        // d3d11_fill_solid == 전부 체우겠다. (빈공간 안만든다)
        desc.FillMode = D3D11_FILL_SOLID;

        // 시계방향 설정 (false == 시계 방향 // true == 반 시계 방향)
        desc.FrontCounterClockwise = false;

        HRESULT hr = DEVICE->CreateRasterizerState(&desc, &rs);
        CHECK(hr);
    }

    // SRV 추출 // 그림 데이터 추출
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