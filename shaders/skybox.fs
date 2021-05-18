#version 400

in vec3 color;
in vec2 uv;

uniform samplerCube cubeBoxTex;  //the cube map
// uniform bool drawSkyBox;  //are we drawing the cube?
// uniform float reflactFactor;
// uniform vec4 materialColor;

out vec4 FragColor;


void main()
{
   FragColor = texture(cubeBoxTex, uv);
   // if(drawSkyBox)
   // {
   //    FragColor = cubeMapColor;
   // }
   // else
   // {
   //    FragColor = mix(materialColor, cubeMapColor, reflactFactor);
   // }
   
}

