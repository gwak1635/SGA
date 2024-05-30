#include "stdafx.h"
#include "02_TextureDemo.h"

void TextureDemo::Init()
{
    tr = new TextureRect({ WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0 },
        { 250.0f,100.0f,1 }, 0, TexturePath + L"Sample2.jpg");
}

void TextureDemo::Destroy()
{
    SAFE_DELETE(tr);
}

void TextureDemo::Update()
{
    tr->Update();
}

void TextureDemo::Render()
{
    tr->Render();
}

void TextureDemo::PostRender()
{
}

void TextureDemo::GUI()
{
}
