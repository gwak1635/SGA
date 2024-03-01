#pragma once

class Graphics final//아이를... 가질 수 없습니다.
{
public:

	Graphics();
	~Graphics();

	void Initialize();
	void CreateBackBuffer(const uint& width, const uint & height);

	auto GetDevice() -> ID3D11Device* { return device; }
	auto GetDeviceContext() -> ID3D11DeviceContext* { return device_context; }
	//반환 값을 알려주기

	void Begin();
	void End();

private:
	//I: COM Interface 컴퓨터에게 요청하면 자동으로 만들어서 할당해 줍니다
	//new 요청해야하고 delete 요청해야함(직접 할 수 없음)
	//release로 해제

	//리소스 생성(여기서는 렌더타겟뷰)
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* device_context = nullptr; //hdc의 dc임(파이프라인에 생성)
	//DXGI : 글카 제조사마다 방식(위치)이 다르기 때문에 자동으로 위치를 할당해 줌
	//스왑체인: 두 개의 버퍼를 번갈아가며 렌더링해, 깜빡임, 찢어짐 현상 방지
	IDXGISwapChain* swap_chain = nullptr;
	//스왑체인에 종속되는 버퍼(도화지)
	ID3D11RenderTargetView* render_target_view = nullptr;
	//뷰포트와 클리어컬러는 COM Interface가 아님 (객체들)[그래서 포인터가 아님]
	//뷰포트: 보여질 영역 결정
	D3D11_VIEWPORT viewport = { 0 };
	//색을 표현할수 있음(rgba)
	//정규화: 0~255를 0~1로 만듦
	//지우는 색?
	D3DXCOLOR clear_color = 0xff555566;
};
//모던 C++(11)부터 헤드에서 초기화 가능

//렌더링 파이프라인
//IA-VS-RS-PS-OM

//DirectX - API
//OpenGL PC, 모바일 등에서 프로그래밍 가능
//왜 다이렉트 X를 배우냐? 1. 윈도우에서 더 편함, 2. OpenGL의 입문 난이도(다양한 플랫폼의 단점)

//GPU(초딩 3-4천명) - CPU (대학생 8명(8코어))