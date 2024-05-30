#pragma once
#include "Framework.h"

// 정점 데이터 이외의 데이터를 CPU에서 GPU로 넘겨줄때 사용할 버퍼
// 주로 상속을 해줄 객체 // 부모 객체
class ShaderBuffer
{
public:

    void SetVSBuffer(uint slot)
    {
        // 데이터를 복사해서
        MapData();
        // VS에서 사용할 데이터를 1개 넘겨주겠다
        DC->VSSetConstantBuffers(slot, 1, &buffer);
    }

    void SetPSBuffer(uint slot)
    {
        // 데이터를 복사해서
        MapData();
        // PS에서 사용할 데이터를 1개 넘겨주겠다
        DC->PSSetConstantBuffers(slot, 1, &buffer);
    }

protected:
    // GPU는 정점 이외의 데이터를 받을땐 상수 버퍼를 통해 받는다.
    ShaderBuffer(void* data, uint dataSize)
        : data(data), dataSize(dataSize)
    {
        desc.Usage = D3D11_USAGE_DYNAMIC;               // 사용 용도
        desc.ByteWidth = dataSize;                      // 버퍼 크기
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;    // 바인딩 대상
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;   // CPU 접근 방식

        // 버퍼 만들기
        HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &buffer);
        CHECK(hr);
    }

private:
    // DirectX에서 Map은 데이터를 잠시 묶고 해당 데이터를 런타임중에
    // 수정하거나 복사하는 기능을 허락하는걸 Map이라 부르고
    // Map을 했으면 반드시 Unmap을 실행해 줘야한다. // 데이터 매핑
    void MapData()
    {
        // 데이터를 임시적으로 보관할 변수
        D3D11_MAPPED_SUBRESOURCE subResource;

        HRESULT hr = DC->Map
        (
            buffer,                     // 매핑할 대상
            0,                          // 매핑 시작 위치 (0은 처음부터)
            D3D11_MAP_WRITE_DISCARD,    // 매핑 방법 (지우고 다시 쓰겠다)
            0,                          // 추가로 매핑할 하위 리소스
            &subResource                // 매핑한 데이터를 저장할 변수
        );
        CHECK(hr);

        // 데이터 복사 (여기있는 데이터를, 여기에다, 이만큼)
        memcpy(subResource.pData, data, dataSize);

        DC->Unmap(buffer, 0);
    }

private:
    D3D11_BUFFER_DESC desc = { 0 };
    ID3D11Buffer* buffer = nullptr;

    // void*는 자료형이 정해져있지 않은 포인터로 
    // 어떠한 자료형의 데이터도 가리킬수있는 포인터이다.
    void* data = nullptr;
    uint dataSize = 0;
};