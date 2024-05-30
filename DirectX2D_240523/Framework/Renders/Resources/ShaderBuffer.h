#pragma once
#include "Framework.h"

// ���� ������ �̿��� �����͸� CPU���� GPU�� �Ѱ��ٶ� ����� ����
// �ַ� ����� ���� ��ü // �θ� ��ü
class ShaderBuffer
{
public:

    void SetVSBuffer(uint slot)
    {
        // �����͸� �����ؼ�
        MapData();
        // VS���� ����� �����͸� 1�� �Ѱ��ְڴ�
        DC->VSSetConstantBuffers(slot, 1, &buffer);
    }

    void SetPSBuffer(uint slot)
    {
        // �����͸� �����ؼ�
        MapData();
        // PS���� ����� �����͸� 1�� �Ѱ��ְڴ�
        DC->PSSetConstantBuffers(slot, 1, &buffer);
    }

protected:
    // GPU�� ���� �̿��� �����͸� ������ ��� ���۸� ���� �޴´�.
    ShaderBuffer(void* data, uint dataSize)
        : data(data), dataSize(dataSize)
    {
        desc.Usage = D3D11_USAGE_DYNAMIC;               // ��� �뵵
        desc.ByteWidth = dataSize;                      // ���� ũ��
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;    // ���ε� ���
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;   // CPU ���� ���

        // ���� �����
        HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &buffer);
        CHECK(hr);
    }

private:
    // DirectX���� Map�� �����͸� ��� ���� �ش� �����͸� ��Ÿ���߿�
    // �����ϰų� �����ϴ� ����� ����ϴ°� Map�̶� �θ���
    // Map�� ������ �ݵ�� Unmap�� ������ ����Ѵ�. // ������ ����
    void MapData()
    {
        // �����͸� �ӽ������� ������ ����
        D3D11_MAPPED_SUBRESOURCE subResource;

        HRESULT hr = DC->Map
        (
            buffer,                     // ������ ���
            0,                          // ���� ���� ��ġ (0�� ó������)
            D3D11_MAP_WRITE_DISCARD,    // ���� ��� (����� �ٽ� ���ڴ�)
            0,                          // �߰��� ������ ���� ���ҽ�
            &subResource                // ������ �����͸� ������ ����
        );
        CHECK(hr);

        // ������ ���� (�����ִ� �����͸�, ���⿡��, �̸�ŭ)
        memcpy(subResource.pData, data, dataSize);

        DC->Unmap(buffer, 0);
    }

private:
    D3D11_BUFFER_DESC desc = { 0 };
    ID3D11Buffer* buffer = nullptr;

    // void*�� �ڷ����� ���������� ���� �����ͷ� 
    // ��� �ڷ����� �����͵� ����ų���ִ� �������̴�.
    void* data = nullptr;
    uint dataSize = 0;
};