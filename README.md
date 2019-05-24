[![Build status](https://ci.appveyor.com/api/projects/status/ryoqb5xj56jq0e04?svg=true)](https://ci.appveyor.com/project/GentenStudios/quartz-engine) [![Build Status](https://travis-ci.org/GentenStudios/quartz-engine.svg?branch=develop)](https://travis-ci.org/GentenStudios/quartz-engine)
# QUARTZ ENGINE

## Dependencies

- CMake (Version >= 3.0)
- A C++11 compatible compiler. The following have been tested
  - Visual Studio 2017 (MSVC 14.10)
  - Clang/Clang++ (Clang 7.0.0-3)
- OpenGL (Version >= 3.3)

## Build Instructions
### Visual Studio

Once cloned, enter the directory, by doing `cd quartz-engine``, and complete the following commands:

<dl>
cmake -H. -BBuild
cmake --build Build
</dl>

### Linux, Mac OS X, MSYS

  1. `mkdir build && cd build`
  2. `cmake ..`
  3. `make`¹

### Linux cross-compile to Windows

  1. `mkdir build && cd build`
  2. `cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/cross-toolchain-mingw32.cmake ..`²
  3. `make`¹

¹ *Use `make -j$(nproc)` to speed up compilation by using all CPU cores (`make -jN` for `N` threads).*  
² *Use `cross-toolchain-mingw64.cmake` for a Win64 build.*

These commands will take a fair amount of time to complete, the first one configures the project and appropriate compilers, whereas the second command actually builds the project using those configurations. To run the executable, for MSVC/Windows users, go into Build/QuartzSandbox and move QuartzSandbox.exe out of Debug and into this folder. You can then run it.

An alternative way of building is executing the initial cmake -H. -BBuild command to generate Visual Studio Solution files, After doing so, go into the Build folder, and open Quartz.sln. Then find the build button and press it, or press F5. The initial run of the application may fail and there will be an error about a startup project. If so, locate the QuartzSandbox project in the sidebar, and right click, then select Set as Startup Project, then press F5 or the Run button.

Voila! You've successfully built QuartzEngine and run the sandbox application, now feel free to start contributing in any way you can!

## Coding Standards

#### Comments

Declarations should be doxygen commented using the Javadoc syntax. For example

```
/**
 * @brief This class is for documentation reasons. 
 */
class FooBar {
public:
	/**
	 * @brief This does an important thing
	 * @param desc A description of the thing
	 * @return A very important integer. (probably an error code or something)
	 */
  	int doThing(std::string desc);
  	
  	float randomNumber; //< This is a single line description for a member
};
```

#### Naming & Formatting

- Braces should start on a newline
- Class names should be pascal case - e.g `PascalCase`
- Variables and functions should use camel case `camelCase` or `void thingyBob();`
- Namespaces should start with a lowercase letter e.g `namespace phoenix`
- Constants and macros should be all uppercase with words separated by underscores `A_CONSTANT` 
- Private member variables should start with the `m_` prefix. E.g `int m_playerHealth;`
- Also don't get too hung up on this sort of stuff. At the end of the day it's not that important.

#### C++ Features

- Prefer C++ casts over C style casts (e.g. `static_cast` or `const_cast` rather than `(<type>) ... `)
- Try not to use features more modern than C++11, although this isn't a fast rule and is open for discussion.


## Community
Here is a link to our public discord where we generally collaborate and discuss the development of the engine.
https://discord.gg/RBsZh4
