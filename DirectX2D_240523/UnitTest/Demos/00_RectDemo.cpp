#include "stdafx.h" 
#include "00_RectDemo.h"

// UnitTest ������Ʈ�� ����ϴ� ���� �������
void RectDemo::Init()
{
    // 2D������ ��ġ�� z���� 0�̰� ũ���� z���� 1�̾ ī�޶� ������.
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
