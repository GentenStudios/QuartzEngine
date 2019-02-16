#include <quartz/core/QuartzPCH.hpp>
#include <quartz/core/graphics/API/Context.hpp>

using namespace qz::gfx;

RenderingAPI Context::m_renderingAPI = RenderingAPI::NONE;

RenderingAPI Context::getRenderingAPI()
{
	return m_renderingAPI;
}

void Context::setRenderingAPI(RenderingAPI api)
{
	m_renderingAPI = api;
}
