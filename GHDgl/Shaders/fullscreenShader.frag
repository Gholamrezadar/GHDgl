#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D color;
uniform sampler2D depth;

float near = 0.1; 
float far  = 1.0; 
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

vec4 kernelConvolution(vec2 uv, float kernel[9])
{
    const float offset = 1.0 / 900.0;  
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );
    
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(color, uv + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];
    
    return vec4(col, 1.0);
}

void main()
{ 
    vec2 uv = TexCoords;
    vec4 col;

    // effects_green
    // col = texture(color, uv)*vec4(0.0902, 0.8314, 0.0902, 1.0);


    // effects_bw
    // float lum = dot(texture(color, uv).rgb, vec3(0.299, 0.587, 0.114));
    // col = vec4(lum, lum, lum, 1.0);


    // effects_invert
    // col = vec4(1.0 - texture(color, uv).rgb, 1.0);


    // effects_binary
    // float threshold = 0.45;
    // float lum = dot(texture(color, uv).rgb, vec3(0.299, 0.587, 0.114));
    // if(lum >= threshold) {
    //     col = vec4(1.0, 1.0, 1.0, 1.0);
    // }
    // else{
    //     col = vec4(0.0, 0.0, 0.0, 1.0);
    // }


    // effects_fog
    // float raw_depth = texture(depth, uv).x;
    // float linear_depth = LinearizeDepth(raw_depth);
    // float fog = smoothstep(linear_depth, 0.2, 0.5);
    // col = mix(texture(color, uv), vec4(1.0, 1.0, 1.0, 1.0), fog);


    // effects_pixelate
    // make it square
    // vec2 pixelation = vec2(1.0, 0.6) * 100.0;
    // uv = floor(uv * pixelation) / pixelation;
    // col = texture(color, uv);

    // effects_sharpen
    // float kernel[9] = float[](
    //     -1, -1, -1,
    //     -1,  9, -1,
    //     -1, -1, -1
    // );
    // col = kernelConvolution(uv, kernel);
    
    // effects_blur
    // float kernel[9] = float[](
    //     1.0 / 16, 2.0 / 16, 1.0 / 16,
    //     2.0 / 16, 4.0 / 16, 2.0 / 16,
    //     1.0 / 16, 2.0 / 16, 1.0 / 16  
    // );
    // col = kernelConvolution(uv, kernel);

    // effects_edge
    // float kernel[9] = float[](
    //     -1, -1, -1,
    //     -1,  8, -1,
    //     -1, -1, -1
    // );
    // col = kernelConvolution(uv, kernel);
    // col = vec4(vec3(dot(col.rgb, vec3(0.299, 0.587, 0.114))), 1.0);
    // col = vec4(vec3(smoothstep(0.0, 1.0, col.r)), 1.0);

    // effects_rgb_split
    // float offset = 0.0035; // tweak for intensity
    // float angle = radians(45.0); // direction of split
    // vec2 dir = vec2(cos(angle), sin(angle)) * offset;
    // float r = texture(color, uv + dir).r;
    // float g = texture(color, uv).g;
    // float b = texture(color, uv - dir).b;
    // col = vec4(r, g, b, 1.0);


    // effects_crt_bulge
    // vec2 centered = uv * 2.0 - 1.0; // move [0,1] → [-1,1]
    // float radius = length(centered);
    // float bulge_amount = 0.15; // positive = bulge out, negative = pinch
    // centered *= 1.0 + bulge_amount * radius * radius;
    // uv = (centered * 0.5) + 0.5; // back to [0,1]
    // col = texture(color, uv);


    // effects_vignette
    // vec2 pos = uv - 0.5;
    // float vignette_radius = 0.75; // larger = weaker vignette
    // float vignette_softness = 0.45;
    // float dist = length(pos);
    // float vignette = smoothstep(vignette_radius, vignette_radius - vignette_softness, dist);
    // col = texture(color, uv) * vignette;

    // normal
    col = texture(color, uv);

    FragColor = col;
}