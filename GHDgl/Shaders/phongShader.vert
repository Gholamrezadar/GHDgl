#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aNormal;

out vec3 vertexColor;
out vec2 TexCoord;
out vec3 normal;

uniform mat4 model;
// uniform mat4 view;
// uniform mat4 projection;

uniform mat4 matrix;

void main()
{
    // note that we read the multiplication from right to left
    // gl_Position = projection * view * model * vec4(aPos, 1.0);
    gl_Position = matrix * model * vec4(aPos, 1.0);
    vertexColor = aColor;
    TexCoord = aTexCoord;
    normal = aNormal;
}