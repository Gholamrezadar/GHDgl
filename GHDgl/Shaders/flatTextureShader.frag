#version 330 core
out vec4 FragColor;

uniform vec3 color;  // New uniform variable
uniform sampler2D texture1;

in vec3 vertexColor;
in vec2 TexCoord;

void main()
{
    FragColor = texture(texture1, TexCoord) * vec4(vertexColor, 1.0);
}
