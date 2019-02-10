#include <client/Player.hpp>

#include <quartz/core/math/Ray.hpp>

using namespace client;

Player::Player(qz::gfx::IWindow* window,qz::voxels::ChunkManager* world)
	: m_window(window), m_world(world)
{
	m_camera = std::make_unique<qz::gfx::FPSCam>(window);
	m_camera->enabled = true;

	window->addKeyCallback(events::KeyEventType::PRESSED, events::Keys::KEY_ESCAPE, [&]() {
		m_camera->enabled = !m_camera->enabled;
		if (m_camera->enabled)
		{
			m_window->setCursorState(gfx::CursorState::DISABLED);
		}
		else
		{
			m_window->setCursorState(gfx::CursorState::NORMAL);
		}
	});

	window->addMouseActionCallback(std::bind(&Player::onMouseClick, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void Player::tick(float dt)
{
	m_camera->update(dt);
}

qz::Vector3 Player::getPosition() 
{
	return m_camera->getPosition();
}

void Player::applyTo(qz::gfx::gl::ShaderPipeline* shader)
{
	shader->setMat4("u_projection", m_camera->getProjection());
	shader->setMat4("u_view", m_camera->calculateViewMatrix());
}

void Player::onMouseClick(TVector2<int> position, events::MouseAction action, events::MouseButton button)
{
	using namespace events;
	using namespace voxels;

	auto playerCoordsToBlockCoords = [](Vector3 playerPos) -> Vector3 {
		playerPos = playerPos / 2.f;
		playerPos += 0.5f;
		
		return playerPos;
	};

	auto canPlaceBlockAtPos = [](Vector3 pos) -> bool {
		return pos.x > 0.f && pos.y > 0.f && pos.z > 0.f;
	};

	if (action == MouseAction::DOWN && m_camera->enabled)
	{
		Vector3 pos = playerCoordsToBlockCoords(m_camera->getPosition());

		const float MAX_PICKING_DISTANCE = 32.f;
		const float RAY_INCREMENT = 0.5f;

		switch (button)
		{
		case MouseButton::LEFT:
		{
			Ray ray(pos, m_camera->getDirection());
			
			while (ray.getLength() < MAX_PICKING_DISTANCE)
			{
				pos.floor();
				BlockInstance block = m_world->getBlockAt(pos);

				if (block.getBlockType() != BlockType::GAS)
				{
					LDEBUG("Ray is at: ", pos.x, " ", pos.y, " ", pos.z, "Block Type is: ", block.getBlockID().c_str());
					m_world->breakBlockAt(pos, BlockInstance("core:air"));
					break;
				}

				pos = ray.advance(RAY_INCREMENT);
			}

			break;
		}

		case MouseButton::RIGHT:
			Ray ray(pos, m_camera->getDirection());

			while (ray.getLength() < MAX_PICKING_DISTANCE)
			{
				pos.floor();
				BlockInstance block = m_world->getBlockAt(pos);

				if (block.getBlockType() != BlockType::GAS)
				{
					pos = ray.backtrace(RAY_INCREMENT);

					LDEBUG("Ray is at: ", pos.x, " ", pos.y, " ", pos.z);
					m_world->placeBlockAt(pos, BlockInstance("core:grass"));

					break;
				}

				pos = ray.advance(RAY_INCREMENT);
			}

			break;
		}
	}
}
