// Bryn Mawr College, alinen, 2020
//

#include "AGL.h"
#include "AGLM.h"
#include <cmath>
#include "confetti.h"

using namespace std;
using namespace agl;
using namespace glm;

void Confetti::createParticles(int size)
{
  mTexture = theRenderer.loadTexture("../textures/particle.png");

  while (size > 0)
  {
    Particle p{random_unit_cube(), random_unit_cube(), vec4(random_unit_cube(), 1.0), 0.25f, 0.0f};
    mParticles.push_back(p);
    size--;
  }

  // TODO: Create particles
}

void Confetti::update(float dt)
{
  int i = 0;
  int size = mParticles.size();
  vec3 cameraPos = theRenderer.cameraPosition();
  while (i < size)
  {
    Particle p = mParticles[i];
    //changing position
    p.pos = p.pos +  p.vel * dt; // update particle properties
    if (p.pos.x < -1.0f || p.pos.x > 1.0f)
    {
      p.vel.x = -1 * p.vel.x;
    }
    if (p.pos.y < -1.0f || p.pos.y > 1.0f)
    {
      p.vel.y = -1 * p.vel.y;
    }
    if (p.pos.y < -1.0f || p.pos.y > 1.0f)
    {
      p.vel.z = -1 * p.vel.z;
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

}
