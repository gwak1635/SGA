#pragma once

class VertexBuffer
{
public:
    ~VertexBuffer();

    // template<typename T>�� �� ������ ���� �Լ��� ���� T��
    // ��� ���� ����Ҽ� �ֵ��� ���ִ� ����̴�.
    
    // Create���� ���ø��� ����� ������ �׸� �簢���� ����
    // �ٸ� �����͸� �ǳ���� �ϱ� �����̴�.
    template<typename T>
    void Create(const vector<T>& vertices,
        const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

    ID3D11Buffer* GetResource() { return buffer; }

    uint GetStride() { return stride; }
    uint GetOffset() { return offset; }
    uint GetCount()  { return count;  }

    void SetIA();

private:
    ID3D11Buffer* buffer = nullptr;

    // ���ۿ��� �� ������ ũ�⸦ ��Ÿ���� ��
    uint stride = 0;
    // ���ۿ��� ���� ���� ��ġ
    uint offset = 0;
    // ���ۿ��� ���� ������ ����
    uint count  = 0;
};

template<typename T>
inline void VertexBuffer::Create(const vector<T>& vertices, const D3D11_USAGE& usage)
{
    stride = sizeof(T);     // ���� ũ�� ����
    count = vertices.size();// ���� ���� ����

    // DESC�� ���α׷��Ӱ� ���ϴ� ������ �°� �����
    // Dircex�����͵��� ����� ���� ������ ���赵��.
    D3D11_BUFFER_DESC desc; // ����ü / struct
    // Desc �޸� �ʱ�ȭ
    ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

    // desc ����
    {
        // ��� �뵵
        desc.Usage = usage;
        // ��� ����
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        // ���� ũ��
        desc.ByteWidth = stride * count;
        // cpu ����
        // GPU�� ��� ������ �����Ҽ� �ִ�.
        switch (usage)
        {
            // CPU�� �����Ҽ� ���� ����
            // GPU�� �����Ҽ� �ִ� ����
        case D3D11_USAGE_DEFAULT:
            // CPU�� �����Ҽ� ���� ����
            // GPU�� �����Ҽ� ���� ����
        case D3D11_USAGE_IMMUTABLE:
            break;
            // CPU���� ���� �����ϰ� �����Ҽ� �ִ� ����
            // GPU�� �����Ҽ� ���� ����
        case D3D11_USAGE_DYNAMIC:
            desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            break;
            // CPU���� ���� �����ϰ� �����Ҽ� �ִ� ����
            // GPU�� �����Ҽ� �ִ� ����
        case D3D11_USAGE_STAGING:
            desc.CPUAccessFlags =
                D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
            break;
        }
    }

    // ����
    {
        // D3D11_SUBRESOURCE_DATA�� �پ��� �����͸� �ӽ÷�
        // �����Ҽ��ִ� ����ü�̴�.
        D3D11_SUBRESOURCE_DATA subData;
        ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));

        subData.pSysMem = vertices.data();

        // HRESULT�� �ش� �۾��� ���������� ����ƴ��� �Ǵ��ϴ�
        // �ڷ����̸�, �۾��� ���� ������ CHECK�� ����־�
        // ����, �۾��� ���������� ������� �ʾҴٸ�
        // ����� �����޼����� ��µȴ�.
        HRESULT hr = DEVICE->CreateBuffer(&desc, &subData,
            &buffer);
        CHECK(hr);
    }
}
