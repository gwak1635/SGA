#pragma once

class Graphics final//���̸�... ���� �� �����ϴ�.
{
public:

	Graphics();
	~Graphics();

	void Initialize();
	void CreateBackBuffer(const uint& width, const uint & height);

	auto GetDevice() -> ID3D11Device* { return device; }
	auto GetDeviceContext() -> ID3D11DeviceContext* { return device_context; }
	//��ȯ ���� �˷��ֱ�

	void Begin();
	void End();

private:
	//I: COM Interface ��ǻ�Ϳ��� ��û�ϸ� �ڵ����� ���� �Ҵ��� �ݴϴ�
	//new ��û�ؾ��ϰ� delete ��û�ؾ���(���� �� �� ����)
	//release�� ����

	//���ҽ� ����(���⼭�� ����Ÿ�ٺ�)
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* device_context = nullptr; //hdc�� dc��(���������ο� ����)
	//DXGI : ��ī �����縶�� ���(��ġ)�� �ٸ��� ������ �ڵ����� ��ġ�� �Ҵ��� ��
	//����ü��: �� ���� ���۸� �����ư��� ��������, ������, ������ ���� ����
	IDXGISwapChain* swap_chain = nullptr;
	//����ü�ο� ���ӵǴ� ����(��ȭ��)
	ID3D11RenderTargetView* render_target_view = nullptr;
	//����Ʈ�� Ŭ�����÷��� COM Interface�� �ƴ� (��ü��)[�׷��� �����Ͱ� �ƴ�]
	//����Ʈ: ������ ���� ����
	D3D11_VIEWPORT viewport = { 0 };
	//���� ǥ���Ҽ� ����(rgba)
	//����ȭ: 0~255�� 0~1�� ����
	//����� ��?
	D3DXCOLOR clear_color = 0xff555566;
};
//��� C++(11)���� ��忡�� �ʱ�ȭ ����

//������ ����������
//IA-VS-RS-PS-OM

//DirectX - API
//OpenGL PC, ����� ��� ���α׷��� ����
//�� ���̷�Ʈ X�� ����? 1. �����쿡�� �� ����, 2. OpenGL�� �Թ� ���̵�(�پ��� �÷����� ����)

//GPU(�ʵ� 3-4õ��) - CPU (���л� 8��(8�ھ�))