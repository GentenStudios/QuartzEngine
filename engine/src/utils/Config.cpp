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
	m_configfiles.insert(std::make_pair(name, ConfigFile(name + ".ini")));
	
	ConfigFile *configFile = &m_configfiles[name];
	configFile->reload(); // do inital load

	return configFile;
}

ConfigFile * ConfigManager::getConfigFile(const std::string & name)
{
	// Config file has not been registered so return nullptr.
	if (m_configfiles.find(name) == m_configfiles.end())
	{
		static ConfigFile file;
		LWARNING("Config file \"", name, "\" has not been registered. Returning default config file.");
		return &file;
	}
	return &m_configfiles[name];
}

int ConfigFile::getInteger(const std::string & section, const std::string & key, int default)
{
	return m_inifile.GetInteger(section, key, default);
}

char ConfigFile::getChar(const std::string & section, const std::string & key, char default)
{
	// INI has no concept of single characters only strings, so parse the first letter of the value string as the character.
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

events::Keys ConfigFile::getScancode(const std::string & section, const std::string & key, events::Keys default)
{
	// See https://wiki.libsdl.org/SDL_Keycode for a full map of Key Names -> Key Codes -> Scancodes

	SDL_Keycode defaultKey = SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(default));
	const char* defaultName = SDL_GetKeyName(defaultKey);
	
	std::string value = m_inifile.Get(section, key, defaultName);
	return static_cast<events::Keys>(SDL_GetScancodeFromName(value.c_str()));
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
