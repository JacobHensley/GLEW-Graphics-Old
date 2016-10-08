#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tc;

out vec4 pos;
out vec2 texCoord;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ProjMatrix;

void main() 
{
	gl_Position = u_ProjMatrix * u_ModelMatrix * position;
	pos = position;
	texCoord = tc;
}