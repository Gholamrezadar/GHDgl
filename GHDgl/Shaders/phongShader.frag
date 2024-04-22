#version 330 core
out vec4 FragColor;

uniform vec3 color;  // New uniform variable

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float lightIntensity;

uniform sampler2D texture1;

in vec3 vertexColor;
in vec2 TexCoord;
in vec3 normal;

void main()
{
    // FragColor = texture(texture1, TexCoord) * vec4(vertexColor, 1.0);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * color;
    // FragColor = vec4(result, 1.0f);
    FragColor = vec4(normal, 1.0f);
}
