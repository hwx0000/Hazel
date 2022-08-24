#type vertex

#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;
layout(location = 2) in vec4 aCol;
layout(location = 3) in int aTexIndex;
layout(location = 4) in float aTilingFactor;
layout(location = 5) in int aInstanceId;

uniform mat4 u_ViewProjection;

out vec2 v_TexCoord;
out vec4 v_Color;
flat out int v_TexIndex;
out float v_TilingFactor;
flat out int v_InstanceId;

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

#version 330 core

in vec2 v_TexCoord;
in vec4 v_Color;
flat in int v_TexIndex;
in float v_TilingFactor;
flat in int v_InstanceId;

out vec4 color;
uniform sampler2D u_Texture[32];

void main()
{
	color = texture(u_Texture[v_TexIndex], v_TexCoord * v_TilingFactor) * v_Color;
	//int s = v_InstanceId;
	//
	//if(s == 0)
	//	color = vec4(1, 1, 0, 1);
	//else if(s == 1)
	//	color = vec4(0, 1, 1, 1);
	//else if(s == 2)
	//	color = vec4(0, 1, 1, 1);
	//else if(s == 3)
	//	color = vec4(0.5, 1, 1, 1);
	//else 
	//   color = vec4(0, 0, 1, 1);
}