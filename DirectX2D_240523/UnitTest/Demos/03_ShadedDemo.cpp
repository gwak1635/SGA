#include "stdafx.h"
#include "03_ShadedDemo.h"

void ShadedDemo::Init()
{
    st = new ShadedTexture(
        { WinMaxWidth * 0.3f, WinMaxHeight * 0.3f, 0 },
        { 300.0f, 200.0f,1 }, 0, 
        TexturePath + L"TakeALook.webp");

    at = new AlphaTexture(
        { WinMaxWidth * 0.6f, WinMaxHeight * 0.6f, 0 },
        { 300.0f, 200.0f,1 }, 0,
        TexturePath + L"TakeALook.webp");
}

void ShadedDemo::Destroy()
{
    SAFE_DELETE(at);
    SAFE_DELETE(st);
}

void ShadedDemo::Update()
{
    st->Update();
    at->Update();
}

void ShadedDemo::Render()
{
    st->Render();
    at->Render();
}

void ShadedDemo::PostRender()
{
}

void ShadedDemo::GUI()
{
    st->GUI();
    at->GUI();
}
