#version 330 core

in vec4 position;

uniform mat4 viewProjectionMatrix;

void main()
{
	gl_Position = viewProjectionMatrix * position;
}