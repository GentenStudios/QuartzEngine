#pragma once

/**
 * @brief The universal namespace for all official Phoenix code.
 *
 * @details ONLY Phoenix based code should be placed inside the PHX namespace.
 *			Things like ENUMs, Classes, Functions, Structs, and similar should be placed inside the PHX Namespace,
 *			and in any required sub-namespaces.
 */
namespace phx
{
	/**
	 * @brief The namespace for Event related code.
	 */
	namespace events
	{}

	/**
	 * @brief The Namespace for Graphical Related code.
	 *
	 * @details This namespace should only contain code related to the graphical part of the engine, so things like the OpenGL
	 *			Abstraction Layer should go in here, along with something like a HUD system, etc...
	 */
	namespace gfx
	{
		/**
		 * @brief The Namespace for	specifically OpenGL related code.
		 *
		 * @details This namespace is mainly just for the OpenGL Abstraction Layer, nothing much else.
		 *			The renderer we create later on can use this namespace, but WON'T be in it.
		 */
		namespace gl
		{}
	}
}
