#include "stdafx.h"
#include "Program.h"

#include "Systems/Window.h"

void Program::Init()
{
	// Create VPBuffer
	{
		vpb = new VPBuffer();

		// View ��� ����
		{
			D3DXMatrixLookAtLH
			(
				&view,				// ī�޶�
				&Vector3(0, 0, 0),	// ī�޶� ��ġ
				&Vector3(0, 0, 1),	// �þ� ����
				&Vector3(0, 1, 0)	// ī�޶� �� ����
			);

			vpb->SetView(view);
		}

		// projection ��� ����
		{
			D3DXMatrixOrthoOffCenterLH
			(
				&proj,
				0.0f,				// ���� �� // x��ǥ �ּҰ�
				(float)WinMaxWidth, // ������ ��
				0.0f,				// �Ʒ��� ��
				(float)WinMaxHeight,// ���� ��
				0,
				1
			);

			vpb->SetProj(proj);
		}
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
	for (IObject* obj : objs)
		obj->Update();
}

void Program::Render()
{


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
	desc.AppName = L"D2DGame";
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
