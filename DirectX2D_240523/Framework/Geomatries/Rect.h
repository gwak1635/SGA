#pragma once

// �簢�� ��ü�� ������� ��ü // �ܻ��� ����
class Rect
{
public:
    // ��ü�� ��ġ, ��ü�� ũ��, ��ü�� ȸ��
    Rect(Vector3 position, Vector3 size, float rotation = 0.0f);
    ~Rect();

    // �� �����Ӹ��� ����� �����
    void Update();

    // �� �����Ӹ��� �׸��� �׸��� �ڵ��
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
    // ������ �����͵� // �簢���̴ϱ� 4�� �ʿ��ϹǷ� ���ͷ� ����
    vector<VertexColor> vertices;
    VertexBuffer* vb = nullptr;

    // �ﰢ���� �׸��� ����
    vector<UINT> indices;
    IndexBuffer* ib = nullptr;

    // ������ �������� �ؼ� ���
    InputLayout* il = nullptr;

    // �׸��� �׸� ���̴���
    VertexShader* vs = nullptr;
    PixelShader* ps = nullptr;

    // ������ GPU�� �Ѱ��� ����
    WorldBuffer* wb = nullptr;
    // DirectX�� �ν��� ���� ���
    D3DXMATRIX world;
    // ������ �ش� ��ü�� ũ��, ȸ��, ��ġ
    D3DXMATRIX S, R, T;

    Vector3 position;   // ��ü�� ���� ��ǥ
    Vector3 size;       // ��ü�� ���� ������
    float rotation;     // ��ü�� ���� ȸ����

    // ��ü�� ���� // R,G,B,A
    Color color = Color(1, 0, 0, 1);

    // ImGui���� ����� �Ұ�
    bool bOpen = true;

    RectEdge* edge = nullptr;
    BoundingBox* collision = nullptr;

    Vector3 verticesPosition[4];

    // �̵� ����� Ʈ����
    bool moveD = false;
    bool moveR = false;
};