#include <SFML/Graphics.hpp>	// sf::RenderWindow, sf::VideoMode
#include <string>				// std::string

#include "GameEngine.h"			// nsGameEngine::GameEngine
#include "../GraphicEngine/GraphicEngine.h"		// nsGraphicEngine::GraphicEngine
#include "Player.h"
#include "../Misc/Misc.h"

#define GENGINE nsGameEngine::GameEngine

using namespace nsGraphicEngine;
using namespace std;

GENGINE::GameEngine(const unsigned int & p_width, const unsigned int & p_height, const string & p_title, 
                    const std::string & p_mapName, const unsigned int & p_playerType) noexcept
{
	// Init basic settings
	m_windowDim = sf::VideoMode(p_width, p_height);
	m_windowTitle	= p_title;

	m_window = new sf::RenderWindow(m_windowDim, m_windowTitle);

    m_mapName = p_mapName;

    m_ml = new tmx::MapLoader("../res/maps/");
    m_ml->AddSearchPath("../res/maps/tilesets");

	m_graphicEngine = new GraphicEngine(m_window, m_ml);

    m_player = new Player(p_playerType);
} // GameEngine();


void GENGINE::loadMap() noexcept
{
    m_ml->Load(m_mapName);
}

void GENGINE::frame() noexcept
{
    // Init the graphic engine
    loadMap();	
	

    while (m_window->isOpen())
    {
        sf::Event event;
        while(m_window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                m_window->close();
        }

        m_graphicEngine->reload();
        m_graphicEngine->drawMap(); 
        m_window->display();
    }
} // init();

GENGINE::~GameEngine()
{
    delete m_ml;
    delete m_player;
    delete m_window;
    delete m_graphicEngine;
}
