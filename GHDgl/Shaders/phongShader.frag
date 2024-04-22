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
in vec3 fragPos;

void main()
{
    // FragColor = texture(texture1, TexCoord) * vec4(vertexColor, 1.0);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * color;
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    result = (ambient + diffuse) * color;

    FragColor = vec4(result, 1.0f);
}
