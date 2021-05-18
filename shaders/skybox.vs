#version 400

layout (location = 0) in vec3 vPos;
//layout (location = 1) in vec3 vNor;
//layout (location = 2) in vec2 vText;

out vec3 color;
out vec3 uv;

//out vec3 Normal;
//uniform bool drawSkyBox;
//uniform vec3 uCameraPos;

uniform mat4 uMV;
uniform mat3 uPV;

//uniform mat3 uNMV;
//uniform mat4 uMVP;
//uniform float time;
//uniform vec3 dir;



void main()
{
   //if (drawSkyBox) 
   //{
     // reflectDir = vPos;
   //}
   //else
   //{
     // vec3 worldPos = vec3( uMV * vec4(vPos, 1.0) );
     // vec3 worldNor = vec3( uMV * vec4(vNor, 0.0) );
     // vec3 worldView = normalize( uCameraPos - worldPos );
    //  reflectDir = reflect( -worldView, worldNor );
   //}

   uv = vPos.xy;
   color = vPos;
   gl_Position =  uPV * uMV * vec4(vPos, 1.0);
}


