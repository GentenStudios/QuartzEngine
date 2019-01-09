#include <engine/core/utils/Config.hpp>
#include <engine/core/utils/Logging.hpp>

#include <SDL.h>

#include <fstream>

using namespace phx;

ConfigManager* ConfigManager::get()
{
	static ConfigManager m;
	return &m;
}

ConfigFile* ConfigManager::registerConfig(const std::string & name)
{
	m_configfiles.insert(std::make_pair(name, ConfigFile(name + ".ini")));
	
	ConfigFile *configFile = &m_configfiles[name];
	configFile->reload(); // do initial load

	return configFile;
}

ConfigFile* ConfigManager::getConfigFile(const std::string & name)
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

int ConfigFile::getInteger(const std::string & section, const std::string & key, int defaultReturn) const
{
	return m_inifile.GetInteger(section, key, defaultReturn);
}

char ConfigFile::getChar(const std::string & section, const std::string & key, char defaultReturn) const
{
	// INI has no concept of single characters only strings, so parse the first letter of the value string as the character.
	return m_inifile.Get(section, key, std::string(defaultReturn, 1))[0];
}

bool ConfigFile::getBool(const std::string & section, const std::string & key, bool defaultReturn) const
{
	return m_inifile.GetBoolean(section, key, defaultReturn);
}

float ConfigFile::getFloat(const std::string & section, const std::string & key, float defaultReturn) const
{
	return static_cast<float>(m_inifile.GetReal(section, key, static_cast<float>(defaultReturn)));
}

events::Keys ConfigFile::getScancode(const std::string & section, const std::string & key, events::Keys defaultReturn) const
{
	// See https://wiki.libsdl.org/SDL_Keycode for a full map of Key Names -> Key Codes -> Scancodes

	SDL_Keycode defaultKey = SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(defaultReturn));
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
