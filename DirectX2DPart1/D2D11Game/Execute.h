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

	//��� ������ �ʿ�
	vertexColor* vertices = nullptr;
	ID3D11Buffer* vertex_buffer = nullptr;
	//IA�� VS�� �԰��� ���� �����ִ� ����(~���� ~������ ��ġ�� ~���� ~������ �÷�����)
	ID3D11InputLayout* input_layout = nullptr;

	ID3D11VertexShader* vertex_shader = nullptr;
	ID3DBlob* vs_blob = nullptr;//binary large object

};

//������ ����������
//ȭ�鿡 ǥ�õǱ� ���� ���������� �ڷᰡ �����Ǵ� �ܰ�
// IA VS RS PS OM
//VS,RS�ܰ�� �ڵ� ����

//IA : Input Assembler stage
//��:vertex(���� Ŀ���͸���¡�� ����ؾ� ��)

//VS : vertex Shader
//���̴�:(GPU�Լ��� ����[�������(���� ��)])->HLSL, GLSL
//- Transform (�������� ���� ��ȯ)
