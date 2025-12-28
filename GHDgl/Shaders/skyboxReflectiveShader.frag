#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{             
    vec3 I = normalize(Position - cameraPos);
    vec3 R = reflect(I, normalize(Normal));
    FragColor = vec4(texture(skybox, R).rgb, 1.0);
    // FragColor = vec4(R, 1.0);
    // FragColor = dot(R, vec3(0.0f,1.0f,0.0f))>0.0f?vec4(1.0f, 1.0f, 1.0f, 1.0f):vec4(0.0f, 0.0f, 0.0f, 1.0f);
}