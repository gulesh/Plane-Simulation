#ifndef MyParticleSystem_H_
#define MyParticleSystem_H_

#include "particlesystem.h"

namespace agl {

   class MyParticleSystem : public ParticleSystem {
   public:
      virtual void createParticles(int size) override;
      virtual void update(float dt) override;

      glm::vec3 getOffset() {return offset;}
      glm::vec3 getCurrentPlanePosition() {return currentPlanePosition;}

      void setoffset(glm::vec3 value){ offset = value;}
      void setCurrentPlanePosition(glm::vec3 value) {currentPlanePosition = value;}
   private:
      glm::vec3 offset;
      glm::vec3 currentPlanePosition;
   };

}
#endif