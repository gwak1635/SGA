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
	//���� ������� ������ ���߿� �����ֱ�
	//��۸� ������(�����Ͱ� ������ �޸𸮸� ����Ű�� �ִ� ���)
}

void Graphics::Initialize()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	desc.BufferDesc.Width = 0;
	desc.BufferDesc.Height = 0;
	desc.BufferDesc.RefreshRate.Numerator = 60;//ȭ�� �ֻ����� ���� TODO �ֻ��� ����
	desc.BufferDesc.RefreshRate.Denominator = 1;//ȭ�� �ֻ����� �и�
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//0~255�� �÷�
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferCount = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//�� �� ���ø��Ұų�
	desc.SampleDesc.Count = 1;
	//���ø��� ���ذ�
	desc.SampleDesc.Quality = 0;
	desc.OutputWindow = Settings::Get().GetWindowHandle();
	desc.Windowed = TRUE;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;//���ҵ� �������� ó�����

	//��Ƽ �ٸ���� ���
	//SSAA:��ü�� �÷ȴ� �ٿ��� ����� ����(�� ������ ����)
	//MSAA:�Ϻ�(�밢��)�� �÷ȴ� �ٿ��� ����� ���� �����ϳ� ������ ���

	std::vector<D3D_FEATURE_LEVEL> feature_levels //���� ������ �켱����
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	auto hr = D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,//�ϵ���� ���� ��밡������
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
	auto hr = swap_chain->ResizeBuffers(//�������� ���� ���� 0����!
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
		__uuidof(ID3D11Texture2D),//IID_ID3D11Texture2D //UUID GUID���� ���� ���� 16����Ʈ ������
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

	SAFE_RELEASE(back_buffer);//���� �����̱� ������ ���� �� �����ֱ�!
}

void Graphics::Begin()
{
	//ID3D11RenderTargetView* rtvs[] = {render_target_view};
	//���� ����Ÿ�ٺ信 rtvs�־���ϴµ� �ϳ�¥�� ������ �ּҵ� �ᱹ �迭�� �ּ��ݾ�?
	device_context->OMSetRenderTargets(1,&render_target_view, nullptr);
	device_context->RSSetViewports(1, &viewport);
	device_context->ClearRenderTargetView(render_target_view, clear_color);
}

void Graphics::End()
{
	auto hr = swap_chain->Present(1,0);
	assert(SUCCEEDED(hr));
}

//ID3D11Resource���� ����(�ڷ� 1��)�� �ؽ�ó(1D,2D,3D)�� �ִ�
//Resource View :�ؽ��ĸ� Ư��ȭ
//- ID3D11RenderTargetView, ���̵帮�ҽ���, �������ٽǺ�, �������׼�����