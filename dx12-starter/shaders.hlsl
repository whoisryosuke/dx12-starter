cbuffer SceneConstantBuffer : register(b0)
{
    float4 offset;
    float4 padding[15];
};

struct VSInput
{
    float3 position : POSITION;
    float2 uv : TEXCOORD;
    float3 normals : NORMAL;
};

struct PSInput
{
    float4 position : SV_POSITION;
    float2 color : COLOR;
};

//PSInput VSMain(float3 position : POSITION, float2 uv : TEXCOORD, float3 normals : NORMAL)

PSInput VSMain(VSInput input)
{
    PSInput result;
    
    result.position = float4(input.position, 1.f) + offset;
    result.color = input.uv;

    return result;
}

float4 PSMain(PSInput input) : SV_TARGET
{
    return float4(input.color, 0.f, 1.f);
}
