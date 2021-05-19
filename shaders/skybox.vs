#version 400

layout (location = 0) in vec3 vPos;

out vec3 color;
out vec2 uv;

uniform mat4 uPV;
uniform mat4 uMV;

void main()
{
   uv = vPos.xy;
   color = vPos;
   gl_Position =  uPV * uMV * vec4(vPos, 1.0);
}


