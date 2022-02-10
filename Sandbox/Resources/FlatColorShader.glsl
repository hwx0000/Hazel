#type vertex

#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

void main()
{
	gl_Position = u_ViewProjection * u_Transform * vec4(aPos, 1.0);
}

#type fragment

#version 330 core

uniform vec4 u_Color;
out vec4 color;

void main()
{
	color = u_Color;
}