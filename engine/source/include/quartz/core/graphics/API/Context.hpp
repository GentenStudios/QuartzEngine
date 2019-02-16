#pragma once

#include <quartz/core/Core.hpp>

namespace qz
{
	namespace gfx
	{
		enum class RenderingAPI
		{
			NONE, OPENGL
		};

		class QZ_API Context
		{
		public:
			static RenderingAPI getRenderingAPI();

		private:
			static RenderingAPI m_renderingAPI;

			static void setRenderingAPI(RenderingAPI api);

			friend class IWindow;
		};
	}
}
