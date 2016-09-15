#version 330 core

layout (location = 0) in vec4 position;

out vec4 pos;
uniform mat4 u_Matrix;

void main() 
{
	gl_Position = u_Matrix * position;
	pos = position;
}