/**
 *
 * @file Settings.h
 *
 * @authors : T. Stérin, A. Torres
 *
 * @date : 10/11/2015
 *
 * @version : 1.0
 *
 * @brief Settings class header file
 *
 * @see Settings.cpp
 *
 **/

#ifndef DEF_SETTINGS_H
#define DEF_SETTINGS_H

#include <string>				// std::string

/// @namespace nsGameEngine
/// @brief The GameEngine namespace.
/// @details The GameEngine namespace gather all the classes that are related to the game engine.
namespace nsGameEngine
{

    /// @def CONFIG_FILE_PATH
    /// @brief The (relative) path of the config file at execution.
    #define CONFIG_FILE_PATH "config.cfg"
    
	/// @class Settings Settings.h
	/// @brief The settings class of the game
	/// @details The Setting class will allow to load and save settings for the game.
    /// It uses a simple text file to load and save user's settings.
	class Settings
	{
		public:
            /// @fn Settings(const unsigned int & p_width, const unsigned int & p_height, const std::string & p_title) noexcept;
            /// @brief The default constructor of the Settings class.
            /// @details The constructor create a Settings object that will allow to easily manage in-game settings.
			Settings() noexcept;

            /// @fn ~Settings();
            /// @brief The destructor.
            /// @details It will free the memory.
			~Settings();

            /// @fn void load() noexcept;
            /// @brief Loads the settings from a file.
            /// @details The function will load the configuration file in the memory if it is not already done.
            /// Once loaded, the settings can be acceded by using the differents getters of the class.
			void load() noexcept;


            /*
             *  SETTERS AND GETTERS
             */

            unsigned int getWindowWidth();
            unsigned int getWindowHeight();
            std::string getWindowTitle();
            
            void setWindowWidth(const unsigned int &p_width);
            void setWindowHeight(const unsigned int &p_height);
            void setWindowTitle(const std::string &p_windowTitle);
			
		private:
            /// @brief The width of the window.
            unsigned int m_windowWidth;
            
            /// @brief The height of the window.
            unsigned int m_windowHeight;

            /// @brief The title of the window.
            std::string m_windowTitle;
	};
}

#endif /* DEF_SETTINGS_H */
