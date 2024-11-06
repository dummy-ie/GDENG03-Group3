struct VS_INPUT
{
    float4 pos : POSITION;
    float3 color : COLOR;
    float2 texcoord : TEXCOORD;
    //float3 color1 : COLOR1;
};

struct VS_OUTPUT
{
    float4 pos : POSITION;
    float3 color : COLOR;
    float2 texcoord : TEXCOORD;
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

// Texture Resources
Texture2D albedoMap : register(t0);
Texture2D normalMap : register(t1);
Texture2D metallicMap : register(t2);
Texture2D smoothnessMap : register(t3);

// Sampler for Textures
SamplerState samplerState : register(s0);


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
    //output.color1 = input.color1;
    
    output.texcoord = input.texcoord;

    // Calculate linear fog    
    output.fogFactor = getFogFactor(distance(cameraPos, input.pos));

    return output;
}

/* This is the required means to set shader resources. Conduct this WITHIN the rendering code.
deviceContext->PSSetShaderResources(0, 1, &albedoTexture);
deviceContext->PSSetShaderResources(1, 1, &normalTexture);
deviceContext->PSSetShaderResources(2, 1, &metallicTexture);
deviceContext->PSSetShaderResources(3, 1, &smoothnessTexture);
deviceContext->PSSetSamplers(0, 1, &samplerState);
*/