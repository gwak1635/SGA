#include "Framework.h"
#include "TextureRect.h"

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation)
    : position(position), size(size), rotation(rotation)
{
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
}

TextureRect::TextureRect(Vector3 position, Vector3 size, float rotation, wstring path)
    : position(position), size(size), rotation(rotation)
{
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

TextureRect::~TextureRect()
{
    SAFE_RELEASE(srv);
    SAFE_RELEASE(rs);

    SAFE_DELETE(collision);
    SAFE_DELETE(edge);

    SAFE_DELETE(wb);

    SAFE_DELETE(ps);
    SAFE_DELETE(il);
    SAFE_DELETE(vs);

    SAFE_DELETE(ib);
    SAFE_DELETE(vb);
}

void TextureRect::Update()
{
    UpdateWorld();

    collision->UpdateCollisionData(world, verticesPosition);
}

void TextureRect::Render()
{
    vb->SetIA();
    ib->SetIA();
    il->SetIA();
    // 삼각형을 어떻게 그릴지 정해주는 함수
    DC->IASetPrimitiveTopology(
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    vs->SetShader();
    wb->SetVSBuffer(0);

    ps->SetShader();

    DC->PSSetShaderResources(0, 1, &srv);
    DC->RSSetState(rs);

    // 실질적으로 그림을 그리는 코드
    DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void TextureRect::GUI()
{
    // 필요하면 만들어서 넣으면됨
    // Rect->GUI() 참고 하기
}

void TextureRect::UpdateWorld()
{
    // 로컬 크기를 월드상 크기로 변경
    D3DXMatrixScaling(&S, size.x, size.y, size.z);
    // 로컬 회전값을 월드상 회전값으로 변경
    D3DXMatrixRotationZ(&R, rotation);
    // 로컬 위치를 월드상 위치로 변경
    D3DXMatrixTranslation(&T, position.x, position.y, position.z);

    // SRT순서가 아니면 정상적으로 나오지 않음
    world = S * R * T;
    wb->SetWorld(world);
}

void TextureRect::SetShader(wstring shaderPath)
{
    vs->Clear();
    ps->Clear();

    vs->Create(shaderPath, "VS");
    ps->Create(shaderPath, "PS");
}

void TextureRect::SetImage(wstring imagePath)
{
    SAFE_RELEASE(srv);
    // SRV 추출 // 그림 데이터 추출
    HRESULT hr = D3DX11CreateShaderResourceViewFromFile
    (
        DEVICE,
        imagePath.c_str(),
        nullptr,
        nullptr,
        &srv,
        nullptr
    );
    CHECK(hr);
}
