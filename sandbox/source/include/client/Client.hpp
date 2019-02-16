#pragma once

#include <Quartz.hpp>

#include <memory>

namespace client
{
	class Sandbox : public qz::Application
	{
	public:
		Sandbox();
		~Sandbox() = default;

		const qz::ApplicationRequirements* getRequirements() { return m_appRequirements; }
		void setAppData(qz::ApplicationData* appData) { m_appData = appData; }

		void run();

	private:
		qz::ApplicationRequirements* m_appRequirements = nullptr;
		qz::ApplicationData* m_appData = nullptr;
	};
}
