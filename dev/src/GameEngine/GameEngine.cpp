#include <SFML/Graphics.hpp>	// sf::RenderWindow, sf::VideoMode
#include <string>				// std::string

#include "GameEngine.h"			// nsGameEngine::GameEngine
#include "../GraphicEngine/GraphicEngine.h"		// nsGraphicEngine::GraphicEngine
#include "../MapEngine/MapEngine.h"
#include "../NetEngine/NetEngine.h"
#include "World.h"
#include "Player.h"
#include "../Misc/Misc.h"

#define GENGINE nsGameEngine::GameEngine

using namespace nsMapEngine;
using namespace nsGameEngine;
using namespace nsGraphicEngine;
using namespace nsNetEngine;
using namespace std;

GENGINE::GameEngine(const unsigned int & p_width, const unsigned int & p_height, const string & p_title, 
                    MapEngine* p_mapEngine, PLAYER_TYPE p_playerType, NetEngine *p_netEngine) noexcept
{
	// Init basic settings
	m_windowDim = sf::VideoMode(p_width, p_height);
	m_windowTitle	= p_title;

	m_window = new sf::RenderWindow(m_windowDim, m_windowTitle);

    m_mapEngine = p_mapEngine;
	m_netEngine = p_netEngine;
	m_graphicEngine = new GraphicEngine(m_window, m_mapEngine);

    m_player = new Player(p_playerType);

    m_world = new World();

    loadWorld();
} // GameEngine();

Terrain GENGINE::gidToTerrain(int gid, int p_x, int p_y)
{
    switch(gid)
    {
        case 145+7:
            return Terrain(HQ,p_x,p_y,RED);
        case 145+21:
            return Terrain(HQ,p_x,p_y,BLUE);
        case 145+35:
            return Terrain(HQ,p_x,p_y,GREEN);
        case 145+49:
            return Terrain(HQ,p_x,p_y,YELLOW);
        case 145+63:
            return Terrain(HQ,p_x,p_y,BLACK);

        case 145+8:
            return Terrain(CITY,p_x,p_y,RED);
        case 145+22:
            return Terrain(CITY,p_x,p_y,BLUE);
        case 145+36:
            return Terrain(CITY,p_x,p_y,GREEN);
        case 145+50:
            return Terrain(CITY,p_x,p_y,YELLOW);
        case 145+65:
            return Terrain(CITY,p_x,p_y,BLACK);
        case 145+78:
            return Terrain(CITY,p_x,p_y,NEUTRAL);

        case 145+9:
            return Terrain(BASE,p_x,p_y,RED);
        case 145+23:
            return Terrain(BASE,p_x,p_y,BLUE);
        case 145+37:
            return Terrain(BASE,p_x,p_y,GREEN);
        case 145+51:
            return Terrain(BASE,p_x,p_y,YELLOW);
        case 145+66:
            return Terrain(BASE,p_x,p_y,BLACK);
        case 145+79:
            return Terrain(BASE,p_x,p_y,NEUTRAL);



        case 1:
            return Terrain(PLAIN,p_x,p_y);
        case 91:
            return Terrain(MOUNTAIN,p_x,p_y);
        case 127:
            return Terrain(MOUNTAIN,p_x,p_y);
        case 2:
            return Terrain(ROADS,p_x,p_y);
        case 20:
            return Terrain(ROADS,p_x,p_y);
        case 38:
            return Terrain(ROADS,p_x,p_y);
        case 74:
            return Terrain(ROADS,p_x,p_y);
        case 92:
            return Terrain(ROADS,p_x,p_y);
        case 110:
            return Terrain(ROADS,p_x,p_y);
        case 128:
            return Terrain(ROADS,p_x,p_y);
        case 129:
            return Terrain(ROADS,p_x,p_y);
        case 111:
            return Terrain(ROADS,p_x,p_y);
        case 93:
            return Terrain(ROADS,p_x,p_y);
        case 75:
            return Terrain(ROADS,p_x,p_y);
        case 21:
            return Terrain(BRIDGES,p_x,p_y);
        case 3:
            return Terrain(BRIDGES,p_x,p_y);
        case 52:
            return Terrain(ROADS,p_x,p_y);
        case 70:
            return Terrain(ROADS,p_x,p_y);
        case 124:
            return Terrain(WOODS,p_x,p_y);
        case 55:
            return Terrain(WOODS,p_x,p_y);

        default:
            return Terrain(OTHER,p_x,p_y);
    }
}

void GENGINE::loadWorld()
{
    int x = 0, y = 0;
    for(int gid: m_mapEngine->getLayerTiles(2))
    {
        m_world->addTerrain(gidToTerrain(gid,x,y));
        x += 1;
        if(x >= m_mapEngine->getWidth())
        {
            x = 0;
            y += 1;
        }
    }

    x=0,y=0;
    for(int gid: m_mapEngine->getLayerTiles(0))
    {
        if(!m_world->getTerrain(x,y).isProperty())
        {
            m_world->addTerrain(gidToTerrain(gid,x,y));
            x += 1;
            if(x >= m_mapEngine->getWidth())
            {
                x = 0;
                y += 1;
            }
        }
    }

    printf("%d %d\n", m_world->getTerrain(1,18).getType(), m_world->getTerrain(1,18).getOwner());
    m_world->getTerrain(8,16).setOwner(BLUE);
    //printf("%d %d\n", m_world->getTerrain(8,0).getType(), m_world->getTerrain(8,0).getOwner());
}

void GENGINE::frame() noexcept
{
	
    while (m_window->isOpen())
    {
        sf::Event event;
        while(m_window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                m_window->close();
        }
        m_graphicEngine->reload();
        m_graphicEngine->checkProperties(m_world);
        m_graphicEngine->drawMap();
	m_graphicEngine->refreshUserInterface(m_player);
        m_window->display();
    }
} // init();

GENGINE::~GameEngine()
{
    delete m_player;
    delete m_world;
    delete m_window;
    delete m_graphicEngine;
}

void GENGINE::notify(const std::string &p_message)
{
    cout << "SERVER SENT ME : " << p_message;
}

void GENGINE::test()
{
    NetPackage np;
    np.message = "test";
    m_netEngine->send(np);
}
