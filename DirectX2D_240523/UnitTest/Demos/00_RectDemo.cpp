#include "stdafx.h" 
#include "00_RectDemo.h"

// UnitTest 프로젝트가 사용하는 공용 헤더파일
void RectDemo::Init()
{
    // 2D에서는 위치의 z값은 0이고 크기의 z값은 1이어여 카메라에 잡힌다.
    rect = new Rect(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0),
        Vector3(100, 100, 1), 0);
}

void RectDemo::Destroy()
{
    SAFE_DELETE(rect);
}

void RectDemo::Update()
{
    rect->Update();
}

void RectDemo::Render()
{
    rect->Render();
}

void RectDemo::PostRender()
{
}

void RectDemo::GUI()
{
    rect->GUI();
}
