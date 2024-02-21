struct VertexInput
{//float°¡ 4°³!
    float4 position : POSITION0;
    float4 color : COLOR0;
};

struct PixelInput
{//SV: system value
    float4 position : SV_POSITION0;
    float4 color : COLOR0;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.position = input.position;
    output.color = input.color;
    
    
    return output;
}