#include "stdafx.h"
#include "Program.h"

#include "Systems/Window.h"

#include "Demos/00_RectDemo.h"
#include "Demos/01_CollisionDemo.h"
#include "Demos/02_TextureDemo.h"
#include "Demos/03_ShadedDemo.h"
#include "Demos/04_AnimDemo.h"
#include "Demos/P00_RhythmGame.h"

void Program::Init()
{
	// 다이렉트 싱글톤 세팅
	States::Create();

	// 카메라 싱글톤 세팅
	Camera::Create(); 

	// Demo 세팅
	{
		// Push(new RectDemo);
		// Push(new CollisionDemo);
		// Push(new TextureDemo);
		Push(new RhythmGame);
	}
}

void Program::Destroy()
{
	for (IObject* obj : objs)
	{
		obj->Destroy();
		SAFE_DELETE(obj);
	}
}

void Program::Update()
{
	Camera::Get()->Update();

	for (IObject* obj : objs)
		obj->Update();
}

void Program::Render()
{
	Camera::Get()->UpdateView();
	Camera::Get()->Render();

	for (IObject* obj : objs)
		obj->Render();
}

void Program::PostRender()
{
	for (IObject* obj : objs)
		obj->PostRender();
}

void Program::GUI()
{
	for (IObject* obj : objs)
	{
		obj->GUI();
	}
}

void Program::Push(IObject* obj)
{
	objs.push_back(obj);
	obj->Init();
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	srand((UINT)time(NULL));

	DXDesc desc;
	desc.AppName = L"D2DGame"; // 창 이름
	desc.instance = instance;
	desc.handle = NULL;
	desc.width = WinMaxWidth;
	desc.height = WinMaxHeight;

	Program* program = new Program();
	Window* window = new Window(desc);
	WPARAM wParam = window->Run(program);

	SAFE_DELETE(window);
	SAFE_DELETE(program);

	return wParam;

}
