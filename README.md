# QUARTZ ENGINE

## Development

#### Dependencies

- CMake (Version >= 3.0)
- A C++11 compatible compiler. The following have been tested
  - Visual Studio 2017 (MSVC 14.10)

#### Building

- Either clone https://github.com/GentenStudios/quartz-engine or fork and then clone your fork. You will have to either clone with the
``--recursive`` option, or you can run: ``git submodule update --init`` after cloning.

- Run `cmake -H. -Bbuild` inside the root directory

- Then either build with `cmake --build build` or follow the instructions for your compiler

  ##### Visual Studio

  - Right click on `quartz-sandbox` and click `Set as StartUp project`
  - Click `Local Windows Debugger` to run

  ##### Make

  - run `cd build` and then `make`.
  - Run the resulting binary



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
