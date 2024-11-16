#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aNormal;

out vec3 vertexColor;
out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 matrix; // Combines projection * view from the camera

void main()
{
    // note that we read the multiplication from right to left
    gl_Position = matrix * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    vertexColor = aColor;
    TexCoords = aTexCoord;
    Normal = mat3(transpose(inverse(model))) * aNormal;
}