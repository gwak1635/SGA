#pragma once

/*
InputLayout
- 버텍스 버퍼의 데이터 구조를 정의
- 버텍스 데이터의 각 요소(위치, 색상, 그림 좌표 등)의 형식, 크기, 순서 등을 지정
- IA 단계에서 VS로 데이터를 전달하기 전에 정점 데이터를 받고 해당 데이터를
옳바르게 해석하기 위해 사용
*/

class InputLayout
{
public:
    ~InputLayout();
    
    // Renders/Resource에 있는 VertexType을 넣는다.
    void Create(D3D11_INPUT_ELEMENT_DESC* descs, uint count,
        ID3DBlob* blob);

    void SetIA();

private:
    ID3D11InputLayout* inputLayout = nullptr;
};