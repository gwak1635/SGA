#pragma once

struct vertexColor {
	D3DXVECTOR3 position;
	D3DXCOLOR color;
};
 
struct TRANSFORM_DATA {
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
};
class Execute final
{
public:
	Execute();
	~Execute();

	void Update();
	void Render();
private:
	class Graphics* graphics = nullptr;

	//얘는 컨버팅 필요
	vertexColor* vertices = nullptr;
	ID3D11Buffer* vertex_buffer = nullptr;

	uint* indices = nullptr;
	ID3D11Buffer* index_buffer = nullptr;

	//IA와 VS의 규격을 서로 맞춰주는 역할(~부터 ~까지가 위치고 ~부터 ~까지가 컬러인지)
	ID3D11InputLayout* input_layout = nullptr;


	ID3D11VertexShader* vertex_shader = nullptr;
	ID3DBlob* vs_blob = nullptr;//binary large object

	ID3D11PixelShader* pixel_shader = nullptr;
	ID3DBlob* ps_blob = nullptr;

	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
	/*
	영행렬 (모든 행이 0)
	[단위행렬]항등행렬 (n행 n열이 1)
	공간이 커지면 데이터들도 같이 늘어남
	1 0 0 0
	0 1 0 0
	0 0 1 0
	0 0 0 1(중심점): 공간이 이동하면 정점들도 같이 이동한다!
	*/

	TRANSFORM_DATA cpu_buffer;
	ID3D11Buffer* gpu_buffer = nullptr; // 상수 버퍼
};

//렌더링 파이프라인
//화면에 표시되기 위해 순차적으로 자료가 가공되는 단계
// IA VS RS PS OM
//VS,RS단계는 코딩 가능

//IA : Input Assembler stage
//점:vertex(직접 커스터마이징해 사용해야 함)

//VS : vertex Shader
//셰이더:(GPU함수의 집합[어셈블리어(였던 것)])->HLSL, GLSL
//- Transform (정점들의 공간 변환)

//RS : Rasterlizer (VS에서 정규화된 데이터를 다시 늘려줌)[안 보이는 건 렌더링하지 않음!)
//래스터화(3D데이터를 2D 데이터로 바꿔주는 것
//Begin에 OM과 RS가 있음 
//NDC: 0~1로 정규화된 것(늘어짐)
//트랜스폼: 그걸 또 픽셀로 바꿈

//PS : 

//Local : 설계상의 좌표공간(지역좌표계)
//World : 전역 좌표계
//View : 보이는 영역(뒷면은 안 보임!)
//Projection : 투영공간(3D->2D)
//Clip : 오리기 편하도록 정규화(0-1로) -동차공간
//NDC : 동차좌표까지 정규화된 공간-유클리드 공간
//Viewport : 보이는 공간

//동차공간
//(1,0,0)은 좌표? 방향? 몰?루
//1차원 더 확장시키자
//(1,0,0,0[w])w로 방향인지 위치인지 판단 w가 0이라면 얘는 방향이다