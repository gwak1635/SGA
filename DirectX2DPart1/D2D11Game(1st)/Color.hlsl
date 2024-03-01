struct VertexInput
{//float가 4개!
    float4 position : POSITION0;
    float4 color : COLOR0;
};

struct PixelInput
{//SV: system value
    float4 position : SV_POSITION0;
    float4 color : COLOR0;
};

cbuffer TransformBuffer : register(b0) // 0~13번까지 7096 (16byte정렬)
{
    matrix world; //행우선 행렬
    matrix view;  
    matrix proj;  
};

PixelInput VS(VertexInput input)
{
    
    PixelInput output;
    output.position = mul(input.position, world);
    output.position = mul(output.position, view);
    output.position = mul(output.position, proj);//클리핑 스페이스 포함
    
    output.color = input.color;
    
    return output;
}

//래스터라이저가 지정한 픽셀 개수만큼 호출
float4 PS(PixelInput input) : SV_Target
{
    return input.color;//어디다 그려야 할지 모름
}
//hlsl은 진입점 단위 컴파일
