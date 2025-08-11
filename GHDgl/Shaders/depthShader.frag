#version 330 core
out vec4 FragColor;

uniform vec3 color;  // New uniform variable
uniform sampler2D texture1;
uniform vec3 viewPos; // Camera position

in vec3 vertexColor;
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

// depth visualization
float near = 0.1; 
float far  = 10.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{
    // float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
    // FragColor = vec4(vec3(depth), 1.0);
    FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
}