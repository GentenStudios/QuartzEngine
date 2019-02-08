#pragma once

#include <Quartz.hpp>

#include <memory>

namespace client
{
	class Player
	{
	public:
		Player(qz::gfx::IWindow* window, qz::voxels::ChunkManager* world);

		void tick(float dt);
		qz::Vector3 getPosition();

		void applyTo(qz::gfx::gl::ShaderPipeline* shader);
	
	private:
		void onMouseClick(TVector2<int> position, events::MouseAction action, events::MouseButton button);
	
	private:
		std::unique_ptr<qz::gfx::FPSCam> m_camera;
		qz::gfx::IWindow*                m_window;
		qz::voxels::ChunkManager*        m_world;
	};
}