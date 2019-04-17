[![Build status](https://ci.appveyor.com/api/projects/status/ryoqb5xj56jq0e04?svg=true)](https://ci.appveyor.com/project/GentenStudios/quartz-engine) [![Build Status](https://travis-ci.org/GentenStudios/quartz-engine.svg?branch=develop)](https://travis-ci.org/GentenStudios/quartz-engine)
# QUARTZ ENGINE

## Community

Here is a link to our public discord where we generally collaborate and discuss the development of the engine.
https://discord.gg/5JmwPJf

## Development

#### Dependencies

- CMake (Version >= 3.0)
- A C++11 compatible compiler. The following have been tested
  - Visual Studio 2017 (MSVC 14.10)
  - Clang/Clang++ (Clang 7.0.0-3)
- OpenGL (Version >= 3.3)

#### Building

- (https://help.github.com/en/articles/cloning-a-repository) Clone https://github.com/GentenStudios/quartz-engine using GitBash or fork (https://help.github.com/en/articles/fork-a-repo) and then clone (See beginning of sentence) your fork.

- Inside of the folder that you've just cloned right click on an empty space and click GitBash Here.

- Then run cmake -H. -Bbuild in the terminal

  ##### Visual Studio

  - Open up Quartz.sln in Visual Studios
  - Click on the Build tab at the top of VS
  - Then click Build Solution
  
  - After it's built go to the folder for the engine search .exe
  - Move QuartzSandbox.exe file to the QuartzSandbox folder


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
