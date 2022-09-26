#type vertex

#version 450 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;
layout(location = 2) in vec4 aCol;
layout(location = 3) in int aTexIndex;
layout(location = 4) in float aTilingFactor;
layout(location = 5) in int aInstanceId;


// 这里的binding类似于layout(location = 1)的location，应该是绑定到0号槽位的uniform buffer上
layout(std140, binding = 0) uniform Transform
{
    mat4 u_ViewProjection;
};

layout(location = 0) out vec2 v_TexCoord;
layout(location = 1) out vec4 v_Color;
layout(location = 2) flat out int v_TexIndex;
layout(location = 3) out float v_TilingFactor;
layout(location = 4) flat out int v_InstanceId;

void main()
{
	gl_Position = u_ViewProjection * vec4(aPos, 1.0);
	v_TexCoord = aTex;
	v_Color = aCol;
	v_TexIndex = aTexIndex;
	v_TilingFactor = aTilingFactor;
	v_InstanceId = aInstanceId;
}

#type fragment

#version 450 core

layout(location = 0) in vec2 v_TexCoord;
layout(location = 1) in vec4 v_Color;
layout(location = 2) flat in int v_TexIndex;
layout(location = 3) in float v_TilingFactor;
layout(location = 4) flat in int v_InstanceId;


layout (location = 0) out vec4 out_color;
layout (location = 1) out int out_InstanceId;


// 这个就没有必要用Uniform Buffer了
layout (binding = 0) uniform sampler2D u_Texture[32];

void main()
{
	out_color = texture(u_Texture[v_TexIndex], v_TexCoord * v_TilingFactor) * v_Color;
	out_InstanceId = v_InstanceId;
}