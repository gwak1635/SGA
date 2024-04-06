#pragma once

class VertexBuffer
{
public:
    ~VertexBuffer();

    // template<typename T>�� �� ������ ���� �Լ��� ���� T��
    // ��� ���� ����Ҽ� �ֵ��� ���ִ� ����̴�.

    // Create�� ���ø����� ����� ������ ���߿� ���� �簢���� ����
    // ������ �����͸� �ٸ��� �ǳ���� �ϱ� �����̴�.
    template<typename T>
    void Create(const vector<T>& vertices,
        const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

    ID3D11Buffer* GetResource() { return buffer; }

    UINT GetStride() { return stride; }
    UINT GetOffset() { return offset; }
    UINT GetCount() { return count; }

    void SetIA();
private:
    ID3D11Buffer* buffer = nullptr;

    UINT stride = 0; // ���ۿ��� �� ������ ũ��
    UINT offset = 0; // ���ۿ��� ���� ���� ��ġ
    UINT count = 0; // ���ۿ��� ���� ������ ����
};

template<typename T>
inline void VertexBuffer::Create(const vector<T>& vertices, const D3D11_USAGE& usage)
{
    // ������ ũ��
    stride = sizeof(T);
    // ������ ����
    count = vertices.size();

    // DESC�� ���α׷��Ӱ� ���ϴ� ������ �°� �����
    // DirectX �����͵��� ����� ���� ������ ���赵 & ��û���̴�.
    D3D11_BUFFER_DESC desc;
    // desc�� ����ü �̱� ������, ������ �����͵��� �ʱ�ȭ �ϱ�
    // ���ؼ��� ZeroMemory�� ����ؾ� �Ѵ�.
    ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

    /*
    Buffer�� CPU�� GPU���� �����͸� ������ �ֱ� ���� ���Ǵ�
    �����̴�.
    Buffer�� �⺻������ ���α׷��Ӱ� ����� ���� �ƴ� ���赵��
    �ۼ��� DirectX���� �����޶� ��û�ϴ� �����̸�,
    �̷��� Buffer�� CPU���� GPU�� �����͸� �����ϴ� �뵵�θ�
    ���ȴ�.
    �̶� Buffer�� ���޵ǰ� ���� �ش� Buffer�� ���� �����
    ���� ������ ��ġ���� �����Ͱ� �����Ǵ� Blob�̶� �����͵�
    ���ܳ���.
    */

    // desc ����
    {
        // Usage�� cpu�� gpu�� �ش� �����͸� ��� ����Ұ���
        // �����ϴ� ��� �뵵�̴�.
        desc.Usage = usage;

        // ��� ����
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        // ���� ũ��
        desc.ByteWidth = stride * count;

        // cpu����
        // �⺻������ cpu�� gpu�� �ǳ��ִ� �������̴� ����
        // gpu�� ��� �����Ϳ� �����ϴ°��� �����ϴ�.
        switch (usage)
        {
        case D3D11_USAGE_DEFAULT:
        {
            // CPU�� ������ �� ����
            // GPU�� ������ �� �ִ�
        }
        case D3D11_USAGE_IMMUTABLE:
        {
            // CPU�� ������ �� ����
            // GPU�� ������ �� ����
        }
        break;
        case D3D11_USAGE_DYNAMIC:
        {
            // CPU�� �����ϰ� �����Ҽ� �ִ�
            // GPU�� ������ �� ����
            desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            break;
        }
        case D3D11_USAGE_STAGING:
        {
            // CPU�� �����ϰ� �����Ҽ� �ִ�
            // GPU�� ������ �� �ִ�
            desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE |
                D3D11_CPU_ACCESS_READ;
            break;
        }
        }
    }

    // ���� ����
    {
        // D3D11_SUBRESOURCE_DATA�� �پ��� �����͸� �ӽ÷�
        // �����ϴ°��� ������ ����ü �̴�.
        // D3D11_SUBRESOURCE_DATA�� ������ٴ� ���� �ַ�
        // �޸𸮻� ���������� �ִٴ� ���̴�.
        // D3D11_SUBRESOURCE_DATA���� �ʱ�ȭ�� ZeroMemory��
        // �̿��Ѵ�.
        D3D11_SUBRESOURCE_DATA subData;
        ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));

        // subData�� vertices ���� ��ǥ�� �ǳ���
        subData.pSysMem = vertices.data();

        // HRESULT�� �ش� �۾��� ���������� ���� �ƴ����� �Ǵ��ϴ�
        // �ڷ����̸�, �۾��� ���� ������ CHECK�� ����־�
        // ����, �۾��� ���������� ������ �ʾҴٸ�
        // ���α׷��� ���Ľ�Ű�� �ش� CHECK�� ��ġ�� �˷��ش�.
        HRESULT hr = DEVICE->CreateBuffer(&desc, &subData,
            &buffer);
        CHECK(hr);
    }
}
