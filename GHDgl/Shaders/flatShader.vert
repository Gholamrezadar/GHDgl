#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aNormal;

out vec3 vertexColor;
out vec2 TexCoord;
out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 matrix; // Combines projection * view from the camera

void main()
{
    // note that we read the multiplication from right to left
    gl_Position = matrix * model * vec4(aPos, 1.0);
    fragPos = vec3(model * vec4(aPos, 1.0));
    vertexColor = aColor;
    normal = mat3(transpose(inverse(model))) * aNormal;
}