#include <quartz/core/QuartzPCH.hpp>
#include <quartz/core/math/Ray.hpp>

using namespace qz;

Ray::Ray(const Vector3& start, const Vector3& direction)
	: m_start(start), m_direction(direction), 
	m_currentPosition(start), m_length(0.f)
{
}

Vector3 Ray::advance(float scale)
{
	m_currentPosition += m_direction * scale;
	m_length += scale;

	return m_currentPosition;
}

Vector3 Ray::backtrace(float scale)
{
	m_currentPosition -= m_direction * scale;
	m_length -= scale;

	return m_currentPosition;
}

float Ray::getLength() const
{
	return m_length;
}

Vector3 Ray::getCurrentPosition() const
{
	return m_currentPosition;
}
