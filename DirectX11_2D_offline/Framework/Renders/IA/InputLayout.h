#pragma once

// CPU�� GPU���� ������ �����͸� �ǳ��ٶ�
// �ش� ������ �������� �����͸� �ǳ��� Ŭ����
class InputLayout
{
public:
    ~InputLayout();

    void Create(D3D11_INPUT_ELEMENT_DESC* descs, UINT count,
        ID3DBlob* blob);

    void SetIA();
private:
    ID3D11InputLayout* il = nullptr;
};