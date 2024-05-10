#pragma once

class TextureRect
{
public:
    TextureRect(Vector3 position, Vector3 size, float rotation = 0.0f);
    TextureRect(Vector3 position, Vector3 size, float rotation, wstring path);
    ~TextureRect();

    // �� �����Ӹ��� ����� ����
    void Update();

    // ������Ʈ ���� �׸� ����
    void Render();

    // ImGui����� ���� �Լ�
    void GUI();

    void UpdateColor();
    void SetColor(Color color);

    // ImGui���� ����� ��ü ���а�
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
    // ������ ������ // �簢���̴ϱ� 4�� �ʿ��� �׷��� vector�� ����
    vector<VertexTexture> vertices;
    VertexBuffer* vb = nullptr;

    // �ﰢ���� �׸��� ����
    vector<UINT> indices;
    IndexBuffer* ib = nullptr;

    // ������ ������ �ؼ� ���
    InputLayout* il = nullptr;

    // �׸��� �׸� ���̴�
    VertexShader* vs = nullptr;
    PixelShader* ps = nullptr;

    // ������ �����͸� ������ ����
    WorldBuffer* wb = nullptr;
    // �������� ���� ������
    D3DXMATRIX world;
    // ������ ��ġ�� ũ��, ȸ��, ��ġ ��
    D3DXMATRIX S, R, T;

    Vector3 position;   // ��ü�� ���� ��ǥ
    Vector3 size;       // ��ü�� ���� ũ��
    float rotation;     // ��ü�� ���� ȸ����

    ID3D11ShaderResourceView* srv = nullptr;
    ID3D11RasterizerState* rs = nullptr;
    

    // ��ü�� ���� // R, G, B, A
    Color color = Color(1, 0, 0, 1);

    // ImGui���� ����� Ʈ����
    bool bOpen = true;

    // �̵� ����� Ʈ����
    bool moveD = false;
    bool moveR = false;

    // ���� ���� ������
    bool bJump = false;

    float maxJumpT = 0.75f;
    float curJumpT = 0.0f;

    float maxJumpSpd = 10.0f;
    float curJumpSpd = maxJumpSpd;

    bool bFall = false;

    float jumpStartY = 0.0f;

    // �浹 ����� �ϱ� ���� ����
    BoundingBox* collision = nullptr;
    RectEdge* edge = nullptr;

    Vector3 verticesPosition[4];

    //��ֹ��� ��������� �̵������� ���� ����
    bool isGoleft = true;

    bool LockW = false;
    bool LockA = false;
    bool LockS = false;
    bool LockD = false;
};

