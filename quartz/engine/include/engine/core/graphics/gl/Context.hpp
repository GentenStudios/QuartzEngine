#pragma once

namespace phx
{
	namespace gfx
	{
		/**
		 * @brief The OpenGL Profile that is wanted.
		 * 
		 * @details OpenGL supports multiple profiles. Core being the most "useful". Compatibility, as in the name offers better compatibility, at the cost of some difficulties.
		 * 			The Core profile is RECOMMENDED.
		 * 			The ES Profile is not yet tested or recommended at all (as of 17th November 2018) as we do not even support mobile devices at this point.
		 * 
		 */
		enum class GLProfile {
			CORE,
			COMPATABILITY,
			ES
		};

		/**
		 * @brief The OpenGL Versions that is used in context creation during the initialization of the window.
		 * 
		 * @details Anything over OpenGL 3.3, is "technically" supported, although we may have some warning for deprecated functions at a later date.
		 * 			We, as of 17th November 2018 (stated by BeeperDeeper089, or Vyom Fadia) DO NOT, AND WILL NOT SUPPORT ANYTHING BEFORE OPENGL 3.3.
		 * 			We will be supported OpenGLES at a later date, but will be sticking with normal, desktop OpenGL for now, due to ease of development.
		 */
		struct GLVersion {
			int glMajor;
			int glMinor;

			GLVersion(int a, int b) :
				glMajor(a),
				glMinor(b)
			{}

			GLVersion() :
				glMajor(0),
				glMinor(0)
			{}
		};

	}
}
