#pragma once

#include <engine/core/Core.hpp>

namespace phx
{
	namespace gfx
	{

		enum class GLProfile {
			CORE,
			COMPATABILITY,
			ES
		};

		struct GLVersion {
			int major;
			int minor;
		};

	}
}
