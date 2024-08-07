#pragma once

class TextureRect
{
public:
    TextureRect(Vector3 position, Vector3 size, float rotation = 0.0f);
    TextureRect(Vector3 position, Vector3 size, float rotation, wstring path);
    ~TextureRect();

    // 매 프레임마다 실행될 내용
    void Update();

    // 업데이트 이후 그릴 내용
    void Render();

    // ImGui출력을 위한 함수
    void GUI();

    void UpdateColor();
    void SetColor(Color color);

    // ImGui에서 사용할 객체 구분값
    string MakeLabel(string label);

    void UpdateWorld();

    void Move();

    void AutoMove();

    void RevercemoveWS();

    void RevercemoveAD();

    void Jump();

    BoundingBox* GetCollision() { return collision; }

    void SetGoingLeft(bool left) { isGoleft = left; }

    void GotoBegin();

    Vector3 GetPosition() { return position; }
    void SetPosition(Vector3 pos) { position = pos; }

    void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }
    void SetShader(wstring shaderPath);
    void SetImage(wstring imagePath);

private:
    // 정점의 데이터 // 사각형이니까 4개 필요함 그래서 vector로 선언
    vector<VertexTexture> vertices;
    VertexBuffer* vb = nullptr;

    // 삼각형을 그리는 순서
    vector<UINT> indices;
    IndexBuffer* ib = nullptr;

    // 정점의 데이터 해석 방법
    InputLayout* il = nullptr;

    // 그림을 그릴 쉐이더
    VertexShader* vs = nullptr;
    PixelShader* ps = nullptr;

    // 공간의 데이터를 저장할 버퍼
    WorldBuffer* wb = nullptr;
    // 실질적인 공간 데이터
    D3DXMATRIX world;
    // 공간에 배치된 크기, 회전, 위치 값
    D3DXMATRIX S, R, T;

    Vector3 position;   // 객체의 로컬 좌표
    Vector3 size;       // 객체의 로컬 크기
    float rotation;     // 객체의 로컬 회전값

    ID3D11ShaderResourceView* srv = nullptr;
    ID3D11RasterizerState* rs = nullptr;
    

    // 객체의 색깔 // R, G, B, A
    Color color = Color(1, 0, 0, 1);

    // ImGui에서 사용할 트리거
    bool bOpen = true;

    // 이동 제어용 트리거
    bool moveD = false;
    bool moveR = false;

    // 점프 관련 변수들
    bool bJump = false;

    float maxJumpT = 0.75f;
    float curJumpT = 0.0f;

    float maxJumpSpd = 10.0f;
    float curJumpSpd = maxJumpSpd;

    bool bFall = false;

    float jumpStartY = 0.0f;

    // 충돌 계산을 하기 위한 변수
    BoundingBox* collision = nullptr;
    RectEdge* edge = nullptr;

    Vector3 verticesPosition[4];

    //장애물이 어느쪽으로 이동할지에 대한 변수
    bool isGoleft = true;

    bool LockW = false;
    bool LockA = false;
    bool LockS = false;
    bool LockD = false;
};

