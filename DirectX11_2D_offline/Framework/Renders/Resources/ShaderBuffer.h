#pragma once
#include "Framework.h"

// CPU�� GPU���� ������ �ƴ� �����͸� �ǳ��ֱ� ���� �뵵�� ���
class ShaderBuffer
{
public:
    void SetVSBuffer(UINT slot)
    {
        MapData();
        DC->VSSetConstantBuffers(slot, 1, &buffer);
    }

    void SetPSBuffer(UINT slot)
    {
        MapData();
        DC->PSSetConstantBuffers(slot, 1, &buffer);
    }
protected:
    ShaderBuffer(void* data, UINT dataSize)
        : data(data), dataSize(dataSize)
    {
        // ������ ��� �뵵 // DYNAMIC = CPU���� ���� ����
        desc.Usage = D3D11_USAGE_DYNAMIC;
        // ������ ũ��
        desc.ByteWidth = dataSize;
        // ��� ���� // CONSTANT_BUFFER = ��� ���۷� ����� ���̴�.
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        // CPU ���� ���
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &buffer);
        CHECK(hr);
    }

private: // �Լ�

    // Map�� DirectX���� ��Ÿ���߿� �޸𸮰� ������ �ִ� �����͸� �����ϴ�
    // ����� ���Ѵ�.
    // Map�� ����ϴ� ������ ��Ÿ���߿� �߿��� �����Ͱ� �ջ���� ���� �����ϵ���
    // �ϱ� ���ؼ� �ε�, �׷��� ������ ���� �߿��� �����Ͱ� �ƴ϶��
    // Map�� ������� �ʴ´�.
    // Map�� �ݵ�� D3D11_MAPPED_SUBRESOURCE�� �̿��� �޸𸮸� �����ϴµ�
    // D3D11_MAPPED_SUBRESOURCE �� ���� ��� �����͸� �����ϰ� �ű�� �ִ�
    // ����ü �̴�.
    void MapData()
    {
        // ������ ������ ������ ����ü
        D3D11_MAPPED_SUBRESOURCE subRe;
        // ������ ����
        HRESULT hr = DC->Map
        (
            buffer,                 // ������ ���
            0,                      // ���� ���� ��ġ (0 = ó������)
            D3D11_MAP_WRITE_DISCARD,// ���� ��� // WRITE_DISCARD�� ������ �ٽ�
            0,                      // �߰��� ������ ��� (0 = ����)
            &subRe                  // ���� �����͸� ������ ����ü
        );
        CHECK(hr);
        // �޸� ���� // subRe�� �������ִ� �����͸� data���� dataSize��ŭ
        memcpy(subRe.pData, data, dataSize);
        DC->Unmap(buffer, 0);
    }
private: // ����
    D3D11_BUFFER_DESC desc = { 0 };
    ID3D11Buffer* buffer = nullptr;

    void* data = nullptr;
    UINT dataSize = 0;
};