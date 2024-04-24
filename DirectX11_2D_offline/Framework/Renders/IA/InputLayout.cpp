#include "Framework.h"
#include "InputLayout.h"

InputLayout::~InputLayout()
{
    SAFE_RELEASE(il);
}

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC* descs, UINT count, ID3DBlob* blob)
{
    // �ŰԺ����� �ϳ��� �������
    if (!descs || !count || !blob)
        CHECK(false); // ���α׷� ���� ����

    HRESULT hr = DEVICE->CreateInputLayout
    (
        descs,                      // ���赵
        count,                      // ���赵 ����
        blob->GetBufferPointer(),   // VertexBuffer�� ��ġ
        blob->GetBufferSize(),      // VertexBuffer�� ũ��
        &il
    );
    CHECK(hr);
}

void InputLayout::SetIA()
{
    DC->IASetInputLayout(il);
}
