#version 400

in vec3 recDir;
in vec2 uv;

uniform samplerCube cubeBoxTex;  //the cube map
out vec4 FragColor;

void main()
{
   FragColor = texture(cubeBoxTex, recDir);
}

