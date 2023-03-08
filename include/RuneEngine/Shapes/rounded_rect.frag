#version 450

uniform vec2 ures;
uniform sampler2D uTexture;
uniform float radius;
const vec2 size = vec2(1.0, 1.0);
float roundedRect(vec2 pos)
{
    float r = radius / ures.y;
    return smoothstep(size.x / 2.0 + r, size.x / 2.0 - r, abs(pos.x)) * 
           smoothstep(size.y / 2.0 + r, size.y / 2.0 - r, abs(pos.y));    
}

layout (location = 0) out vec4 fragColor;

void main()
{    
    vec2 uv = gl_FragCoord.xy/ures - 0.5;
    float delta = 0.5 / radius;
    uv.y = - uv.y;
    vec4 TexCol = texture(uTexture, uv.xy + 0.5);  
    fragColor = TexCol*smoothstep(0.5 - delta, 0.5 + delta, roundedRect(uv));
}