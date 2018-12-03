/**
 * @file Config.hpp
 * @brief Class(es) and #defines for Configuration Loading and Interpreting.
 * 
 */

#pragma once

#include <string>
#include <unordered_map>
#include <SDL.h>

#include <inih/INIReader.h>

#include <engine/core/events/Keys.hpp>

#define PHX_REGISTER_CONFIG(filenameStr) \
	phx::ConfigManager::get()->registerConfig(filenameStr)

#define PHX_GET_CONFIG(filenameStr) \
	phx::ConfigManager::get()->getConfigFile(filenameStr)

namespace phx
{
	/**
	 * @brief Class for Configuration File loading and interpreting.
	 * 
	 */
	class ConfigFile
	{
	public:
		/**
		 * @brief Load's a integer value from the config .ini file, using the specfied default value if the value doesn't exist.
		 * @param section The ini section that the key/value belongs to.
		 * @param key The integers key (ini key/value pairs are in the format `key=value`
		 * @param default The integer to be returned if the key/value/section doesn't exist.
		 * @return If the key/value/section all exist then return the loaded value from the ini file, otherwise return the default.
		 */
		int getInteger(const std::string& section, const std::string& key, int default);

		/**
		 * @brief Load's a single character value from the config .ini file, using the specfied default value if the value doesn't exist
		 * @param section The ini section that the key/value belongs to.
		 * @param key The integers key (ini key/value pairs are in the format `key=value`
		 * @param default The integer to be returned if the key/value/section doesn't exist.
		 * @return If the key/value/section all exist then return the loaded value from the ini file, otherwise return the default.
		 */
		char getChar(const std::string& section, const std::string& key, char default);

		/**
		 * @brief Load's a boolean value from the config .ini file, using the specfied default value if the value doesn't exist
		 * @param section The ini section that the key/value belongs to.
		 * @param key The integers key (ini key/value pairs are in the format `key=value`
		 * @param default The integer to be returned if the key/value/section doesn't exist.
		 * @return If the key/value/section all exist then return the loaded value from the ini file, otherwise return the default.
		 */
		bool getBool(const std::string& section, const std::string& key, bool default);

		/**
		 * @brief Load's a 32 bit real value (float) from the config .ini file, using the specfied default value if the value doesn't exist
		 * @param section The ini section that the key/value belongs to.
		 * @param key The integers key (ini key/value pairs are in the format `key=value`
		 * @param default The integer to be returned if the key/value/section doesn't exist.
		 * @return If the key/value/section all exist then return the loaded value from the ini file, otherwise return the default.
		 */
		float getFloat(const std::string& section, const std::string& key, float default);

		/**
         * @brief Load's a event::Keys enumumator value from the config .ini file, using the specfied default value if the value doesn't exist.
		 *        This will parse the key names into a events::Keys value. See https://wiki.libsdl.org/SDL_Keycode for a list of all possible key names
		 * @param section The ini section that the key/value belongs to.
		 * @param key The integers key (ini key/value pairs are in the format `key=value`
		 * @param default The integer to be returned if the key/value/section doesn't exist.
		 * @return If the key/value/section all exist then return the loaded value from the ini file, otherwise return the default.
		 */
		events::Keys getScancode(const std::string& section, const std::string& key, events::Keys default);
		
		/**
	 	 * @brief Return's if the .ini file for this config file exists on disk. This allows for cleaner handling of the file not existing.
		 *        E.g. no requirement for the .ini to exist - if it doesn't just use defaults.
		 * @return Return's true if the file exists on disk, false if not.
		 */
		bool existsOnDisk() const;

		/**
		 * @brief Load's the .ini file using the filename that has been set in the constructor. Can be used multiple times (to hot reload config files, for example).
		 */
		void reload();

		/*
		 * @brief Set's the assosiated .ini file for this ConfigFile. This filepath should be full (e.g. include the .ini extension)
		 * @param filepath The filepath of the .ini file (should include .ini extension).
		 */
		ConfigFile(const std::string& filepath)
			: m_filepath(filepath) {}
		
		/*
		 * @brief Default stub constructor. Does nothing.
		 */
		ConfigFile() {}

	private:
		INIReader   m_inifile;
		std::string m_filepath;
	};

	class ConfigManager
	{
	public:
		/**
		 * @brief Pointer to the static instance of ConfigManager
		 * @return The ConfigManager singleton.
		 */
		static ConfigManager* get();

		/**
		 * @brief Registers a config file with the manager. Should be called at begining of the program.
		 * @param name The filename of the .ini file (excluding the .ini extension) e.g. "Controls.ini" is just "Controls". Can include directories.
		 * @return A pointer to the newly registered config file of the specified name.
		 */
		ConfigFile* registerConfig(const std::string& name);

		/**
		 * @brief Fetches a pointer to the registered config file. Default config object if the file has not been registered yet (aka always returns default).
		 * @param name The filename of the config file (excluding the .ini extension). Must be the same as the one used in the corresponding REGISTER_CONFIG call. 
		 * @return A pointer to the ConfigFile of the specified name. Default config object if the file has not been registered yet (aka always returns default). 
		 */
		ConfigFile* getConfigFile(const std::string& name);

	private:
		std::unordered_map<std::string, ConfigFile> m_configfiles;
	};
}
