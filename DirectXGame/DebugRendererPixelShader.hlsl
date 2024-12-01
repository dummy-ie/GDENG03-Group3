struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float3 color : COLOR;
};

cbuffer constant : register(b0)
{
    row_major float4x4 world;
    // row_major float4x4 view;
    // row_major float4x4 proj;
    float3 cameraPos;
    float time;

    float3 color;         // albedo color
    float metallicMul;       // metallic strength
    float smoothnessMul;     // specular strength
    float flatness;       // normal flatness
    float2 tiling;        // texture tiling
    float2 offset;        // texture offset

    float hasAlbedoMap;
    float hasNormalMap;
    float hasMetallicMap;
    float hasSmoothnessMap;
};

cbuffer camera : register(b1)
{
    row_major float4x4 view;
    row_major float4x4 proj;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    return float4(input.color, 1.0f);
}

