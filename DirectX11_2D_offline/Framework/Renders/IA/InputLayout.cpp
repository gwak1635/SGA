#include "Framework.h"
#include "InputLayout.h"

InputLayout::~InputLayout()
{
    SAFE_RELEASE(inputLayout);
}

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC* descs, uint count, ID3DBlob* blob)
{
    // 만약에 매게변수중 하나라도 없다면 폭파
    if (!descs || !count || !blob)
        CHECK(false);

    HRESULT hr = DEVICE->CreateInputLayout
    (
        // 설계도, 요청서
        descs,
        // 요소의 개수
        count,
        // blob = 메모리 블록
        // blob안에는 버퍼의 다양한 데이터가 들어있다.
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        &inputLayout
    );
}

void InputLayout::SetIA()
{
    DC->IASetInputLayout(inputLayout);
}
