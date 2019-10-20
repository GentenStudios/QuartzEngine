[![Build status](https://ci.appveyor.com/api/projects/status/ryoqb5xj56jq0e04?svg=true)](https://ci.appveyor.com/project/GentenStudios/QuartzEngine) [![Build Status](https://travis-ci.org/GentenStudios/quartz-engine.svg?branch=develop)](https://travis-ci.org/GentenStudios/QuartzEngine)
# QUARTZ ENGINE

## Community
[Here's a link to our public discord server](https://discord.gg/XRttqAm), where we collaborate and discuss the development of the engine.

## Dependencies

- CMake (Version >= 3.0)
- A C++11 compatible compiler. The following have been tested
  - Visual Studio 2017 (MSVC 14.10)
  - Clang/Clang++ (Clang 7.0.0-3)
- OpenGL (Version >= 3.3)

## Build Instructions

Once cloned, navigate to the projects root directory and execute the following commands in a terminal.

  1. `cmake -S. -BBuild`
  2. `cmake --build Build --target QuartzSandbox`

Now follow the platform specific instructions detailed below.

### Visual Studio

  - Open the generated solution file in the `Build/` folder in Visual Studio
  - Set the Startup Project to `QuartzSandbox`.
  - At this point you should be able to run, since the project should have already been
    built in step 2. above. You can always build the traditional way with Visual Studio.
  - And voila, all done. Now you should be able to run the project!

### Linux, Mac OS X, MSYS
 
  - Navigate to the `Build/` folder and run `./QuartzSandbox` to run the executable.

## Coding Standards

[Here's a link to our Coding Standards.](https://github.com/GentenStudios/Genten/wiki/Dev:-Home)
You can also have a look at our [wiki](https://github.com/GentenStudios/quartz-engine/wiki) for more information..
