#version 400

in vec3 Position;
in vec3 Normal; 
out vec4 FragColor;

uniform vec3 uLightPosition;
uniform vec3 color;
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float Shininess;

void main()
{
    vec3 n = normalize(Normal);
    vec3 s = normalize(uLightPosition - Position);
    vec3 v = normalize(vec3(-Position));
    vec3 r = reflect(-s, n);
    vec3 color = color * (Ka + Kd * max( dot(s,n), 0.0) + Ks * pow(max( dot(r,v), 0.0), Shininess));
    FragColor = vec4(color, 1.0);
}


