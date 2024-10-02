
struct PS_INPUT
{
    float4 position : SV_POSITION;
  
    float2 texcoord : TEXCOORD; //recieve texcoord from vertex shader
};

Texture2D tex : register(t0); //Declaration of texture

SamplerState samplerState : register(s0); //Declare the sampler

float4 psmain(PS_INPUT input) : SV_TARGET
{
   
    
     // Sample the texture at the given texture coordinates
    float3 textureColor = tex.Sample(samplerState, input.texcoord);


    // Return the final color with full opacity
    return float4(textureColor, 1.0f);
    
    
}






//float3 color : COLOR;
//float3 color1 : COLOR1;

/*cbuffer constant : register(b0)
{
    float m_angle;
};*/

// return float4(lerp(input.color, input.color1, (sin(m_angle) + 1.0f) / 2.0f), 1.0f);

 // Blend texture color with input vertex color (example: 50% blend)
    //float3 blendedColor = lerp(input.color, textureColor.rgb, 0.5); // 0.5 means equal blending

//return float4(input.color, 1.0f);