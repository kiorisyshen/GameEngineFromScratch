#pragma clang diagnostic ignored "-Wmissing-prototypes"

#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

struct a2v_pos_only
{
    float3 inputPosition;
};

struct pos_only_vert_output
{
    float4 pos;
};

struct PerBatchConstants
{
    float4x4 modelMatrix;
};

struct PerFrameConstants
{
    float4x4 viewMatrix;
    float4x4 projectionMatrix;
    float4 camPos;
    int numLights;
};

struct Light
{
    float lightIntensity;
    int lightType;
    int lightCastShadow;
    int lightShadowMapIndex;
    int lightAngleAttenCurveType;
    int lightDistAttenCurveType;
    float2 lightSize;
    int4 lightGuid;
    float4 lightPosition;
    float4 lightColor;
    float4 lightDirection;
    float4 lightDistAttenCurveParams[2];
    float4 lightAngleAttenCurveParams[2];
    float4x4 lightVP;
    float4 padding[2];
};

struct LightInfo
{
    Light lights[100];
};

struct DebugConstants
{
    float layer_index;
    float mip_level;
    float line_width;
    float padding0;
    float4 front_color;
    float4 back_color;
};

struct ShadowMapConstants
{
    float4x4 shadowMatrices[6];
    float4 lightPos;
    float shadowmap_layer_index;
    float far_plane;
};

struct shadowmap_omni_vert_main_out
{
    float4 gl_Position [[position]];
};

struct shadowmap_omni_vert_main_in
{
    float3 a_inputPosition [[attribute(0)]];
};

pos_only_vert_output _shadowmap_omni_vert_main(thread const a2v_pos_only& a, constant PerBatchConstants& v_33)
{
    float4 v = float4(a.inputPosition, 1.0);
    pos_only_vert_output o;
    o.pos = v_33.modelMatrix * v;
    return o;
}

vertex shadowmap_omni_vert_main_out shadowmap_omni_vert_main(shadowmap_omni_vert_main_in in [[stage_in]], constant PerBatchConstants& v_33 [[buffer(11)]])
{
    shadowmap_omni_vert_main_out out = {};
    a2v_pos_only a;
    a.inputPosition = in.a_inputPosition;
    a2v_pos_only param = a;
    out.gl_Position = _shadowmap_omni_vert_main(param, v_33).pos;
    return out;
}

