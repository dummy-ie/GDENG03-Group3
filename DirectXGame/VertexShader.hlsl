struct VS_INPUT
{
    float4 pos : POSITION;
    float4 pos1 : POSITION1;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

struct VS_OUTPUT
{
    float4 pos : POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

cbuffer constant : register(b0)
{
    row_major float4x4 world;
    row_major float4x4 view;
    row_major float4x4 proj;
    float time;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;

    input.pos = lerp(input.pos, input.pos1, (sin(time) + 1.0f) / 2.0f);
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);

	// output.pos1 = input.pos1;
    output.color = input.color;
    output.color1 = input.color1;
    return output;
}