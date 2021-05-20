# Plane_Contrails
This is a demonstration of the contrails created by the planes in the sky.

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
particles $ mkdir build
particles $ cd build
particles/build $ cmake -G "Visual Studio 16 2019" ..
particles/build $ start Plane_Contrails.sln
```

Your solution file should contain two projects: `pixmap_art` and `pixmap_test`.
To run from the git bash command shell, 

```
particles/build $ ../bin/Debug/scene
```

*macOS*

Open terminal to the directory containing this repository.

```
particles $ mkdir build
particles $ cd build
particles/build $ cmake ..
particles/build $ make
```

To run each program from build, you would type

```
particles/build $ ../bin/scene
```

## Results

**Main Objects**

- a **skybox** is mapped on a cube to form the backgeround. 

![cubemaps_skybox](https://user-images.githubusercontent.com/60520906/119030314-b5f65a80-b977-11eb-943e-577909ff29ab.png)

- a **plane** is loaded in the model using meshes

<img width="497" alt="Screen Shot 2021-05-20 at 2 31 02 PM" src="https://user-images.githubusercontent.com/60520906/119030957-8ac03b00-b978-11eb-9e0c-fe3cf6e9c704.png">


- The **smoke (contrails)** is formed using cloud image.
 
<img width="493" alt="Screen Shot 2021-05-20 at 2 33 13 PM" src="https://user-images.githubusercontent.com/60520906/119031023-a0cdfb80-b978-11eb-9395-4b6f8c1ccac3.png">

- All objects combined give the following image:

<img width="491" alt="Screen Shot 2021-05-20 at 1 24 55 PM" src="https://user-images.githubusercontent.com/60520906/119022634-dec62200-b96e-11eb-89c6-13de7d2285bc.png">

## Algorithms and Data structures

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
  
**Project Demo** 

https://user-images.githubusercontent.com/60520906/119023339-b8ed4d00-b96f-11eb-833e-2820a7a6d8e0.mov

