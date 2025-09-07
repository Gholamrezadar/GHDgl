#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // attenuation
    float constant;
    float linear;
    float quadratic;
};

#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform vec3 color;  // New uniform variable
uniform sampler2D texture1;
uniform vec3 viewPos; // Camera position
uniform vec2 tiling;
uniform sampler2D shadowMap;


in vec3 vertexColor;
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in vec4 FragPosLightSpace;


float ShadowCalculation(vec4 fragPosLightSpace)
{
    // Transform from clip space to [0,1] range for texture lookup
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;

    // If outside light frustum, return 0 shadow
    if (projCoords.z > 1.0)
        return 0.0;

    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    // return closestDepth;
    // return currentDepth;
    // float bias = 0.001;
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0; 
    // return shadow;

    // PCF (Percentage-Closer Filtering)
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - 0.005 > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    return shadow;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec2 uv)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading phong
    // vec3 reflectDir = reflect(-lightDir, normal);
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // specular shading blinn_phong
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 16.0);

    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
    light.quadratic * (distance * distance));

    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, uv));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, uv));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, uv));

    // ambient *= attenuation;
    specular *= attenuation;
    diffuse *= attenuation;

    // shadow
    float shadow = ShadowCalculation(FragPosLightSpace);
    // lift the shadows
    shadow = shadow - 0.09;
    vec3 lighting = (ambient*(1.0-shadow) + ambient*0.4 + (1.0 - shadow) * (diffuse + specular));
    return lighting;
}

void main()
{
    // UV mapping
    vec2 uv = TexCoords;
    // tiling
    uv *= tiling;

    // calculate some useful vectors
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0, 0.0, 0.0);
    for(int i = 0; i < NR_POINT_LIGHTS; i++) {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir, uv);
    }

    //result = vec3(max(dot(norm, viewDir), 0.0));
    //result = vec3(norm);
    // float shadow = ShadowCalculation(FragPosLightSpace);

    // result = vec3(shadow);

    FragColor = vec4(result, 1.0);
}


// depth visualization

// float near = 0.1; 
// float far  = 10.0; 
  
// float LinearizeDepth(float depth) 
// {
//     float z = depth * 2.0 - 1.0; // back to NDC 
//     return (2.0 * near * far) / (far + near - z * (far - near));	
// }

// void main()
// {             
//     float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
//     FragColor = vec4(vec3(depth), 1.0);
// }