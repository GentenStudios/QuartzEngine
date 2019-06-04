[![Build status](https://ci.appveyor.com/api/projects/status/ryoqb5xj56jq0e04?svg=true)](https://ci.appveyor.com/project/GentenStudios/quartz-engine) [![Build Status](https://travis-ci.org/GentenStudios/quartz-engine.svg?branch=develop)](https://travis-ci.org/GentenStudios/quartz-engine)
# QUARTZ ENGINE

## Community
Here is a link to our public discord where we generally collaborate and discuss the development of the engine.
[Here is a link to our public discord server](https://discord.gg/XRttqAm)

## Dependencies

- CMake (Version >= 3.0)
- A C++11 compatible compiler. The following have been tested
  - Visual Studio 2017 (MSVC 14.10)
  - Clang/Clang++ (Clang 7.0.0-3)
- OpenGL (Version >= 3.3)

## Build Instructions
### Visual Studio

Once cloned, enter the directory, by doing `cd quartz-engine`, and complete the following commands:

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

## Coding Standards

#### C++ Features

- Prefer C++ casts over C style casts (e.g. `static_cast` or `const_cast` rather than `(<type>) ... `)
- Try not to use features more modern than C++11, although this isn't a fast rule and is open for discussion.

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
