#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTextureIn;

out vec2 f_texcoord;
out vec2 vTexutreOut;

uniform vec2 inPos;

vec4 pos = vec4(inPos.x, inPos.y, 0.0f, 0.0f);

void main()
{
	gl_Position = vPosition + pos;	
	f_texcoord = vTextureIn;
}
