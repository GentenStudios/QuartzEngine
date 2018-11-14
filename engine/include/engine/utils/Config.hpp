#pragma once

#include <string>
#include <unordered_map>
#include <SDL.h>

#include <inih/INIReader.h>

#define PHX_REGISTER_CONFIG(filenameStr) \
	phx::ConfigManager::get()->registerConfig(filenameStr)

#define PHX_GET_CONFIG(filenameStr) \
	phx::ConfigManager::get()->getConfigFile(filenameStr)

namespace phx
{
	class ConfigFile
	{
	public:
		int getInteger(const std::string& section, const std::string& key, int default);
		char getChar(const std::string& section, const std::string& key, char default);
		bool getBool(const std::string& section, const std::string& key, bool default);
		float getFloat(const std::string& section, const std::string& key, float default);
		SDL_Scancode getScancode(const std::string& section, const std::string& key, SDL_Scancode default);

		bool existsOnDisk() const;

		void reload();

		ConfigFile(const std::string& filepath)
			: m_filepath(filepath) {}
		ConfigFile() {}
	private:
		INIReader m_inifile;
		std::string m_filepath;
	};

	class ConfigManager
	{
	public:
		static ConfigManager* get();

		ConfigFile* registerConfig(const std::string& name);
		ConfigFile* getConfigFile(const std::string& name);

	private:
		std::unordered_map<std::string, ConfigFile> m_configfiles;
	};
}