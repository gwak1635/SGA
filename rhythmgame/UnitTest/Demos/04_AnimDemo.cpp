#include "stdafx.h"
#include "04_AnimDemo.h"

void AnimDemo::Init()
{
	ar = new AnimationRect({ WinMaxWidth * 0.5f,WinMaxHeight * 0.5f,0 }, { 500,500,1 });

	Sounds::Get()->AddSound("BGM", SoundPath + L"bgm.wav", true);

	Sounds::Get()->Play("BGM");
}

void AnimDemo::Destroy()
{
	SAFE_DELETE(ar);
}

void AnimDemo::Update()
{
	ar->Update();
}

void AnimDemo::Render()
{
	ar->Render();
}

void AnimDemo::PostRender()
{
}

void AnimDemo::GUI()
{
}
