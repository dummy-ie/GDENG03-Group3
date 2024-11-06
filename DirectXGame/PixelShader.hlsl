struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float3 color : COLOR;
    float2 texcoord : TEXCOORD;
    //float3 color1 : COLOR1;
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

float4 main(PS_INPUT input) : SV_TARGET
{
    float4 color = float4(0.f, 1.f, 0.f, 1.f);
    float4 fogColor = float4(0.83f, 0.58f, 0.895f, 1.f);
    // float4 fogColor = float4(1.f, 1.f, 1.f, 1.f);
    // Sample textures
    float4 albedo = albedoMap.Sample(samplerState, input.texcoord);
    float3 normal = normalMap.Sample(samplerState, input.texcoord).rgb * 2.0 - 1.0;
    float metallic = metallicMap.Sample(samplerState, input.texcoord).r;
    float smoothness = smoothnessMap.Sample(samplerState, input.texcoord).r;

    
    color = float4(lerp(input.color, input.color, (sin(time) + 1.0f) / 2.0f), 1.f);

    // return lerp(color, fogColor, input.fogFactor);
    return color;
}

