#pragma once

// 사각형 물체를 출력해줄 객체 // 단색을 가진
class Rect
{
public:
    // 객체의 위치, 객체의 크기, 객체의 회전
    Rect(Vector3 position, Vector3 size, float rotation = 0.0f);
    ~Rect();

    // 매 프레임마다 실행될 내용들
    void Update();

    // 매 프레임마다 그림을 그리는 코드들
    void Render();

    void Move();

    void GUI();

    void UpdateColor();
    string MakeLabel(string label);

    void UpdateWorld();

    void SetColor(Color color);

    BoundingBox* GetCollision() { return collision; }
    
    Vector3 GetSize() { return size; }

    Vector3 GetPosition() { return position; }
    void SetPosition(Vector3 pos) { position = pos; }

private:
    // 정점의 데이터들 // 사각형이니까 4개 필요하므로 벡터로 선언
    vector<VertexColor> vertices;
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

    // 객체의 색깔 // R,G,B,A
    Color color = Color(1, 0, 0, 1);

    // ImGui에서 사용할 불값
    bool bOpen = true;

    RectEdge* edge = nullptr;
    BoundingBox* collision = nullptr;

    Vector3 verticesPosition[4];

    // 이동 제어용 트리거
    bool moveD = false;
    bool moveR = false;
};