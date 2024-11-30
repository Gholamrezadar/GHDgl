#version 330 core
out vec4 FragColor;

uniform vec3 color;  // New uniform variable

in vec3 vertexColor;
in vec2 TexCoord;
in vec3 normal;
in vec3 fragPos;

void main()
{
    FragColor = vec4(color, 1.0f);
}
