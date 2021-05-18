
#include "mesh.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;
using namespace glm;
using namespace agl;

Mesh::Mesh()
{
   meshIndices = NULL;
   meshPositions = NULL;
   meshNormals = NULL;
   meshTextures = NULL;
}

Mesh::~Mesh()
{
   delete[] meshIndices;
   delete[] meshPositions;
   delete[] meshNormals;
   delete[] meshTextures;
}

bool Mesh::loadPLY(const std::string &filename)
{
   minVector = glm::vec3(999999.0f);
   maxVector = glm::vec3(-9999999.0f);
   cout << filename << endl;
   ifstream file(filename);
   if (!file) // true if the file is valid
   {
      cout << "Cannot load file: " << filename << endl;
      return 1;
   }
   string value;
   float num;
   getline(file, value);
   cout << value << endl;
   if (value != "ply")
   {
      return 1;
   }
   getline(file, value); //skipping ascii
   getline(file, value); //skipping another line

   // storing the number of vertices
   getline(file, value);
   value = value.substr(15);

   verticesNum = stoi(value);
   cout << "vertices Num:  " << verticesNum << endl;

   delete[] meshIndices;
   delete[] meshPositions;
   delete[] meshNormals;
   delete[] meshTextures;

   meshPositions = new float[3 * verticesNum];
   meshNormals = new float[3 * verticesNum];

   // getline(file, value);
   int attributeNum = 0;
   string facesNum;

   //skipping three lines
   while (value != "end_header")
   {
      getline(file, value); //skipping ascii
      if (value.substr(0, 13) == "element face ")
      {
         facesNum = value.substr(13);
      }
      // cout << value << endl;
      attributeNum = attributeNum + 1;
   }
   cout << "value after loop: " << value << endl;
   attributeNum = attributeNum - 9; //this is used to see extra features like texture in the file along with normals and vertices
   // cout << attributeNum << endl;
   meshTextures = new float[attributeNum * verticesNum]; //texture buffer

   trianglesNum = stoi(facesNum);
   cout << "traingles num: " << trianglesNum << endl;
   meshIndices = new unsigned int[3 * trianglesNum];

   // //skipping two more lines
   // getline(file, value);
   // getline(file, value);

   if (attributeNum > 0)
   {

      int i = 0;
      int indexV = 0;
      int indexN = 0;
      int indexT = 0;
      //storing the info in the buffers
      while (i < verticesNum)
      {
         //stroing vertices
         file >> num;
         if (num <= minVector.x)
         {
            minVector.x = num;
         }
         if (num >= maxVector.x)
         {
            maxVector.x = num;
         }
         meshPositions[indexV] = num; //x

         file >> num;
         if (num <= minVector.y)
         {
            minVector.y = num;
         }
         if (num >= maxVector.y)
         {
            maxVector.y = num;
         }
         meshPositions[indexV + 1] = num; //y

         file >> num;
         if (num <= minVector.z)
         {
            minVector.z = num;
         }
         if (num >= maxVector.z)
         {
            maxVector.z = num;
         }
         meshPositions[indexV + 2] = num; //z
         indexV = indexV + 3;

         //storing normals
         file >> num;
         meshNormals[indexN] = num;
         file >> num;
         meshNormals[indexN + 1] = num;
         file >> num;
         meshNormals[indexN + 2] = num;
         indexN = indexN + 3;

         while (attributeNum > 0)
         {
            file >> num;
            meshTextures[indexT] = num;
            indexT++;
            attributeNum--;
         }

         i++;
      }
   }
   else
   {
      int i = 0;
      int indexV = 0;
      int indexN = 0;
      //storing the info in the buffers
      while (i < verticesNum)
      {
         //stroing vertices
         file >> num;
         if (num <= minVector.x)
         {
            minVector.x = num;
         }
         if (num >= maxVector.x)
         {
            maxVector.x = num;
         }
         meshPositions[indexV] = num; //x

         file >> num;
         if (num <= minVector.y)
         {
            minVector.y = num;
         }
         if (num >= maxVector.y)
         {
            maxVector.y = num;
         }
         meshPositions[indexV + 1] = num; //y

         file >> num;
         if (num <= minVector.z)
         {
            minVector.z = num;
         }
         if (num >= maxVector.z)
         {
            maxVector.z = num;
         }
         meshPositions[indexV + 2] = num; //z
         indexV = indexV + 3;

         //storing normals
         file >> num;
         meshNormals[indexN] = num;
         file >> num;
         meshNormals[indexN + 1] = num;
         file >> num;
         meshNormals[indexN + 2] = num;
         indexN = indexN + 3;

         i++;
      }
   }

   int j = 0;
   int indexI = 0;
   while (j < trianglesNum)
   {
      file >> num; //this is the number 3
      //stroing vertices
      file >> num;
      meshIndices[indexI] = (unsigned int)num;
      file >> num;
      meshIndices[indexI + 1] = (unsigned int)num;
      file >> num;
      meshIndices[indexI + 2] = (unsigned int)num;
      indexI = indexI + 3;

      j++;
   }

   return true;
}

glm::vec3 Mesh::getMinBounds() const
{
   return minVector;
}

glm::vec3 Mesh::getMaxBounds() const
{
   return maxVector;
}

int Mesh::numVertices() const
{
   return verticesNum;
}

int Mesh::numTriangles() const
{
   return trianglesNum;
}

float *Mesh::positions() const
{
   return meshPositions;
}

float *Mesh::normals() const
{
   return meshNormals;
}

float *Mesh::textures() const
{
   return meshTextures;
}

unsigned int *Mesh::indices() const
{
   return meshIndices;
}

void Mesh::initBuffer()
{
   if (meshIndices == nullptr || meshPositions == nullptr || meshNormals == nullptr)
      return;

   glGenBuffers(1, &mIndicesId);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndicesId);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, trianglesNum * 3 * sizeof(unsigned int), meshIndices, GL_STATIC_DRAW);

   glGenBuffers(1, &mPosId);
   glBindBuffer(GL_ARRAY_BUFFER, mPosId);
   glBufferData(GL_ARRAY_BUFFER, verticesNum * sizeof(float), meshPositions, GL_STATIC_DRAW);

   glGenBuffers(1, &mNormalId);
   glBindBuffer(GL_ARRAY_BUFFER, mNormalId);
   glBufferData(GL_ARRAY_BUFFER, verticesNum * sizeof(float), meshNormals, GL_STATIC_DRAW);

   if (meshTextures != nullptr)
   {
      glGenBuffers(1, &mTextureId);
      glBindBuffer(GL_ARRAY_BUFFER, mTextureId);
      glBufferData(GL_ARRAY_BUFFER, verticesNum * sizeof(float), meshTextures, GL_STATIC_DRAW);
   }

   glGenVertexArrays(1, &mVaoId);
   glBindVertexArray(mVaoId);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndicesId);

   // Position
   glBindBuffer(GL_ARRAY_BUFFER, mPosId);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
   glEnableVertexAttribArray(0); // Vertex position

   // Normal
   glBindBuffer(GL_ARRAY_BUFFER, mNormalId);
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
   glEnableVertexAttribArray(1); // Normal

   // Tex coords
   if (meshTextures != nullptr)
   {
      glBindBuffer(GL_ARRAY_BUFFER, mTextureId);
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(2); // Tex coord
   }

   glBindVertexArray(0);
}

void Mesh::renderer() const {
    if(mVaoId == 0) return;

    glBindVertexArray(mVaoId);
    glDrawElements(GL_TRIANGLES, verticesNum, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

