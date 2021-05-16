
#ifndef meshmodel_H_
#define meshmodel_H_

#include "AGLM.h"

namespace agl {
   class Mesh
   {
   public:

      Mesh();

      virtual ~Mesh();

      // Initialize this object with the given file
      // Returns true if successfull. false otherwise.
      bool loadPLY(const std::string& filename);

      // Return the minimum point of the axis-aligned bounding box
      glm::vec3 getMinBounds() const;

      // Return the maximum point of the axis-aligned bounding box
      glm::vec3 getMaxBounds() const;

      // Return number of vertices in this model
      int numVertices() const;

      // Positions in this model
      float* positions() const;

      // Normals in this model
      float* normals() const;

      // Texture in this model
      float* textures() const;

      // Return number of faces in this model
      int numTriangles() const;

      // face indices in this model
      unsigned int* indices() const;
   
   private:
   float* meshPositions;
   float* meshNormals;
   float* meshTextures;
   unsigned int* meshIndices;
   int verticesNum;
   int trianglesNum;
   glm::vec3 minVector = glm::vec3(999999.0f);
   glm::vec3 maxVector = glm::vec3(-9999999.0f);
   };

}

#endif
