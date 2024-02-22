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

	//��� ������ �ʿ�
	vertexColor* vertices = nullptr;
	ID3D11Buffer* vertex_buffer = nullptr;

	uint* indices = nullptr;
	ID3D11Buffer* index_buffer = nullptr;

	//IA�� VS�� �԰��� ���� �����ִ� ����(~���� ~������ ��ġ�� ~���� ~������ �÷�����)
	ID3D11InputLayout* input_layout = nullptr;


	ID3D11VertexShader* vertex_shader = nullptr;
	ID3DBlob* vs_blob = nullptr;//binary large object

	ID3D11PixelShader* pixel_shader = nullptr;
	ID3DBlob* ps_blob = nullptr;

	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
	/*
	����� (��� ���� 0)
	[�������]�׵���� (n�� n���� 1)
	������ Ŀ���� �����͵鵵 ���� �þ
	1 0 0 0
	0 1 0 0
	0 0 1 0
	0 0 0 1(�߽���): ������ �̵��ϸ� �����鵵 ���� �̵��Ѵ�!
	*/

	TRANSFORM_DATA cpu_buffer;
	ID3D11Buffer* gpu_buffer = nullptr; // ��� ����
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

//RS : Rasterlizer (VS���� ����ȭ�� �����͸� �ٽ� �÷���)[�� ���̴� �� ���������� ����!)
//������ȭ(3D�����͸� 2D �����ͷ� �ٲ��ִ� ��
//Begin�� OM�� RS�� ���� 
//NDC: 0~1�� ����ȭ�� ��(�þ���)
//Ʈ������: �װ� �� �ȼ��� �ٲ�

//PS : 

//Local : ������� ��ǥ����(������ǥ��)
//World : ���� ��ǥ��
//View : ���̴� ����(�޸��� �� ����!)
//Projection : ��������(3D->2D)
//Clip : ������ ���ϵ��� ����ȭ(0-1��) -��������
//NDC : ������ǥ���� ����ȭ�� ����-��Ŭ���� ����
//Viewport : ���̴� ����

//��������
//(1,0,0)�� ��ǥ? ����? ��?��
//1���� �� Ȯ���Ű��
//(1,0,0,0[w])w�� �������� ��ġ���� �Ǵ� w�� 0�̶�� ��� �����̴�