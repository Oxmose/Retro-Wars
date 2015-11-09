#include <SFML/Graphics.hpp>	// sf::RenderWindow, sf::VideoMode
#include <string>				// std::string

#include "GameEngine.h"			// nsGameEngine::GameEngine
#include "GraphicEngine.h"		// nsGraphicEngine::GraphicEngine

#define nsGameEngine::GameEngine GENGINE

using namespace nsGraphicEngine;
using namespace sf;
using namespace std;

GENGINE::GameEngine(const unsigned int & p_width, const unsigned int & p_height, const string & p_title) noexcept
{
	// Init basic settings
	m_windowDim = VideoMode(p_width, p_height);
	m_title	= p_title;

	m_window = window(m_windowDim, m_title);
} // GameEngine();

void GENGINE::init(void) noexcept;
{	
	// Init the graphic engine
	m_graphicEngine = GraphicEngine(&m_window);
	m_graphicEngine.loadTest();
	
	while (m_window.isOpen())
    	{
        	m_graphicEngine.drawTest();
    	}
} // init();
