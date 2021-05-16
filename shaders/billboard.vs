#version 400

layout (location = 0) in vec3 vPos;

uniform vec3 uCameraPos;
uniform float uSize;
uniform vec3 uOffset;
uniform vec4 uColor;
uniform mat4 uVP;

out vec4 color;
out vec2 uv;

void main()
{
   uv = vPos.xy ;
   vec3 initTranslation = vPos - vec3(0.5, 0.5, 0);
   initTranslation = uSize * initTranslation ;
   color = uColor;
   

   vec3 z = normalize(uCameraPos - uOffset);
   vec3 x = cross(vec3(0,1,0), z);
   vec3 y = cross(z, x);

   mat3 R = mat3(x, y, z);
   vec3 finalRenderVec = R * initTranslation;
   finalRenderVec = finalRenderVec + uOffset;

   gl_Position =  uVP *  vec4(finalRenderVec , 1.0);
   //gl_Position =  vec4(vPos , 1.0);

}
