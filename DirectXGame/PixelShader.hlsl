struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float2 texcoord : TEXCOORD;
    float3 color : COLOR;
    float3 directionToCamera : TEXCOORD1;
    float fogFactor : FOG;
};

cbuffer constant : register(b0)
{
    row_major float4x4 world;
    row_major float4x4 view;
    row_major float4x4 proj;
    float3 cameraPos;
    float time;

    float3 color; // albedo color
    float metallicMul; // metallic strength
    float smoothnessMul; // specular strength
    float flatness; // normal flatness
    float2 tiling; // texture tiling
    float2 offset; // texture offset

    float hasAlbedoMap;
    float hasNormalMap;
    float hasMetallicMap;
    float hasSmoothnessMap;
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
	// Sample textures
    float4 albedo = (hasAlbedoMap > 0.5) ? albedoMap.Sample(samplerState, input.texcoord) * float4(color, 1.0) : float4(color, 1.0);
    float3 normal = (hasNormalMap > 0.5) ? (normalMap.Sample(samplerState, input.texcoord).rgb * 2.0 - 1.0) * (1.0 - flatness) + float3(0.0, 0.0, flatness)
                          : float3(0.0, 0.0, 1.0);
    float metallic = (hasMetallicMap > 0.5) ? metallicMap.Sample(samplerState, input.texcoord).r * metallicMul : metallicMul;
    float smoothness = (hasSmoothnessMap > 0.5) ? smoothnessMap.Sample(samplerState, input.texcoord).r * smoothnessMul : smoothnessMul;

    float3 lightDirection = normalize(float3(0.f, -1.f, 0.f));

    //AMBIENT LIGHT
    float ka = 0.6;
    float3 ia = float3(1.0, 1.0, 1.0);

    float3 ambientLight = ka * ia;

	//DIFFUSE LIGHT
    float kd = 10.0 * metallic;
    float3 id = float3(1.0, 1.0, 1.0);
    float amountDiffuseLight = max(0.1 * smoothness, dot(lightDirection, normal));
    float3 diffuseLight = (kd + 1) * amountDiffuseLight * id;

	//SPECULAR LIGHT
    float ks = metallic * 2.0 + 0.1;
    float3 is = float3(1.0, 1.0, 1.0);
    float3 reflectedLight = reflect(-lightDirection, normal);
    float shininess = lerp(5.0, 100.0, smoothness);
    float amountSpecularLight = pow(max(0.0, dot(reflectedLight, input.directionToCamera)), shininess);

    float3 specularLight = ks * amountSpecularLight * is;

    float3 finalLight = ambientLight + diffuseLight + specularLight;

    float4 color = float4(1.f, 1.f, 1.f, 1.f);
    float4 fogColor = float4(0.83f, 0.58f, 0.895f, 1.f);
    // float4 fogColor = float4(1.f, 1.f, 1.f, 1.f);

    color *= albedo;

    // if (any(finalLight > float3(0.f, 0.f, 0.f)))
    // {
    //     color *= float4(finalLight, 1.f);
    // }

    // if (any(input.color < float3(1.f, 1.f, 1.f)))
    // {
    //     color *= float4(input.color, 1.f);
    // }

    // color = float4(lerp(input.color, input.color, (sin(time) + 1.0f) / 2.0f), 1.f);

    // return lerp(color, fogColor, input.fogFactor);
    return color;
}

