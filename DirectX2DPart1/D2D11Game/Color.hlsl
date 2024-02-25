struct VertexInput
{//float�� 4��!
    float4 position : POSITION0;
    float4 color : COLOR0;
};

struct PixelInput
{//SV: system value
    float4 position : SV_POSITION0;
    float4 color : COLOR0;
};

cbuffer TransformBuffer : register(b0) // 0~13������ 7096 (16byte����)
{
    matrix world; //��켱 ���
    matrix view;  
    matrix proj;  
};

PixelInput VS(VertexInput input)
{
    
    PixelInput output;
    output.position = mul(input.position, world);
    output.position = mul(output.position, view);
    output.position = mul(output.position, proj);//Ŭ���� �����̽� ����
    
    output.color = input.color;
    
    return output;
}

//�����Ͷ������� ������ �ȼ� ������ŭ ȣ��
float4 PS(PixelInput input) : SV_Target
{
    return input.color;//���� �׷��� ���� ��
}
//hlsl�� ������ ���� ������