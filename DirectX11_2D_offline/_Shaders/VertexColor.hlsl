
// VertexInput ����ü ����
struct VertexInput	// VertexShdaer���� ����� ����
{
	// VertexType���� ������ ����ƽ �̸��� ��ȣ�� ����ؾ� �Ѵ�.
	float4 position : POSITION0;	// ������ ��ġ
	float4 color	: COLOR0;		// ������ ��
};

// PixelInput ����ü ����
struct PixelInput	// PixelShdaer���� ����� ����
{
	// VertexType���� ������ ����ƽ �̸��� ��ȣ�� ����ؾ� �Ѵ�.
	float4 position : SV_POSITION0; // ������ ��ġ
	float4 color	: COLOR0;		// ������ ��
};

cbuffer WorldBuffer : register(b0)
{
	matrix _world;
};

cbuffer VPBuffer : register(b1)
{
	matrix _view;
	matrix _proj;
};

PixelInput VS(VertexInput input)
{
	PixelInput output;
	
	output.position = mul(input.position, _world);
	output.position = mul(output.position, _view);
	output.position = mul(output.position, _proj);
	
	output.color = input.color;
	
	return output;
};

float4 PS(PixelInput input) : SV_Target
{
	float4 color = input.color;
	
	return color;
};

/*
Semantic : ����ƽ
- HLSL ���̴����� �������� �ǹ̸� �����ϴµ� ���Ǵ� ����
- ���̴��� �Է� �����Ϳ� ��� �����͸� �ùٸ��� �ؼ��ϰ� ó���� �� �ֵ���
�����ش�. // VertexType�� InputLayout�� �̿��Ѵ�.
- ���� �̸��ڿ� : �� �Ա� ����
- �ý��� �� ����ƽ�� SV_ ���λ�� �����ϸ�, DirectX���� ������ Ư����
�ǹ̸� ���ϰ� �ȴ�.
- �ý��� �� ����ƽ�� ���� ���̴� �������� ���� �����͸� �����ϴµ� ���ȴ�.
// VS���� output���� ���� PixelInput���� PS�� ����ä�� ����Ҽ� �ְ� �ߴ�.

slot
- GPU���� ����ϴ� ��� ����, �ؽ�ó, ���÷� ���� �ڿ����� �ĺ��ϴ� �ε���
- �� ������ ������ ��ȣ�� ������, �ش� �ڿ��� ������ ���ҿ� ���� �ٸ���
�����Ѵ�.
- register��� Ű���带 ����Ͽ� ����
- �� �ڿ��� � ���Կ��� �Ҵ� �� �������� ��������� ������ �� �ִ�.
- �ֿ� ����
	1) ��� ���� ����
	- ��� �����͸� �����ϴµ� ���Ǹ�, VS�� PS���� ������ �� �ִ�.
	- register(b#)�� �Ҵ��Ͽ� ����
	
	2) �ؽ�ó ����
	- �̹��� �����͸� �����ϴµ� ���
	- register(t#)�� �Ҵ��Ͽ� ����

	3) ���÷� ����
	- �ؽ�ó�� ���ø��� ����� �����͸� �����ϴµ� ���
	- ���ø��� �ؽ�ó�� �����͸� �о���� ����� ���Ѵ�.
	- register(s#)�� �Ҵ��Ͽ� ����

cbuffer = Constant Buffer : ��� ����
- ���̴����� ����ϴ� ���� ������ �����ϴµ� ���
- �� ��� ���� �������ʹ� �� ���� ��� ���۸� �Ҵ��� �� �ִ�.
- ��� ���� ���ο��� ������ ������ ���� �� �ִ�.
- CPU���� GPU�� ������ �ƴ� �����͸� �ǳ��ֱ� ���ؼ��� 
cbuffer�� ��� �ؾ��Ѵ�.
*/