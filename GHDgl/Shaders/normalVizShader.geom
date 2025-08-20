#version 330 core

layout (triangles) in;
layout (line_strip, max_vertices = 2) out;

in vec3 Normal[];    // from vertex shader
in vec3 Position[];

uniform mat4 projection;
uniform mat4 view;
uniform float normalLength; // length of normal lines (default: 0.1)

void main()
{
    // Calculate proper face normal from triangle edges
    vec3 edge1 = Position[1] - Position[0];
    vec3 edge2 = Position[2] - Position[0];
    vec3 faceNormal = normalize(cross(edge1, edge2));
    
    // Calculate triangle center
    vec3 center = (Position[0] + Position[1] + Position[2]) / 3.0;
    
    // First vertex: triangle center
    gl_Position = projection * view * vec4(center, 1.0);
    EmitVertex();
    
    // Second vertex: center + normal direction
    vec3 normalEnd = center + faceNormal * normalLength;
    gl_Position = projection * view * vec4(normalEnd, 1.0);
    EmitVertex();
    
    EndPrimitive();
}