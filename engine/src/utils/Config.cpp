#include "engine/utils/Config.hpp"

#include "engine/utils/logging.hpp"

#include <fstream>

using namespace phx;

ConfigManager* ConfigManager::get()
{
	static ConfigManager m;
	return &m;
}

ConfigFile *ConfigManager::registerConfig(const std::string & name)
{
	m_configfiles[name] = ConfigFile(name + ".ini");
	ConfigFile *f = &m_configfiles[name];

	f->reload(); // do inital load
	return f;
}

ConfigFile * ConfigManager::getConfigFile(const std::string & name)
{
	return &m_configfiles[name];
}

int ConfigFile::getInteger(const std::string & section, const std::string & key, int default)
{
	return m_inifile.GetInteger(section, key, default);
}

char ConfigFile::getChar(const std::string & section, const std::string & key, char default)
{
	return m_inifile.Get(section, key, std::string(default, 1))[0];
}

bool ConfigFile::getBool(const std::string & section, const std::string & key, bool default)
{
	return m_inifile.GetBoolean(section, key, default);
}

float ConfigFile::getFloat(const std::string & section, const std::string & key, float default)
{
	return static_cast<float>(m_inifile.GetReal(section, key, static_cast<float>(default)));
}

SDL_Scancode phx::ConfigFile::getScancode(const std::string & section, const std::string & key, SDL_Scancode default)
{
	SDL_Keycode defaultKey = SDL_GetKeyFromScancode(default);
	const char* defaultName = SDL_GetKeyName(defaultKey);
	
	std::string value = m_inifile.Get(section, key, defaultName);
	return SDL_GetScancodeFromName(value.c_str());
}

bool ConfigFile::existsOnDisk() const
{
	return !!std::ifstream(m_filepath);
}

void ConfigFile::reload()
{
	m_inifile = INIReader(m_filepath);
	if (!existsOnDisk())
	{
		LWARNING("Config file \"", m_filepath, "\" does not exist on disk. Default's will be used instead.");
	}
}
