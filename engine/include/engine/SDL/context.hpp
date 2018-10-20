#pragma once

#include "engine/common.hpp"
#include <SDL.h>

namespace phx
{
	namespace sdl
	{

		enum class GLProfile {
			CORE = SDL_GL_CONTEXT_PROFILE_CORE,
			COMPATABILITY = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY,
			ES = SDL_GL_CONTEXT_PROFILE_ES
		};

		struct GLVersion {
			int major;
			int minor;
		};

		enum class Feature {
			DOUBLEBUFFER = SDL_GL_DOUBLEBUFFER,
		};

		enum class Attribute {
			BUFFER_SIZE = SDL_GL_BUFFER_SIZE,
			DEPTH_SIZE = SDL_GL_DEPTH_SIZE,
			STENCIL_SIZE = SDL_GL_STENCIL_SIZE,
			MULTISAMPLE_BUFFERS = SDL_GL_MULTISAMPLEBUFFERS,
			MULTISAMPLE_SAMPLES = SDL_GL_MULTISAMPLESAMPLES,
		};

	}
}
