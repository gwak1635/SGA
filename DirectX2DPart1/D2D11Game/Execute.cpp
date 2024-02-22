#include "stdafx.h"
#include "Execute.h"
#include "Graphics.h"

#define NUMOFVERTEX 4
#define NUMOFINDEX 6

Execute::Execute()
{
	graphics = new Graphics();//�ҿ���ȯ ��¼����¼��: �𸥴�! ��� �߰��ض�!
	graphics->Initialize();
	graphics->CreateBackBuffer(static_cast<uint>(Settings::Get().GetWidth()), static_cast<uint>(Settings::Get().GetHeight()));

	//vertex Data
	{
		vertices = new vertexColor[NUMOFVERTEX];
		vertices[0].position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f); //0
		vertices[0].color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		vertices[1].position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);  //1
		vertices[1].color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

		vertices[2].position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);  //2
		vertices[2].color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

		vertices[3].position = D3DXVECTOR3(0.5f, 0.5f, 0.0f);	//3
		vertices[3].color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		//���� ���̴� ����: ����ȭ�� �Ͼ(������ �ϳ��� �ھ� �ϳ�?)
		//�簢���� ������ �ﰢ�� 2���� �̾�ٿ��� �� (�ð����)
		//�簢���� ũ�Ⱑ 1�ε� 200px �̻��̶��?(���ؽ� ���̴����� ��ǥ��ȯ�� ���ؼ� �׷�)
		//������ ��ȣ�� �ű��, ��� �������� �������� �ε����ϸ� ���� 4���� �ᵵ ���� ������?
		//�׷��� �ε��� ���۸� ��
	}
	//vertex Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = sizeof(vertexColor) * NUMOFVERTEX;

		//CPU �����͸� GPU�� �����ϱ�
		D3D11_SUBRESOURCE_DATA sub_data;
		ZeroMemory(&sub_data, sizeof(D3D11_SUBRESOURCE_DATA));
		sub_data.pSysMem = vertices;

		auto hr = graphics->GetDevice()->CreateBuffer(&desc, &sub_data, &vertex_buffer);
		assert(SUCCEEDED(hr));
	}
	//Index Data
	{
		indices = new uint[NUMOFINDEX]{ 0,1,2,2,1,3 };//TODO ���� �þ�� �ٲٱ�

	}
	//Index Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = sizeof(uint) * NUMOFINDEX;//TODO ���� �þ�� �ٲٱ�(2)

		D3D11_SUBRESOURCE_DATA sub_data;
		ZeroMemory(&sub_data, sizeof(D3D11_SUBRESOURCE_DATA));
		sub_data.pSysMem = indices;

		auto hr = graphics->GetDevice()->CreateBuffer(&desc, &sub_data, &index_buffer);
		assert(SUCCEEDED(hr));
	}
	//Vertex Shader
	{
		auto hr = D3DX11CompileFromFileA(
			"Color.hlsl",
			nullptr,
			nullptr,
			"VS",
			"vs_5_0",
			0,
			0,
			nullptr,
			&vs_blob,
			nullptr,
			nullptr
		);
		assert(SUCCEEDED(hr));

		hr = graphics->GetDevice()->CreateVertexShader(vs_blob->GetBufferPointer(),vs_blob->GetBufferSize(), nullptr, &vertex_shader);
		assert(SUCCEEDED(hr));
	}
	//Input Layout
	{
		D3D11_INPUT_ELEMENT_DESC layout_desc[]{
			{ "POSITION",0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		//����Ʈ�ڵ� �������� ���
		auto hr = graphics->GetDevice()->CreateInputLayout(layout_desc, 2, vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), &input_layout);
		assert(SUCCEEDED(hr));
	}
	//Pixel Shader
	{
		//hlsl ������
		auto hr = D3DX11CompileFromFileA(
			"Color.hlsl",
			nullptr,
			nullptr,
			"PS",
			"ps_5_0",
			0,
			0,
			nullptr,
			&ps_blob,
			nullptr,
			nullptr
		);
		assert(SUCCEEDED(hr));

		hr = graphics->GetDevice()->CreatePixelShader(ps_blob->GetBufferPointer(), ps_blob->GetBufferSize(), nullptr, &pixel_shader);
		assert(SUCCEEDED(hr));
	}
	//Create world view projection
	{
		D3DXMatrixIdentity(&world);//������ķ� ����� �Լ�
		D3DXMatrixIdentity(&view);
		D3DXMatrixIdentity(&projection);

		
		D3DXMatrixLookAtLH(&view,&D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 1), &D3DXVECTOR3(0, 1, 0));
		D3DXMatrixOrthoLH(&projection, Settings::Get().GetWidth(), Settings::Get().GetHeight(),0,1);

		//ortho:����(�յڰŸ� ���� ���� ������)
		//perspec:����(�յڰŸ� ������)[����ü]

		std::cout << "View Matrix" << std::endl;
		std::cout << view._11 << " " << view._12 << " " << view._13 << " " << view._14 << std::endl;
		std::cout << view._21 << " " << view._22 << " " << view._23 << " " << view._24 << std::endl;
		std::cout << view._31 << " " << view._32 << " " << view._33 << " " << view._34 << std::endl;
		std::cout << view._41 << " " << view._42 << " " << view._43 << " " << view._44 << std::endl;

		std::cout << std::endl;

		std::cout << "Projection Matrix" << std::endl;
		std::cout << projection._11 << " " << projection._12 << " " << projection._13 << " " << projection._14 << std::endl;
		std::cout << projection._21 << " " << projection._22 << " " << projection._23 << " " << projection._24 << std::endl;
		std::cout << projection._31 << " " << projection._32 << " " << projection._33 << " " << projection._34 << std::endl;
		std::cout << projection._41 << " " << projection._42 << " " << projection._43 << " " << projection._44 << std::endl;
	}
}

Execute::~Execute()
{
	SAFE_RELEASE(pixel_shader);
	SAFE_RELEASE(ps_blob);

	SAFE_RELEASE(input_layout);

	SAFE_RELEASE(vertex_shader);
	SAFE_RELEASE(vs_blob);

	SAFE_DELETE_ARRAY(indices);
	SAFE_RELEASE(index_buffer);

	SAFE_RELEASE(vertex_buffer);
	SAFE_DELETE_ARRAY(vertices);

	SAFE_DELETE(graphics);
}

void Execute::Update()
{
}

void Execute::Render()
{
	uint stride = sizeof(vertexColor);//���� �ϳ��� ũ��(����)
	uint offset = 0;//������

	graphics->Begin();
	{
		//IA : Input Assembler stage
		graphics->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
		graphics->GetDeviceContext()->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);
		graphics->GetDeviceContext()->IASetInputLayout(input_layout);
		//������ ��� ������ ����? �ﰢ������ �Ұ���!
		graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
		//VS : vertex Shader
		graphics->GetDeviceContext()->VSSetShader(vertex_shader, nullptr, 0);//������ ������ŭ ȣ���

		//PS
		graphics->GetDeviceContext()->PSSetShader(pixel_shader, nullptr, 0);

		//������������ �� ���ƴٸ� Draw�ϱ�
		graphics->GetDeviceContext()->DrawIndexed(NUMOFINDEX, 0, 0);//TODO ���� �þ�� �ٲٱ�

	}
	graphics->End();
}
