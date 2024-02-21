#pragma once

struct vertexColor {
	D3DXVECTOR3 position;
	D3DXCOLOR color;
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
	//IA와 VS의 규격을 서로 맞춰주는 역할(~부터 ~까지가 위치고 ~부터 ~까지가 컬러인지)
	ID3D11InputLayout* input_layout = nullptr;

	ID3D11VertexShader* vertex_shader = nullptr;
	ID3DBlob* vs_blob = nullptr;//binary large object

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
