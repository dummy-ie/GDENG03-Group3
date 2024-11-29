struct VS_INPUT
{
    float4 position : POSITION;
    float2 texcoord : TEXCOORD;
    float3 color : COLOR;
};

struct VS_OUTPUT
{
    float4 position : POSITION;
    float2 texcoord : TEXCOORD;
    float3 color : COLOR;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    return output;
}