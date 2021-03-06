#version 420

struct a2v_pos_only
{
    vec3 inputPosition;
};

struct pos_only_vert_output
{
    vec4 pos;
};

struct Light
{
    float lightIntensity;
    int lightType;
    int lightCastShadow;
    int lightShadowMapIndex;
    int lightAngleAttenCurveType;
    int lightDistAttenCurveType;
    vec2 lightSize;
    ivec4 lightGuid;
    vec4 lightPosition;
    vec4 lightColor;
    vec4 lightDirection;
    vec4 lightDistAttenCurveParams[2];
    vec4 lightAngleAttenCurveParams[2];
    mat4 lightVP;
    vec4 padding[2];
};

layout(binding = 11, std140) uniform PerBatchConstants
{
    mat4 modelMatrix;
} _33;

layout(location = 0) in vec3 a_inputPosition;

pos_only_vert_output _shadowmap_omni_vert_main(a2v_pos_only a)
{
    vec4 v = vec4(a.inputPosition, 1.0);
    pos_only_vert_output o;
    o.pos = _33.modelMatrix * v;
    return o;
}

void main()
{
    a2v_pos_only a;
    a.inputPosition = a_inputPosition;
    a2v_pos_only param = a;
    gl_Position = _shadowmap_omni_vert_main(param).pos;
}

