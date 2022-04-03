#type vertex

#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;
layout(location = 2) in vec4 aCol;

out vec2 v_TexCoord;
out vec4 v_Color;

uniform mat4 u_ViewProjection;

void main()
{
	gl_Position = u_ViewProjection * vec4(aPos, 1.0);
	v_TexCoord = aTex;
	v_Color = aCol;
}

#type fragment

#version 330 core

in vec2 v_TexCoord;
in vec4 v_Color;

out vec4 color;
uniform sampler2D u_Texture;
uniform float u_TilingFactor;

void main()
{
	color = texture(u_Texture, v_TexCoord * u_TilingFactor) * v_Color;
}