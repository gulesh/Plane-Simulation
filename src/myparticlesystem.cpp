// Bryn Mawr College, alinen, 2020
//

#include "AGL.h"
#include "AGLM.h"
#include "mesh.h"
#include <cmath>
#include "myparticlesystem.h"

using namespace std;
using namespace agl;
using namespace glm;

void MyParticleSystem::createParticles(int size)
{
   mTexture = theRenderer.loadTexture("../textures/ParticleCloudWhite.png");
   float tempDist = 0;
   float psize = 0;
   // mTexture = theRenderer.loadTexture("../textures/particle.png");
   // glm::vec3 offset;
   // glm::vec3 currentPlanePosition;
   // cout << "offsett in mPart: " << offset << "curentposition in mpart: " << currentPlanePosition <<endl;

   while (size > 0)
   {
      Particle p{vec3(0, currentPlanePosition.y + tempDist, 0), vec3(vec3(0, 1, 0)), vec4(1.0, 1.0, 1.0, 1.0), psize, 0.0f};
      // psize = psize + 0.1f;
      tempDist = tempDist + 0.05f;
      mParticles.push_back(p);
      size--;
   }

   // Particle p{vec3(0, currentPlanePosition.y - 0.5, 0), vec3(vec3(0, 1, 0)), vec4(1.0, 1.0, 1.0, 1.0), 10, 0.0f};   
   // mParticles.push_back(p);
   // size--;
}

void MyParticleSystem::update(float dt)
{
   int i = 0;
   int size = (mParticles.size()) / 2;
   vec3 cameraPos = theRenderer.cameraPosition();
   while (i < size)
   {
      Particle p = mParticles[i];
      //changing position
      p.pos = p.pos + p.vel * dt; // update particle properties
      p.size = p.size + 0.009f;
      if (p.pos.y < -4.0f || p.pos.y > 4.0f)
      {
         p.pos.y = currentPlanePosition.y;
         p.size = 0.009;
      }

      if (i != 0)
      {
         Particle p2 = mParticles[i - 1];
         float prevParticleDist = length(p2.pos - cameraPos);
         float currParticleDist = length(p.pos - cameraPos);

         if (currParticleDist > prevParticleDist)
         {
            mParticles[i - 1] = p;
            mParticles[i] = p2;
         }
         else
         {
            mParticles[i] = p;
         }
      }
      else
      {
         mParticles[i] = p;
      }
      // mParticles[i] = p;
      i++;
      // update particles
   }
   // for (int i = 0; i < 10; i++)
   // {
   //    Particle p = mParticles[i];
   //    if(i % 2 == 0 )
   //    {
   //       p.size = 2 * p.size;
   //    }
   //    else
   //    {
   //       p.size = 4 * p.size;
   //    }
     
   // }
   
   // cout<< p.pos <<endl;
}
