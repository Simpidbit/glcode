#version 330 core
in vec3 myColor;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D myTexture1;
uniform sampler2D myTexture2;

void main()
{
    FragColor = mix(texture(myTexture1, TexCoord), texture(myTexture2, TexCoord), 0.5);
} 
