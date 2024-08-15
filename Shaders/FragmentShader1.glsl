#version 330 core
out vec4 FragColor;

in vec4 vertexColor; // input variable from vertex shader

void main()
{
	FragColor = vertexColor;
}