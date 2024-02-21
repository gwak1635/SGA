#include"stdafx.h"
#include"Graphics.h"

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
	SAFE_RELEASE(render_target_view);
	SAFE_RELEASE(swap_chain);
	SAFE_RELEASE(device_context);
	SAFE_RELEASE(device);
	//먼저 만들어진 변수는 나중에 지워주기
	//댕글링 포인터(포인터가 해제된 메모리를 가리키고 있는 경우)
}

void Graphics::Initialize()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	desc.BufferDesc.Width = 0;
	desc.BufferDesc.Height = 0;
	desc.BufferDesc.RefreshRate.Numerator = 60;//화면 주사율의 분자 TODO 주사율 조정
	desc.BufferDesc.RefreshRate.Denominator = 1;//화면 주사율의 분모
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//0~255의 컬러
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferCount = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//몇 번 샘플링할거냐
	desc.SampleDesc.Count = 1;
	//샘플링의 수준값
	desc.SampleDesc.Quality = 0;
	desc.OutputWindow = Settings::Get().GetWindowHandle();
	desc.Windowed = TRUE;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;//스왑된 데이터의 처리방식

	//안티 앨리어싱 방법
	//SSAA:전체를 늘렸다 줄였다 비용이 강함(잘 쓰이지 않음)
	//MSAA:일부(대각선)을 늘렸다 줄였다 비용이 비교적 저렴하나 여전히 비쌈

	std::vector<D3D_FEATURE_LEVEL> feature_levels //지원 레벨의 우선순위
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	auto hr = D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,//하드웨어 가속 사용가능케함
		nullptr,
		0,
		feature_levels.data(),
		feature_levels.size(),
		D3D11_SDK_VERSION,
		&desc,
		&swap_chain,
		&device,
		nullptr,
		&device_context
	);
	assert(SUCCEEDED(hr));
}

void Graphics::CreateBackBuffer(const uint& width, const uint& height)
{
	auto hr = swap_chain->ResizeBuffers(//변경하지 않을 값은 0으로!
		0,
		width,
		height,
		DXGI_FORMAT_UNKNOWN,
		0
	);
	assert(SUCCEEDED(hr));

	ID3D11Texture2D* back_buffer = nullptr;

	hr = swap_chain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),//IID_ID3D11Texture2D //UUID GUID같은 개념 공용 16바이트 데이터
		reinterpret_cast<void**>(&back_buffer)
	);
	assert(SUCCEEDED(hr));

	hr = device->CreateRenderTargetView(
		back_buffer,
		nullptr,
		&render_target_view
	);
	assert(SUCCEEDED(hr));

	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width  = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	SAFE_RELEASE(back_buffer);//지역 변수이기 때문에 끝날 때 지워주기!
}

void Graphics::Begin()
{
	//ID3D11RenderTargetView* rtvs[] = {render_target_view};
	//원래 렌더타겟뷰에 rtvs넣어야하는데 하나짜리 변수의 주소도 결국 배열의 주소잖애?
	device_context->OMSetRenderTargets(1,&render_target_view, nullptr);
	device_context->RSSetViewports(1, &viewport);
	device_context->ClearRenderTargetView(render_target_view, clear_color);
}

void Graphics::End()
{
	auto hr = swap_chain->Present(1,0);
	assert(SUCCEEDED(hr));
}

//ID3D11Resource에는 버퍼(자료 1개)와 텍스처(1D,2D,3D)가 있다
//Resource View :텍스쳐를 특수화
//- ID3D11RenderTargetView, 셰이드리소스뷰, 뎁스스텐실뷰, 언오더드액세스뷰