#include <engine/core/graphics/Renderer2D.hpp>
#include <engine/core/utils/IO.hpp>

#include <assert.h>

using namespace phx::gfx;
using namespace phx;

static const int MAX_RENDERABLES = 10000;
static const int MAX_VERTICES    = MAX_RENDERABLES * 4;
static const int MAX_INDICES     = MAX_RENDERABLES * 6;

Renderer2D::Renderer2D(const Matrix4x4& projectionMatrix, const std::string& vertexShader, const std::string& fragmentShader)
	: m_indexOffset(0)
{
	m_shader.addStage(gl::ShaderType::VERTEX_SHADER, File::readFile(vertexShader).c_str());
	m_shader.addStage(gl::ShaderType::FRAGMENT_SHADER, File::readFile(fragmentShader).c_str());
	m_shader.build();
	m_shader.use();
	m_shader.setMat4("u_projection", projectionMatrix);

	m_batchRenderer.create(MAX_VERTICES, MAX_INDICES, m_shader);
}

void Renderer2D::fillRectangle(const Vector2& position, float width, float height, const Color3& color)
{
	assert(m_batchRenderer.isReadyForDrawing());

	Vector3 pos3 = Vector3(position.x, position.y, 0.f);

	const float Z = 0.f;

	m_batchRenderer.addVertex(Vertex3D(pos3, color));
	m_batchRenderer.addVertex(Vertex3D(pos3 + Vector3(width, 0.f, Z), color));
	m_batchRenderer.addVertex(Vertex3D(pos3 + Vector3(width, height, Z), color));
	m_batchRenderer.addVertex(Vertex3D(pos3 + Vector3(0.f, height, Z), color));
	
	m_batchRenderer.addIndex(m_indexOffset);
	m_batchRenderer.addIndex(m_indexOffset + 1);
	m_batchRenderer.addIndex(m_indexOffset + 2);
	m_batchRenderer.addIndex(m_indexOffset + 2);
	m_batchRenderer.addIndex(m_indexOffset + 3);
	m_batchRenderer.addIndex(m_indexOffset);

	m_indexOffset += 4;
}

void Renderer2D::fillCircle(const Vector2& position, float radius, size_t noPoints, const Color3& color)
{
	assert(m_batchRenderer.isReadyForDrawing());
	assert(noPoints >= 3);

	const Vector3 centrePos = { position.x, position.y, 0.f };

	const float segmentSize = MathUtils::toRadians(360.f / noPoints);
	for (size_t i = 0; i < noPoints; ++i)
	{
		float angle = segmentSize * i;
		
		Vector3 pos = {
			radius * std::cos(angle) + centrePos.x,
			radius * std::sin(angle) + centrePos.y,
			0.f
		};
		m_batchRenderer.addVertex(Vertex3D(pos, color));

		angle = segmentSize * (i + 1);
		
		pos.x = radius * std::cos(angle) + centrePos.x;
		pos.y = radius * std::sin(angle) + centrePos.y;

		m_batchRenderer.addVertex(Vertex3D(pos, color));

		// middle vertex
		m_batchRenderer.addVertex(Vertex3D(centrePos, color));

		m_batchRenderer.addIndex(m_indexOffset);
		m_batchRenderer.addIndex(m_indexOffset + 1);
		m_batchRenderer.addIndex(m_indexOffset + 2);
		
		m_indexOffset += 3;
	}
}

void Renderer2D::begin()
{
	m_batchRenderer.openBuffer();
}

void Renderer2D::end()
{
	m_batchRenderer.closeBuffer();
}

void Renderer2D::draw()
{
	m_shader.use();
	m_batchRenderer.draw();
	m_indexOffset = 0;
}