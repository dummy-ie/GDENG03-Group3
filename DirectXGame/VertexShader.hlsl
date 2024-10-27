struct VS_INPUT
{
    float4 pos : POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

struct VS_OUTPUT
{
    float4 pos : POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
    float fogFactor : FOG;
};

cbuffer constant : register(b0)
{
    row_major float4x4 world;
    row_major float4x4 view;
    row_major float4x4 proj;
    float3 cameraPos;
    float time;
};

float getFogFactor(float d)
{
    const float fogMax = 10.0;
    const float fogMin = 1.0;

    return clamp((d - fogMin) / (fogMax - fogMin), 0, 1);
}

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    // input.pos.w = 1.0f;

    //output.pos = lerp(input.pos, input.pos1, (sin(m_angle) + 1.0f) / 2.0f);

    // World Space
    output.pos = mul(input.pos, world);

	// View Space
    output.pos = mul(output.pos, view);

    // Screen Space
    output.pos = mul(output.pos, proj);

    output.color = input.color;
    output.color1 = input.color1;

    // Calculate linear fog    
    output.fogFactor = getFogFactor(distance(cameraPos, input.pos));

    return output;
}