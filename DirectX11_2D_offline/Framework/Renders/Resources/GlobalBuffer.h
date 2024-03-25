#pragma once

#include "Framework.h"

// GlobalBuffer
// WVP = 월드(공간) * 뷰(카메라) * 프로젝션(투영법)
/*
WVP는 3D공간과 모델을 2D 스크린 좌표로 변환하는 과정 중 하나
모니터는 평면이기 때문에 3D게임도 스크린 좌표로 변환하는 과정이 필요하다.

World // 공간
- 모델의 정점을 글로벌 좌표계에서 지역 좌표계로 변환하는 것을 의미한다.
- 모델의 위치, 회전, 크기를 조정한다.

View // 카메라
- 카메라의 위치, 방향, 시야를 나타내는 행렬
- 글로벌 좌표계에서 카메라가 바라보는 방향을 나타낸다. // 실제 카메라 객체있는건 X
- 카메라의 위치와 방향을 변경시켜준다.

proejction // 투영법
- 3D공간을 2D스크린 자표로 변환시키는 방법
- 시야각, 종횡비, 크리핑 평면(단면도 깍기)등을 고려하여 실행
*/

// WorldBuffer
class WorldBuffer : public ShaderBuffer
{
public:

    WorldBuffer() : ShaderBuffer(&data, sizeof(Data))
    {
        // 행렬 초기화
        // 해당 행렬 데이터가 전부 0이 됨
        D3DXMatrixIdentity(&data.world);
    }

    void SetWorld(Matrix world)
    {
        // 전치 행렬
        // 열과 행을 서로 교환 
        // world의 행이 데이터 월드.열, world의 열이 데이터.월드의 행
        D3DXMatrixTranspose(&data.world, &world);
    }

    // CPU에 넘길 데이터들의 종류
    // 메모리 할당량의 합이 16의 배수의 크기를 할당해 주는것이 좋음
    // Ex) int(4Byte) 4개 / char(1Byte) 32개
    struct Data
    {
        // float이 4개 있는 구조체
        Matrix world;
    };
private:
    Data data;
};


// VPBuffer
class VPBuffer : public ShaderBuffer
{
public:

    VPBuffer() : ShaderBuffer(&data, sizeof(Data))
    {
        D3DXMatrixIdentity(&data.view);
        D3DXMatrixIdentity(&data.projection);
    }

    void SetView(Matrix view)
    {
        D3DXMatrixTranspose(&data.view, &view);
    }

    void SetProj(Matrix projection)
    {
        D3DXMatrixTranspose(&data.projection, &projection);
    }

    struct Data
    {
        Matrix view;        // 카메라
        Matrix projection;  // 투영법
    };
private:
    Data data;
};
