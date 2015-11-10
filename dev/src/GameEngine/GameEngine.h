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
#include "../GraphicEngine/GraphicEngine.h"		// nsGraphicEngine::GraphicEngine

namespace nsGameEngine
{
	class GameEngine
	{
		public:
			GameEngine(const unsigned int & p_width, const unsigned int & p_height, const std::string & p_title) noexcept;
			~GameEngine();

			void frame() noexcept;

			
		private:
			// Window settings
			sf::VideoMode 	m_windowDim;
			std::string 	m_windowTitle;
			
			// Window object
			sf::RenderWindow* m_window;
			
			// Graphic engine
			nsGraphicEngine::GraphicEngine*	m_graphicEngine;
	};
}

#endif /* DEF_GAMEENGINE_H */
