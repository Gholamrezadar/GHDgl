#version 330 core
out vec4 FragColor;

uniform vec3 color;  // New uniform variable

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float lightIntensity;

uniform sampler2D texture1;
uniform vec3 viewPos; // Camera position

in vec3 vertexColor;
in vec2 TexCoord;
in vec3 normal;
in vec3 fragPos;

void main()
{
    // FragColor = texture(texture1, TexCoord) * vec4(vertexColor, 1.0);
    float specularStrength = 0.5;
    float ambientStrength = 0.1;

    // calculate some useful vectors
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 lightDir = normalize(lightPos - fragPos);

    // ambient component
    vec3 ambient = ambientStrength * lightColor;

    // diffuse component
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular component
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // add the components together
    vec3 result = (ambient + diffuse + specular) * color;
    FragColor = vec4(result, 1.0f);
}
