#include "stdafx.h"
#include "03_ShaderDemo.h"

void ShaderDemo::Init()
{
	st = new ShaderTexture(
		{ 640,360,0 }, { 500,500,1 }, 0.0f,
		TexturePath + L"penguin.png");
}

void ShaderDemo::Destroy()
{
	SAFE_DELETE(st);
}

void ShaderDemo::Update()
{
	st->Update();
}

void ShaderDemo::Render()
{
	st->Render();
}

void ShaderDemo::PostRender()
{
}

void ShaderDemo::GUI()
{
	st->GUI();
}
