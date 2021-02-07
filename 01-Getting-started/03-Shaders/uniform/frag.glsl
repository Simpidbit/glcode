#version 330 core
in vec4 vertexColor;
out vec4 FragColor;
uniform vec4 myColor;

void main()
{
    FragColor = myColor;
} 
