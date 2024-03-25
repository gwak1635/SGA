#include "Framework.h"
#include "IndexBuffer.h"

IndexBuffer::~IndexBuffer()
{
    SAFE_RELEASE(buffer);
}

void IndexBuffer::Create(const vector<uint>& indices, const D3D11_USAGE& usage)
{
    stride = sizeof(uint);     // ���� ũ�� ����
    count = indices.size();    // ���� ���� ����

    // DESC�� ���α׷��Ӱ� ���ϴ� ������ �°� �����
    // Dircex�����͵��� ����� ���� ������ ���赵��.
    D3D11_BUFFER_DESC desc; // ����ü / struct
    // Desc �޸� �ʱ�ȭ
    ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

    // desc ����
    {
        // Cpu�� gpu�� ��� �����͸� ����Ұ��� �����ϴ�
        // ��� �뵵
        desc.Usage = usage;

        // ��� ����
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        
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

        subData.pSysMem = indices.data();

        // HRESULT�� �ش� �۾��� ���������� ����ƴ��� �Ǵ��ϴ�
        // �ڷ����̸�, �۾��� ���� ������ CHECK�� ����־�
        // ����, �۾��� ���������� ������� �ʾҴٸ�
        // ����� �����޼����� ��µȴ�.
        HRESULT hr = DEVICE->CreateBuffer(&desc, &subData,
            &buffer);
        CHECK(hr);
    }
}

void IndexBuffer::SetIA()
{
    DC->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, offset);
}
