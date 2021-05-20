# Plane_Contrails

**Image_Preview of the Project**

<img width="491" alt="Screen Shot 2021-05-20 at 1 24 55 PM" src="https://user-images.githubusercontent.com/60520906/119022634-dec62200-b96e-11eb-89c6-13de7d2285bc.png">

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

**Project Demo** 

https://user-images.githubusercontent.com/60520906/119023339-b8ed4d00-b96f-11eb-833e-2820a7a6d8e0.mov

