/**
 *
 * @file GameEngine.h
 *
 * @authors : J. 
 *
 * @date : 08/01/14
 *
 * @version : 1.0
 *
 * @brief Board class header.
 *
 * @see board.cpp
 *
 **/

#ifndef DEF_GAMEENGINE_H
#define DEF_GAMEENGINE_H

#include <SFML/Graphics.hpp>	// sf::RenderWindow, sf::VideoMode
#include <string>				// std::string

#include "GameEngine.h"			// nsGameEngine::GameEngine
#include "GraphicEngine.h"		// nsGraphicEngine::GraphicEngine

namespace nsGameEngine
{
	class GameEngine
	{
		public:
			GameEngine() noexcept;
			~GameEgine();

			void init() noexcept;

			
		private:
			// Window settings
			sf::VideoMode 	m_windowDim;
			std::string 	m_windowTitle;
			
			// Window object
			sf::RenderWindow m_window;
			
			// Graphic engine
			nsGraphicEnine	m_graphicEngine;
	}
}

#endif /* DEF_GAMEENGINE_H */
