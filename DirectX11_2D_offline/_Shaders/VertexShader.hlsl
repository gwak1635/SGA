
// VertexInput ����ü ����
struct VertexInput	// VertexShdaer���� ����� ����
{
	// VertexType���� ������ ����ƽ �̸��� ��ȣ�� ����ؾ� �Ѵ�.
	float4 position : POSITION0;	// ������ ��ġ
	float2 uv	: TEXCOORD0;		// �׸��� ��ǥ
};

// PixelInput ����ü ����
struct PixelInput	// PixelShdaer���� ����� ����
{
	// VertexType���� ������ ����ƽ �̸��� ��ȣ�� ����ؾ� �Ѵ�.
    float4 position : SV_POSITION0; // ������ ��ġ
    float2 uv : TEXCOORD0; // �׸��� ��ǥ
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
	
	output.uv = input.uv;
	
	return output;
};

Texture2D _sourceTex : register(t0);
SamplerState _samp : register(s0);

cbuffer STBuffer : register(b0)
{
    int _sel;
	
    int _bc;
    float2 _textureSize;
}

float4 PS(PixelInput input) : SV_Target
{
    float4 color = _sourceTex.Sample(_samp, (float2)input.uv);

    if (_sel == 1)
    {
        return color;
    }
    else if (_sel == 2)
    {
        //Gray
        float3 gray = dot(color.rgb, float3(0.229f, 0.587f, 0.114f));
        color = float4(gray, color.a);

    }
	else if (_sel == 3)
    {
        float3 negative = 1 - abs(color.rgb);
        color = float4(negative, color.a);

    }
	else if (_sel == 4)
    {
		//�ֺ� �ȼ� ��ġ
        float2 arr[8] =
        {
            float2(-1, +1), float2(+0, +1), float2(+1, +1),
            float2(-1, +0), float2(+1, +0),
            float2(-1, -1), float2(+0, -1), float2(+1, -1)
        };
		
        //���� Ŀ���� �� �ϰ� �д´�. 
        for (int blur = 1; blur < _bc; blur++)
        {
            for (int i = 0; i < 8; i++)
            {
                float x = arr[i].x * (float) blur / _textureSize.x;
                float y = arr[i].y * (float) blur / _textureSize.y;
                
                //�ֺ� �ȼ��� uv��
                float2 uv = input.uv + float2(x, y);

                //�ֺ� �ȼ� uv�� ���� �׸� ������ ������ ��� �߰��ϱ�
                color += _sourceTex.Sample(_samp, uv);
            }
        }
        
        int blurInt = _bc - 1;
        int offsetCount = 8;
        
        int totalSamples = blurInt * offsetCount + 1;
        
        color /= totalSamples;
    }
    else if (_sel == 5)
    {
        input.uv.x = 1 - input.uv.x;
        
        color = _sourceTex.Sample(_samp, (float2) input.uv);

    }
    else if (_sel == 6)
    {
        input.uv.y = 1 - input.uv.y;
        
        color = _sourceTex.Sample(_samp, (float2) input.uv);

    }
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