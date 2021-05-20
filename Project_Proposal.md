# Final Project

## Table of Contents
1. [Main_Idea](#Main_Idea)
2. [Features](#Features)
3. [Timeline](#Timeline)
4. [Algorithms](#Algorithms)

## Main_Idea
For the Final project, I am trying to create a simulator for contrails created by planes. The motivation behind is that we have worked with particles systems and meshes in previous two labs. So, for final project, I am trying to add velocity to the plane and add smoke particles to give a natural look.

## Basic_Features
1. Create particles
2. Upload Plane Models
3. Rotate camera using Mouse
4. Create contrails
5. Zoom in and Zoom out (using keyboard and mouse)
6. Adding sky background to give real look

## Additional work
1. Move plane (currently stationary)
2. Add texture to the plane

## Timeline
- This week
  -  Set up basic Environment like view window, camera, make files etc.
  -  uploading meshes, creating particles and generating contrails
  -  Camera Rotation
  -  Zoom in Zoom out
  -  adding velocity to the plane
- Next Week
  - Move incomplete task from last week if any
  - work on Additional features

## Algorithms
- **Camera**
  - The camera roatates using mouse click and cursor positions.
  - The Shift key and mouse cursor are used together to zoom in and zoom out.
  - Formula for camera totation and zooming:

  x = Dist * sin(Azimuth) * cos(Elevation)

  y = Dist * sin(Elevation)

  z = Dist * cos(Azimuth) * cos(Elevation)

- **SKY BOX**
  - Skybox is implemented using new class SkyBox.
  - The Size of the box is 6.0f.
  - SkyBoc.h and SkyBox.cpp are the files to imeplement skybox.
  - skybox.vs and skybox.fs are the shader files which imeplement the skybox.
  - With texture this is what the skybox looks like: 
  
  <img width="498" alt="Screen Shot 2021-05-20 at 2 48 13 PM" src="https://user-images.githubusercontent.com/60520906/119032712-7d0bb500-b97a-11eb-981c-bd80bd2b1ede.png">
  
  - The six textures are mapped correctly using trial and error method.

- **Particle**
  - myParticle.cc and myPaerticle.h files are used to implement particles
  - All particles are placed in a line starting from the end positon of the plane.
  - the initial size is zero for all the particles.
  - the size and positon increase with time, dt.
  - when the parrticle goes out of 3.0f cube, the size is set to zero and the position is set to the initial popsition.
  - billboard.vs and billboard.fs are the shaders file for particles.

- **Plane** 
  - the Plane is implemented using mesh.h and mesh.cpp class. 
  - phongPerFrag.vs and phongPerFrag.fs are the shaders file for the plane.
  - the shaders are per fragment shaders.

- **Final Implementation Algorithm:**
  - There are sepatation set up codes for back ground, particles and meshes outside of while loop where I render the objects.
  - I use shader Ids to render background, particles and the plane.
  - Rendering Algorithms:
    - set background shader as the active shader using glUseProgram(shaderBackGroundId) and then draw background;
    - set particle shader as the active shader using glUseProgram(shaderParticleId) and then draw particles;
    - lastly, set the plane shaders as the active shader using glUseProgram(shaderPlaneId); and then draw the meshes
  
