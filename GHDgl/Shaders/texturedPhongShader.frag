#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // attenuation
    float constant;
    float linear;
    float quadratic;
};
uniform Light light;

uniform vec3 color;  // New uniform variable
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float lightIntensity;
uniform sampler2D texture1;
uniform vec3 viewPos; // Camera position
uniform bool isAttenuated;

in vec3 vertexColor;
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

void main()
{
    // calculate some useful vectors
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 lightDir = normalize(lightPos - FragPos);

    // ambient component
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords)); // TODO: ambient texture?

    // diffuse component
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse =  light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // specular component
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoords)));

    // attenuation
    float distance = length(lightPos - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    if (isAttenuated)
    {
        ambient *= attenuation;
        specular *= attenuation;
        diffuse *= attenuation;
    }
    // add the components together
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0f);

//    FragColor = vec4(1.0f, 0.5f, 1.0f, 1.0f);
}
