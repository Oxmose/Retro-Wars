#include <SFML/Graphics.hpp>	// sf::RenderWindow, sf::VideoMode
#include <string>				// std::string

#include "GameEngine.h"			// nsGameEngine::GameEngine
#include "../GraphicEngine/GraphicEngine.h"		// nsGraphicEngine::GraphicEngine

#define GENGINE nsGameEngine::GameEngine

using namespace nsGraphicEngine;
using namespace std;

GENGINE::GameEngine(const unsigned int & p_width, const unsigned int & p_height, const string & p_title) noexcept
{
	// Init basic settings
	m_windowDim = sf::VideoMode(p_width, p_height);
	m_windowTitle	= p_title;

	m_window = new sf::RenderWindow(m_windowDim, m_windowTitle);
} // GameEngine();

void GENGINE::init() noexcept
{	
	// Init the graphic engine
	m_graphicEngine = GraphicEngine(m_window);
	m_graphicEngine.loadTest();
	
	while (m_window->isOpen())
    {
        sf::Event event;
        while(m_window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                m_window->close();
        }


        m_graphicEngine.reload();
        m_graphicEngine.drawTest();
    
        m_window->display();
    }
} // init();

GENGINE::~GameEngine()
{
    delete m_window;
}
