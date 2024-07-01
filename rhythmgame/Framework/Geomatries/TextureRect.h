#pragma once

class TextureRect
{
public:
    TextureRect(Vector3 position, Vector3 size, float rotation);
    TextureRect(Vector3 position, Vector3 size, float rotation, wstring path);
    

    virtual ~TextureRect();

    void Update();

    void NoteFall(float baesok);

    void Render();
    void GUI();

    void UpdateWorld();

    void SetPosition(Vector3 position) { this->position = position; }
    Vector3 GetPosition() { return position; }

    void SetSize(Vector3 size) { this->size = size; }
    Vector3 GetSize() { return size; }

    void SetLoading(bool loading) { this->isloading = loading; }
    int GetLoading() { return isloading; }

    void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }
    void SetShader(wstring shaderPath);
    void SetImage(wstring imagePath);

    BoundingBox* GetCollision() { return collision; }

protected:
    // 정점의 데이터들 // 사각형이니까 4개 필요하므로 벡터로 선언
    vector<VertexTexture> vertices;
    VertexBuffer* vb = nullptr;

    // 삼각형을 그리는 순서
    vector<UINT> indices;
    IndexBuffer* ib = nullptr;

    // 정점의 데이터의 해석 방법
    InputLayout* il = nullptr;

    // 그림을 그릴 쉐이더들
    VertexShader* vs = nullptr;
    PixelShader* ps = nullptr;

    // 공간을 GPU로 넘겨줄 버퍼
    WorldBuffer* wb = nullptr;
    // DirectX가 인식할 공간 행렬
    D3DXMATRIX world;
    // 공간에 해당 객체의 크기, 회전, 위치
    D3DXMATRIX S, R, T;

    Vector3 position;   // 객체의 로컬 좌표
    Vector3 size;       // 객체의 로컬 사이즈
    float rotation;     // 객체의 로컬 회전값

    ID3D11ShaderResourceView* srv = nullptr;
    ID3D11RasterizerState* rs = nullptr;

    // ImGui에서 사용할 불값
    bool bOpen = true;

    RectEdge* edge = nullptr;
    BoundingBox* collision = nullptr;

    Vector3 verticesPosition[4];


    D3D11_MAPPED_SUBRESOURCE subRe;

    //로딩여부
    bool isloading = true;

};