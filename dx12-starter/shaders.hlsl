cbuffer SceneConstantBuffer : register(b0)
{
    float4 offset;
    float4 padding[15];
};

cbuffer GlobalsConstantBuffer : register(b1)
{
    matrix viewMatrix;
    matrix projectionMatrix;
    float3 cameraPosition;
    float _gpad[26];
};

struct PSInput
{
    float4 position : SV_POSITION;
    float2 color : COLOR;
};

PSInput VSMain(float3 position : POSITION, float2 uv : TEXCOORD, float3 normals : NORMAL)
{
    PSInput result;
    
    result.position = float4(position, 1.f) + offset;
    
    //result.position = mul(viewMatrix, float4(position, 1));
    //result.position = mul(projectionMatrix, result.position);
    
    //result.color = uv;
    result.color = float2(cameraPosition.x, 0.f);

    return result;
}

float4 PSMain(PSInput input) : SV_TARGET
{
    return float4(0.f, input.color, 1.f);
}
