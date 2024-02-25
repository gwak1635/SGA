#include "stdafx.h"
#include "Execute.h"
#include "Graphics.h"

#define NUMOFVERTEX 4
#define NUMOFINDEX 6

Execute::Execute()
{
	graphics = new Graphics();//불완전환 어쩌구저쩌구: 모른다! 헤더 추가해라!
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
		//색이 섞이는 이유: 병렬화가 일어남(꼭지점 하나당 코어 하나?)
		//사각형을 쓰려면 삼각형 2개를 이어붙여야 함 (시계방향)
		//사각형의 크기가 1인데 200px 이상이라고?(버텍스 셰이더에서 좌표변환을 안해서 그럼)
		//정점에 번호를 매기고, 어떻게 점ㅇ들을 이을지만 인덱싱하면 점을 4개만 써도 되지 않을까?
		//그래서 인덱스 버퍼를 씀
	}
	//vertex Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = sizeof(vertexColor) * NUMOFVERTEX;

		//CPU 데이터를 GPU에 연결하기
		D3D11_SUBRESOURCE_DATA sub_data;
		ZeroMemory(&sub_data, sizeof(D3D11_SUBRESOURCE_DATA));
		sub_data.pSysMem = vertices;

		auto hr = graphics->GetDevice()->CreateBuffer(&desc, &sub_data, &vertex_buffer);
		assert(SUCCEEDED(hr));
	}
	//Index Data
	{
		indices = new uint[NUMOFINDEX]{ 0,1,2,2,1,3 };//TODO 정점 늘어나면 바꾸기

	}
	//Index Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = sizeof(uint) * NUMOFINDEX;//TODO 정점 늘어나면 바꾸기(2)

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
		//바이트코드 나왔으면 블롭
		auto hr = graphics->GetDevice()->CreateInputLayout(layout_desc, 2, vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), &input_layout);
		assert(SUCCEEDED(hr));
	}
	//Pixel Shader
	{
		//hlsl 컴파일
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
		D3DXMatrixIdentity(&world);//단위행렬로 만드는 함수
		D3DXMatrixIdentity(&view);
		D3DXMatrixIdentity(&projection);

		
		D3DXMatrixLookAtLH(&view,&D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 1), &D3DXVECTOR3(0, 1, 0));
		D3DXMatrixOrthoLH(&projection, Settings::Get().GetWidth(), Settings::Get().GetHeight(),0,1);
		
		//얘는 Y축이 아래! (윈도우 좌표)
		//D3DXMatrixOrthoOffCenterLH(&view, 0, Settings::Get().GetWidth(),  0, Settings::Get().GetHeight(), 0, 1);

		//ortho:직교(앞뒤거리 관계 없이 보여줌)
		//perspec:원근(앞뒤거리 느껴짐)[절두체]

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
		std::cout << std::endl;

		//world
		D3DXMATRIX S;
		D3DXMatrixScaling(&S, 100, 100, 1);//스케일 세팅 시 1 이상의 값 (크기 변경) //이전 데이터 모두 고정
		
		std::cout << "Scale Matrix" << std::endl;
		std::cout << S._11 << " " << S._12 << " " << S._13 << " " << S._14 << std::endl;
		std::cout << S._21 << " " << S._22 << " " << S._23 << " " << S._24 << std::endl;
		std::cout << S._31 << " " << S._32 << " " << S._33 << " " << S._34 << std::endl;
		std::cout << S._41 << " " << S._42 << " " << S._43 << " " << S._44 << std::endl;
		std::cout << std::endl;

		D3DXMATRIX T;
		D3DXMatrixTranslation(&T, 100, 100, 0);
		std::cout << "Translation Matrix" << std::endl;
		std::cout << T._11 << " " << T._12 << " " << T._13 << " " << T._14 << std::endl;
		std::cout << T._21 << " " << T._22 << " " << T._23 << " " << T._24 << std::endl;
		std::cout << T._31 << " " << T._32 << " " << T._33 << " " << T._34 << std::endl;
		std::cout << T._41 << " " << T._42 << " " << T._43 << " " << T._44 << std::endl;
		std::cout << std::endl;

		D3DXMATRIX R;
		D3DXMatrixRotationZ(&R, static_cast<float>D3DXToRadian(45));//얘 라디안이다!
		std::cout << "Rotation Matrix" << std::endl;
		std::cout << R._11 << " " << R._12 << " " << R._13 << " " << R._14 << std::endl;
		std::cout << R._21 << " " << R._22 << " " << R._23 << " " << R._24 << std::endl;
		std::cout << R._31 << " " << R._32 << " " << R._33 << " " << R._34 << std::endl;
		std::cout << R._41 << " " << R._42 << " " << R._43 << " " << R._44 << std::endl;
		std::cout << std::endl;

		//스 자(자전) 이 공(공전) 부(부모)
		//S R T R P
		world = S */* R * */T;
		//행렬엔 교환법칙 안된다잉~
	}
	//Create constant buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DYNAMIC; //cpu:write gpu:read
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.ByteWidth = sizeof(TRANSFORM_DATA);
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//CPU의 상태
		auto hr = graphics->GetDevice()->CreateBuffer(&desc, nullptr, &gpu_buffer);
		assert(SUCCEEDED(hr));
	}
	//Create Rasterizer State
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
		desc.FillMode = D3D11_FILL_SOLID;
		desc.CullMode = D3D11_CULL_BACK;//어떤 면을 그리지 않게 할 건지!(뒷면 가리개용)
		//cliping: 그리고 나서 잘라내기!
		desc.FrontCounterClockwise = false;//앞면 뒷면 판단하게 하는 놈! [시계방향: 앞면, 반시계방향:뒷면]
		//왼손 좌표계에서는 시계방향을 쓰는 게 계산할 때 편하다!

		auto hr = graphics->GetDevice()->CreateRasterizerState(&desc, &rasterizer_state);
		assert(SUCCEEDED(hr));
	}
}

Execute::~Execute()
{
	SAFE_RELEASE(rasterizer_state);

	SAFE_RELEASE(gpu_buffer);
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
	//D3DXMATRIX = 행우선 행렬
	//gpu- shader = matrix = 열우선 행렬

	//D3DXMATRIX P;
	//D3DXMatrixTranslation(&P,1,0,0);
	//world *= P;

	//전치행렬 - Transpose
	D3DXMatrixTranspose(&cpu_buffer.world, &world);
	D3DXMatrixTranspose(&cpu_buffer.view , &view);
	D3DXMatrixTranspose(&cpu_buffer.projection , &projection);

	//TODO 항상주의 
	D3D11_MAPPED_SUBRESOURCE mapped_subresource;//중개 개념 (상수 버퍼 자원 갱신 가능)
	graphics->GetDeviceContext()->Map(
		gpu_buffer,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&mapped_subresource
	);//파이프라인 건들땐 디바이스컨텍스트

	memcpy(mapped_subresource.pData, &cpu_buffer, sizeof(TRANSFORM_DATA));

	graphics->GetDeviceContext()->Unmap(gpu_buffer, 0);
}

void Execute::Render()
{
	uint stride = sizeof(vertexColor);//정점 하나의 크기(보폭)
	uint offset = 0;//시작점

	graphics->Begin();
	{
		//IA : Input Assembler stage
		graphics->GetDeviceContext()->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
		graphics->GetDeviceContext()->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R32_UINT, 0);
		graphics->GetDeviceContext()->IASetInputLayout(input_layout);
		//정점을 어떻게 연결할 거임? 삼각형으로 할거임!
		graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
		//VS : vertex Shader
		graphics->GetDeviceContext()->VSSetShader(vertex_shader, nullptr, 0);//정점의 개수만큼 호출됨
		graphics->GetDeviceContext()->VSSetConstantBuffers(0, 1, &gpu_buffer);

		//RS
		graphics->GetDeviceContext()->RSSetState(rasterizer_state);

		//PS
		graphics->GetDeviceContext()->PSSetShader(pixel_shader, nullptr, 0);

		//파이프라인을 다 거쳤다면 Draw하기
		graphics->GetDeviceContext()->DrawIndexed(NUMOFINDEX, 0, 0);//TODO 정점 늘어나면 바꾸기

	}
	graphics->End();
}
