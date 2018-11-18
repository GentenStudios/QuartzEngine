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

		const phx::ApplicationRequirements* getRequirements() { return m_appRequirements; }
		void setAppData(phx::ApplicationData* appData) { m_appData = appData; }

		void run();

	private:
		phx::ApplicationRequirements* m_appRequirements = nullptr;
		phx::ApplicationData* m_appData = nullptr;
	};

}