#version 330
uniform sampler2D gcolor;
uniform sampler2D gdepth;
uniform sampler2D gnormal;
uniform vec3 l_color;
uniform vec3 l_ambient;
uniform mat4 iP;
uniform mat4 iV;
uniform mat4 V;
uniform mat4 MV;

in vec2 uv;
in vec3 light_dir;

out vec3 color;

#include rand.glsl
#include clipspace.glsl
#include shadows.glsl
#include normal.glsl


void main() {
    vec4 gcol = texture(gcolor,uv);
    vec4 gnorm = texture(gnormal,uv);
    vec3 normal = normalize(unpackNormal(gnormal,uv));
    float depth = texture(gdepth,uv).r;
    gl_FragDepth = depth;

    vec3 wpos = worldFrom(uv, depth, iP, iV);
    vec3 view_dir = -normalize((V*vec4(wpos,1)).xyz);

    float diff = clamp(dot(normal,light_dir),0,1);
    vec3 ref = reflect(light_dir,normal);
    float spec = clamp(pow(clamp(dot(ref,view_dir),0,1),gnorm.a*64)*gcol.a,0,1);
    float shad = diffFromShadows(vec4(wpos,1), 1, normal, light_dir);
    diff *= shad;
    spec *= shad;
    //color = s_coords.rgb;
    color = gcol.rgb*(l_ambient+diff*l_color)+spec*l_color;
    //color = vec3(diff);
    //color  += debug(vec4(wpos,1))*0.125;
}
