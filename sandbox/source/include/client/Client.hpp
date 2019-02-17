#pragma once

#include <Quartz.hpp>

namespace client
{
	class Sandbox : public qz::Application
	{
	public:
		Sandbox();
		~Sandbox() = default;

		const ApplicationRequirements* getAppRequirements() override { return m_appRequirements; }
		void setAppData(qz::ApplicationData* appData) override { m_appData = appData; }

		void run() override;

		void onEvent(events::Event& e);
		bool onKeyPress(events::KeyPressedEvent& e);
		bool onClose(events::WindowCloseEvent& e);

	private:
		qz::ApplicationRequirements* m_appRequirements = nullptr;
		qz::ApplicationData* m_appData = nullptr;

		qz::gfx::FPSCamera* m_camera;
	};
}

inline qz::Application* qz::createApplication()
{
	return new client::Sandbox();
}
