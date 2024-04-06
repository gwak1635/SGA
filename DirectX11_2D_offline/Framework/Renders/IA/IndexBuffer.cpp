#include "Framework.h"
#include "IndexBuffer.h"

IndexBuffer::~IndexBuffer()
{
    SAFE_RELEASE(buffer);
}

void IndexBuffer::Create(const vector<UINT>& indices, const D3D11_USAGE& usage)
{
    // ������ ũ��
    stride = sizeof(UINT);
    // ������ ����
    count = indices.size();

    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

    // desc ����
    {
        desc.Usage = usage;
        // ��� ����
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
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
        D3D11_SUBRESOURCE_DATA subData;
        ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));

        // subData�� vertices ���� ��ǥ�� �ǳ���
        subData.pSysMem = indices.data();

        HRESULT hr = DEVICE->CreateBuffer(&desc, &subData,
            &buffer);
        CHECK(hr);
    }
}

void IndexBuffer::SetIA()
{
    // ��ǲ ������� ���۸� �־��ִ� �Լ�
    DC->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, offset);
}
