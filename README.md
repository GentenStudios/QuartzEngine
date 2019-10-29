[![Build status](https://ci.appveyor.com/api/projects/status/ryoqb5xj56jq0e04?svg=true)](https://ci.appveyor.com/project/GentenStudios/QuartzEngine) [![Build Status](https://api.travis-ci.org/GentenStudios/QuartzEngine.svg?branch=develop)](https://travis-ci.org/GentenStudios/QuartzEngine)
# QUARTZ ENGINE
## Introduction
Quartz Engine is designed to aid the creation of games with a unique approach to adding content. Quartz will provide lightweight, generic game functionality through an API. The primary feature of Quartz is its scripting functionality, allowing engines to be built so game creators can create a game using only scripts while the heavy lifting is driven in C++. The engine may also provide other useful tools to help someone creating a game.

This will be what our genre specific engines (voxel sandbox, first person shooter, adventure) will be built on.

Our first project is coded [Project Phoenix](https://github.com/GentenStudios/quartz-engine/wiki/Project-Phoenix) and is centered around voxels. This is what we will use to test and improve Quartz with during its initial development.

## Community
[Here's a link to our public discord server](https://discord.gg/XRttqAm), where we collaborate and discuss the development of the engine.

## Components
These components make up the features of Quartz
### Lua Scripting
Quartz will provide the ability to load and run lua scripts to add content to a game. This is the main feature of Quartz engine that makes it unique. By design, a launcher application will pass a client or server scripts to load that provide all game content, the C++/ game engine should never provide content on its own.
### Rendering
Quartz will provide an API that engines can use to implement rendering.
### Networking
The library will provide an API that engines can use to implement networking capabilities. This should handle authentication and sending protocols while the specific engine. 
### Logging
The engine will provide basic logging functionality.
### GUI
Currently we will implement ImGUI but a in house solution may be a part of our future plans.

## Dependencies
- CMake (Version >= 3.0)
- A C++17 compatible compiler. The following have been tested
  - Visual Studio 2017 & 2019 (MSVC >= 19.14)
  - Clang (>= 5.0.0)
  - GCC (>= 4.8.4)
- OpenGL (Version >= 3.3)

## Build Instructions
Once cloned, navigate to the projects root directory and execute the following commands in a terminal.

  1. `mkdir Build`
  2. `cd Build`
  3. `cmake ..`
  4. `cmake --build . --target QuartzSandbox`

Now follow the platform specific instructions detailed below.

### Visual Studio
  - Open the generated solution file in the `Build/` folder in Visual Studio
  - Set the Startup Project to `QuartzSandbox`.
  - At this point you should be able to run, since the project should have already been
    built in step 2. above. You can always build the traditional way with Visual Studio.
  - And voila, all done. Now you should be able to run the project!

### Linux, Mac OS X, MSYS
 
  - Navigate to the `Build/QuartzSandbox` folder and run `./QuartzSandbox` to run the executable.

## Coding Standards
[Here's a link to our Coding Standards.](https://github.com/GentenStudios/Genten/wiki/Dev:-Home)
You can also have a look at our [wiki](https://github.com/GentenStudios/quartz-engine/wiki) for more information..
