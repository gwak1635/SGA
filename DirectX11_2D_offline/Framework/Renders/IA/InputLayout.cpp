#include "Framework.h"
#include "InputLayout.h"

InputLayout::~InputLayout()
{
    SAFE_RELEASE(inputLayout);
}

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC* descs, uint count, ID3DBlob* blob)
{
    // ���࿡ �ŰԺ����� �ϳ��� ���ٸ� ����
    if (!descs || !count || !blob)
        CHECK(false);

    HRESULT hr = DEVICE->CreateInputLayout
    (
        // ���赵, ��û��
        descs,
        // ����� ����
        count,
        // blob = �޸� ���
        // blob�ȿ��� ������ �پ��� �����Ͱ� ����ִ�.
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        &inputLayout
    );
}

void InputLayout::SetIA()
{
    DC->IASetInputLayout(inputLayout);
}
