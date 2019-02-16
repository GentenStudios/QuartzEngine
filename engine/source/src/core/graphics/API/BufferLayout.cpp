#include <quartz/core/QuartzPCH.hpp>
#include <quartz/core/graphics/API/BufferLayout.hpp>

using namespace qz::gfx::api;
using namespace qz::gfx;

void BufferLayout::registerAttribute(const std::string& name, DataType type, int count, int stride, std::size_t offset, bool normalised)
{
	m_bufferLayout.push_back({ name, type, count, stride, offset, normalised });
}

void BufferLayout::registerAttribute(BufferAttribute attribute)
{
	m_bufferLayout.emplace_back(attribute);
}

const std::vector<BufferAttribute>& BufferLayout::getLayouts() const
{
	return m_bufferLayout;
}
