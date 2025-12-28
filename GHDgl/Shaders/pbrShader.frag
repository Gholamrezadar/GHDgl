/*#version 330 core

out vec4 FragColor;

uniform mat4 model;
uniform mat4 matrix; // Combines projection * view from the camera
uniform vec3 color;

void main()
{
   FragColor = vec4(color, 1.0);
}

*/

#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec3 vertexColor;

uniform vec3 camPos;

// base material parameters
uniform vec3 color;        // base albedo color
uniform float metallic;    // [0,1]
uniform float roughness;   // [0,1]
uniform float ao;          // ambient occlusion [0,1]

// light definition (LearnOpenGL-style)
struct Light {
    vec3 position;
    vec3 color;
};

#define MAX_LIGHTS 4
uniform Light lights[MAX_LIGHTS];

const float PI = 3.14159265359;

// ----------------------------------------------------------------------------
// PBR helper functions
// ----------------------------------------------------------------------------
// float DistributionGGX(vec3 N, vec3 H, float roughness)
// {
//     float a      = roughness * roughness;
//     float a2     = a * a;
//     float NdotH  = max(dot(N, H), 0.0);
//     float NdotH2 = NdotH * NdotH;

//     float denom = (NdotH2 * (a2 - 1.0) + 1.0);
//     denom = PI * denom * denom;

//     return a2 / denom;
// }

// float GeometrySchlickGGX(float NdotV, float roughness)
// {
//     float r = roughness + 1.0;
//     float k = (r * r) / 8.0;

//     float denom = NdotV * (1.0 - k) + k;
//     return NdotV / denom;
// }

// float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
// {
//     float NdotV = max(dot(N, V), 0.0);
//     float NdotL = max(dot(N, L), 0.0);
//     float ggx1 = GeometrySchlickGGX(NdotV, roughness);
//     float ggx2 = GeometrySchlickGGX(NdotL, roughness);
//     return ggx1 * ggx2;
// }

// vec3 FresnelSchlick(float cosTheta, vec3 F0)
// {
//     return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
// }

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

// ----------------------------------------------------------------------------
// Main
// ----------------------------------------------------------------------------
// void main()
// {
//     vec3 N = normalize(Normal);
//     vec3 V = normalize(camPos - FragPos);

//     // Base reflectivity
//     vec3 albedo = pow(color, vec3(2.2)); // gamma -> linear

//     vec3 F0 = vec3(0.04);
//     F0 = mix(F0, albedo, metallic);

//     vec3 Lo = vec3(0.0);

//     vec3 temp = vec3(0.0);
//     for (int i = 0; i < MAX_LIGHTS; ++i)
//     {
//         vec3 L = normalize(lights[i].position - FragPos);
//         vec3 H = normalize(V + L);

//         float distance = length(lights[i].position - FragPos);
//         // distance = 0.0;
//         float attenuation = 1.0 / (distance * distance);
//         float power = 0.10;
//         vec3 radiance = lights[i].color * power * attenuation;
//         // temp += radiance;

//         float NDF = DistributionGGX(N, H, roughness);
//         float G   = GeometrySmith(N, V, L, roughness);
//         vec3  F   = FresnelSchlick(max(dot(H, V), 0.0), F0);

//         vec3 numerator    = NDF * G * F;
//         float denom       = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
//         vec3 specular     = numerator / denom;
//         temp += numerator*1000;

//         vec3 kS = F;
//         vec3 kD = vec3(1.0) - kS;
//         kD *= 1.0 - metallic;

//         float NdotL = max(dot(N, L), 0.0);
//         Lo += (kD * albedo / PI + specular) * radiance * NdotL;
//     }

//     // Ambient term (non-IBL version)
//     vec3 ambient = vec3(0.03) * albedo * ao;
//     vec3 colorOut = ambient + Lo;

//     // HDR tonemapping + gamma correction
//     // colorOut = colorOut / (colorOut + vec3(1.0));
//     // colorOut = pow(colorOut, vec3(1.0 / 2.2));

//     // float col = distance(lights[3].position, FragPos);
//     // FragColor = vec4(vec3(col)*lights[3].color, 1.0);
//     FragColor = vec4(temp, 1.0);
// }



void main()
{		
    vec3 N = normalize(Normal);
    vec3 V = normalize(camPos - FragPos);

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, color, metallic);
	           
    // reflectance equation
    vec3 Lo = vec3(0.0);
    for(int i = 0; i < 4; ++i) 
    {
        // calculate per-light radiance
        vec3 L = normalize(lights[i].position - FragPos);
        vec3 H = normalize(V + L);
        float distance    = length(lights[i].position - FragPos);
        float attenuation = 1.0 / (distance * distance);
        float powerr = 1.0;
        vec3 radiance = lights[i].color * powerr * attenuation;        
        
        // cook-torrance brdf
        float NDF = DistributionGGX(N, H, roughness);        
        float G   = GeometrySmith(N, V, L, roughness);      
        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);       
        
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;	  
        
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
        vec3 specular     = numerator / denominator;  
            
        // add to outgoing radiance Lo
        float NdotL = max(dot(N, L), 0.0);                
        Lo += (kD * color / PI + specular) * radiance * NdotL; 
    }   
  
    vec3 ambient = vec3(0.03) * color * ao;
    vec3 color = ambient + Lo;
	
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));  
   
    FragColor = vec4(color, 1.0);
} 