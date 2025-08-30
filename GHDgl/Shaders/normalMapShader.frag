#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
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

in vec3 vertexColor;
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in vec3 v_tangent;
in vec3 v_bitangent;

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
    return (ambient + diffuse + specular);
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

    // Change normals "norm" using the normal map
    // Sample the normal map from the texture
    vec3 normalMapSample = texture(material.normal, uv).rgb;
    
    // Convert from [0,1] range to [-1,1] range
    normalMapSample = normalMapSample * 2.0 - 1.0;
    
    // Create the TBN (Tangent-Bitangent-Normal) matrix
    vec3 N = normalize(norm);
    vec3 T = normalize(v_tangent);
    vec3 B = normalize(v_bitangent);
    mat3 TBN = mat3(T, B, N);
    
    // Transform the normal from tangent space to world space
    vec3 changedNormal = normalize(TBN * normalMapSample);

    vec3 result = vec3(0.0, 0.0, 0.0);
    for(int i = 0; i < NR_POINT_LIGHTS; i++) {
        result += CalcPointLight(pointLights[i], changedNormal, FragPos, viewDir, uv);
    }

    //result = vec3(max(dot(norm, viewDir), 0.0));
    //result = vec3(norm);

    // vec3 normalMap = texture(material.normal, uv).rgb;

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