// Copyright 2019 Genten Studios
// 
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
// following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the 
// following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the 
// following disclaimer in the documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote 
// products derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
// DAMAGE.

#pragma once

/**
 * @brief The universal namespace for all official Phoenix code.
 *
 * ONLY Phoenix based code should be placed inside the PHX namespace.
 * Things like ENUMs, Classes, Functions, Structs, and similar should be placed inside the PHX Namespace,
 * and in any required sub-namespaces.
 */
namespace qz
{
	/**
	 * @brief The namespace for Event related code.
	 */
	namespace events
	{}

	/**
	 * @brief The Namespace for Graphical Related code.
	 *
	 * This namespace should only contain code related to the graphical part of the engine, so things like the OpenGL
	 * Abstraction Layer should go in here, along with something like a HUD system, etc...
	 */
	namespace gfx
	{
		/**
		 * @brief The Namespace for Graphical API Abstraction code.
		 */
		namespace rhi
		{
			/**
			 * @brief The Namespace for	specifically OpenGL related code.
			 *
			 * This namespace is mainly just for the OpenGL Abstraction Layer, nothing much else.
			 * The renderer we create later on can use this namespace, but WON'T be in it.
			 */
			namespace gl
			{
			}
		}
	}
}

