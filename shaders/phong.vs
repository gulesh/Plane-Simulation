#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNor;

out vec3 color;

struct ligthtInfo
{
   vec3 position; //light position 
   vec3 color; //color of light
};

struct materialInfo
{
   vec3 Ka; //ambient reflectivity 
   vec3 Kd; // diffuse reflectivity
   vec3 Ks; //specular reflectivity 
   float shininess; //specular light intensity 
};

uniform ligthtInfo uLight;
uniform materialInfo uMaterial;
uniform mat4 uMV;
uniform mat3 uNMV;
uniform mat4 uMVP;

void main()
{
   
   vec3 eNormal = normalize(uNMV * vNor);
   vec4 ePos = uMV * vec4(vPos, 1.0);

   vec3 ambient = uLight.color * uMaterial.Ka;

   vec3 s = normalize(uLight.position.xyz - ePos.xyz); //light source
   float angle = max(dot(s, eNormal), 0.0);
   vec3 diffuse = uLight.color * angle * uMaterial.Kd;

   vec3 v = normalize(-ePos.xyz); //viewpos vector
   vec3 r = reflect(-s, eNormal);
   
   
   float cosPhi = dot(v, r); 
   float positivePhi = max(0.0f, cosPhi);
   vec3 specular = vec3(0.0);
   if(angle > 0.0)
   {
      specular = uLight.color * uMaterial.Ks * pow(positivePhi, uMaterial.shininess); 
   }

   color = ambient + diffuse + specular;
   //color =  vec3(pow(positivePhi, uMaterial.shininess), 0, 0);
   
   gl_Position = uMVP * vec4(vPos, 1.0);
}


