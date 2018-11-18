#pragma once

//#define PHX_MAIN_HANDLED
#include <Phoenix.hpp>

namespace client
{
	
	class Sandbox : public phx::Application
	{
	public:
		Sandbox();
		~Sandbox();

		void setup(phx::Application::SetupCallback setupCallback);
		void run();

	private:
		phx::ApplicationRequirements* m_appRequirements = nullptr;
		phx::ApplicationData* m_appData = nullptr;
	};

}