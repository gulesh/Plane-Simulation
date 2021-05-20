#ifndef SKYBOX_H
#define SKYBOX_H
#include "AGL.h"

class SkyBox 
{
private:
    unsigned int vaoHandle;

public:
    SkyBox(int size);

    void render() const;
};


#endif // SKYBOX_H
