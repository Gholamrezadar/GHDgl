#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

// from vertex shader
in vec3 Normal[];
in vec3 Position[];

// pass to fragment shader
out vec3 gNormal;
out vec3 gPosition;

// explosion amount
uniform float amount;

void main()
{
    // Calculate face normal from triangle edges
    vec3 edge1 = Position[1] - Position[0];
    vec3 edge2 = Position[2] - Position[0];
    vec3 faceNormal = normalize(cross(edge1, edge2));
    
    // Displace each vertex along the face normal
    for(int i = 0; i < 3; i++)
    {
        // Passing to fragment shader
        gNormal = Normal[i];
        gPosition = Position[i] + faceNormal * amount;

        // Explosion (Move along the face normal)
        gl_Position = gl_in[i].gl_Position + vec4(faceNormal * amount, 0.0);
        EmitVertex();
    }

    EndPrimitive();
}