#version 330 core
out vec4 FragColor;

in vec3 gNormal;
in vec3 gPosition;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{             
    vec3 I = normalize(gPosition - cameraPos);
    vec3 R = reflect(I, normalize(gNormal));
    
    FragColor = vec4(texture(skybox, R).rgb, 1.0);
    
    // FragColor = vec4(normalize(gNormal) * 0.5 + 0.5, 1.0);
}