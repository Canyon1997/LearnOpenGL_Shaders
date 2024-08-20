#version 330 core
out vec4 FragColor;

uniform vec4 ourColor; // Global variable used in shader program defined in main.cpp instead

void main()
{
	FragColor = ourColor;
}