#version 330 core
in vec4 vertexColor;
in vec4 posColor;
out vec4 FragColor;

void main()
{
    FragColor = posColor;
} 
