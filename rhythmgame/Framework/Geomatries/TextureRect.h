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
    // ������ �����͵� // �簢���̴ϱ� 4�� �ʿ��ϹǷ� ���ͷ� ����
    vector<VertexTexture> vertices;
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

    ID3D11ShaderResourceView* srv = nullptr;
    ID3D11RasterizerState* rs = nullptr;

    // ImGui���� ����� �Ұ�
    bool bOpen = true;

    RectEdge* edge = nullptr;
    BoundingBox* collision = nullptr;

    Vector3 verticesPosition[4];


    D3D11_MAPPED_SUBRESOURCE subRe;

    //�ε�����
    bool isloading = true;

};