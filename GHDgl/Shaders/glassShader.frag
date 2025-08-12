#version 330 core
out vec4 FragColor;

uniform vec4 color;  // New uniform variable
uniform sampler2D texture1;
uniform vec3 viewPos; // Camera position
uniform vec2 tiling;

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
    vec2 uv = TexCoords;
    // tiling
    uv *= tiling; 
    // uv += vec2(0.5, 0.25);

    FragColor = vec4(texture(texture1, uv));
}