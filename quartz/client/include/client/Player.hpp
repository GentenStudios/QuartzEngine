#pragma once

#define PHX_MAIN_HANDLED
#include <Phoenix.hpp>

#include <memory>

namespace client
{
	class Player
	{
	public:
		Player(phx::gfx::IWindow* window, phx::voxels::ChunkManager* world);

		void tick(float dt);
		phx::Vector3 getPosition();

		void applyTo(phx::gfx::gl::ShaderPipeline* shader);
	
	private:
		void onMouseClick(TVector2<int> position, events::MouseAction action, events::MouseButton button);
	
	private:
		std::unique_ptr<phx::gfx::FPSCam> m_camera;
		phx::gfx::IWindow*                m_window;
		phx::voxels::ChunkManager*        m_world;
	};
}