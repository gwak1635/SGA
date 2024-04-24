#pragma once

class Rect
{
public:
    Rect(Vector3 position, Vector3 size, float rotation = 0.0f);
    ~Rect();

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

    void Jump();

    BoundingBox* GetCollision() { return collision; }
private:
    // ������ ������ // �簢���̴ϱ� 4�� �ʿ��� �׷��� vector�� ����
    vector<VertexColor> vertices;
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

};