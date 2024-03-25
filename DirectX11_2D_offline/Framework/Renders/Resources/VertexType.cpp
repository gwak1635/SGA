#include "Framework.h"
#include "VertexType.h"

/*
    D3D11_INPUT_ELEMENT_DESC 의 내부 구조
    - SemanticName              
    : 정점 데이터의 의미를 나타내는 문구 // 이름
    - SemanticIndex
    : 위 이름이 중복되는 경우 구분하기 위한 인덱스 값 // 번호
    - Format
    : 데이터 형식 // 해석법
    - InputSlot
    : 입력 슬롯의 인덱스 // 대부분 0
    - AlignedByteOffset
    : 정점 데이터의 바이트 단위 간격 // 0 = 기본값, 자동 계산
    - InputSlotClass
    : 사용되는 데이터의 형식 // 버텍스 정보니까 버텍스 데이터
    - InstanceDataStepRate
    : 인스턴스마다 데이터를 읽어들이는데 사용할 스템 레이트 값 // 대부분 0
*/

D3D11_INPUT_ELEMENT_DESC VertexColor::descs[]
{
    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, // 정점의 위치
    0,                              D3D11_INPUT_PER_VERTEX_DATA, 0},

    {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, // 정점의 색상
    D3D11_APPEND_ALIGNED_ELEMENT,   D3D11_INPUT_PER_VERTEX_DATA, 0}
};

D3D11_INPUT_ELEMENT_DESC VertexTexture::descs[]
{
    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, // 정점의 위치
    0,                              D3D11_INPUT_PER_VERTEX_DATA, 0},

    {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,    // 그림의 좌표
    D3D11_APPEND_ALIGNED_ELEMENT,   D3D11_INPUT_PER_VERTEX_DATA, 0}
};