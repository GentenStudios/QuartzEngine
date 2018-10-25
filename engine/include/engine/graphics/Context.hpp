#pragma once

#include "engine/common.hpp"

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
