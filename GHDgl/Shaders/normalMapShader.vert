#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aColor;

out vec3 vertexColor;
out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;
out vec3 v_tangent;
out vec3 v_bitangent;

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

    // Calculate tangent vector
    // This creates a tangent that generally aligns with the U texture coordinate direction
    vec3 c1 = cross(Normal, vec3(0.0, 0.0, 1.0));
    vec3 c2 = cross(Normal, vec3(0.0, 1.0, 0.0));
    
    // Choose the cross product that gives us the longer vector (more stable)
    if (length(c1) > length(c2)) {
        v_tangent = normalize(c1);
    } else {
        v_tangent = normalize(c2);
    }
    
    // Calculate bitangent
    v_bitangent = normalize(cross(Normal, v_tangent));
    //Normal = aNormal;
}