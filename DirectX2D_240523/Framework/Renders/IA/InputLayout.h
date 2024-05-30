#pragma once

/*
InputLayout
- ���ؽ� ������ ������ ������ ����
- ���ؽ� �������� �� ���(��ġ, ����, �׸� ��ǥ ��)�� ����, ũ��, ���� ���� ����
- IA �ܰ迡�� VS�� �����͸� �����ϱ� ���� ���� �����͸� �ް� �ش� �����͸�
�ǹٸ��� �ؼ��ϱ� ���� ���
*/

class InputLayout
{
public:
    ~InputLayout();
    
    // Renders/Resource�� �ִ� VertexType�� �ִ´�.
    void Create(D3D11_INPUT_ELEMENT_DESC* descs, uint count,
        ID3DBlob* blob);

    void SetIA();

private:
    ID3D11InputLayout* inputLayout = nullptr;
};