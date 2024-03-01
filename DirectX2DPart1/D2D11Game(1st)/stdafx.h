#pragma once

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")//�� �ٸ� �ܼ�â�� ����
#endif // _DEBUG


//Window
#include <Windows.h>
#include <assert.h>//�ܾ�, ����� ��忡���� �۵�

//STL
#include <iostream>
#include <vector>

//DirectX
#include <d3dcompiler.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>

//���̺귯�� ���� �ڵ� (�߰� ���Ӽ�)
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dcompiler.lib")

typedef unsigned int uint;

//Macro Function
#define SAFE_DELETE(p)		 { if(p) {delete(p);(p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) { if(p) {delete[](p);(p)=nullptr;}}
#define SAFE_RELEASE(p)		 { if(p) {p->Release();(p)=nullptr;}}

//Framework
#include "Settings.h"