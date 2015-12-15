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

    m_world = new World(p_playerType, m_mapEngine->getWidth(), m_mapEngine->getHeight());


    loadWorld();
    for (int i = 0; i < m_mapEngine->getWidth(); ++i)
    {
        for (int j = 0; j < m_mapEngine->getHeight(); ++j)
        {
            Terrain tmp_ter = m_world->getTerrain(i, j);
            if (tmp_ter.getType() == HQ && tmp_ter.getOwner() == p_playerType)
            {
                m_player->setCoord(i, j);
            }
        }
    }

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

Unit GENGINE::gidToUnit(int gid, int p_x, int p_y)
{

    switch(gid)
    {
        case 229+0:
            return Unit(INFANTRY,p_x,p_y,RED,229);
        case 229+1:
            return Unit(MDTANK,p_x,p_y,RED,229+1);
        case 229+2:
            return Unit(RECON,p_x,p_y,RED,229+2);
        case 229+3:
            return Unit(ARTILLERY,p_x,p_y,RED,229+3);
        case 229+9:
            return Unit(NEOTANK,p_x,p_y,RED,229+9);
        case 229+10:
            return Unit(MEGATANK,p_x,p_y,RED,229+10);
        case 229+13:
            return Unit(MECH,p_x,p_y,RED,229+13);
        case 229+14:
            return Unit(TANK,p_x,p_y,RED,229+14);
        case 229+16:
            return Unit(ROCKET,p_x,p_y,RED,229+16);


        case 255:
            return Unit(INFANTRY,p_x,p_y,BLUE,255);
        case 256:
            return Unit(MDTANK,p_x,p_y,BLUE,256);
        case 257:
            return Unit(RECON,p_x,p_y,BLUE,257);
        case 258:
            return Unit(ARTILLERY,p_x,p_y,BLUE,258);
        case 264:
            return Unit(NEOTANK,p_x,p_y,BLUE,264);
        case 265:
            return Unit(MEGATANK,p_x,p_y,BLUE,265);
        case 268:
            return Unit(MECH,p_x,p_y,BLUE,268);
        case 269:
            return Unit(TANK,p_x,p_y,BLUE,269);
        case 271:
            return Unit(ROCKET,p_x,p_y,BLUE,271);

        default:
            return Unit(INFANTRY,-1,-1,NEUTRAL,0);
    }
}

void GENGINE::loadWorld()
{
    int x = 0, y = 0;
    
    for(int gid: m_mapEngine->getLayerTiles(2))
    {
        if(gid != 0)
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
        if(gid != 0)
            if(m_world->getTerrain(x,y).isNoneTerrain())
                m_world->addTerrain(gidToTerrain(gid,x,y));
        
        x += 1;
        if(x >= m_mapEngine->getWidth())
        {
            x = 0;
            y += 1;
        }
    }


    x=0,y=0;
    for(int gid: m_mapEngine->getLayerTiles(4))
    {
        if(gid != 0)
            m_world->addUnit(gidToUnit(gid,x,y));
        x += 1;
        if(x >= m_mapEngine->getWidth())
        {
            x = 0;
            y += 1;
        }
    }

    //printf("%d %d\n", m_world->getTerrain(1,18).getType(), m_world->getTerrain(1,18).getOwner());
    //m_world->getTerrain(8,16).setOwner(BLUE);
    //printf("%d %d\n", m_world->getTerrain(8,0).getType(), m_world->getTerrain(8,0).getOwner());
}

void GENGINE::frame()
{
    bool turn = true;
    int view = 0;

    Terrain selectedTerrain;
    Unit selectedUnit;
    bool selectedUnitBool = false;

    unsigned int fps = 25;
    sf::Time framerate = sf::milliseconds(1000 / fps);
    
    pair<int, int> mvtCursor = make_pair(0, 0);

	sf::Clock clock;
    while (m_window->isOpen())
    {	
       
        sf::Event event;
        while(m_window->pollEvent(event))
        {
            // Key event
            if(event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    if (selectedUnitBool)
                    {
                        mvtCursor.second--;
                        if (mvtCursor.second < 0)
                            mvtCursor.second = 0;
                    }
                    else
                    {
                        int newY = m_player->getCoord().second - 1;

                        if (newY < 0)
                            newY = 0;
        
                        m_player->setCoord(m_player->getCoord().first, newY);
                        mvtCursor = m_player->getCoord();
                    }
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    if (selectedUnitBool)
                    {
                        mvtCursor.second++;
                        if (mvtCursor.second > m_mapEngine->getHeight() - 1)
                            mvtCursor.second = m_mapEngine->getHeight() - 1;
                    }
                    else
                    {
                        int newY = m_player->getCoord().second + 1;

                        if (newY > m_mapEngine->getHeight() - 1)
                            newY = m_mapEngine->getHeight() - 1;
        
                        m_player->setCoord(m_player->getCoord().first, newY);
                        mvtCursor = m_player->getCoord();
                    }
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    if (selectedUnitBool)
                    {
                        mvtCursor.first--;
                        if (mvtCursor.first < 0)
                            mvtCursor.first = 0;
                    }
                    else
                    {
                        int newX = m_player->getCoord().first - 1;

                        if (newX < 0)
                            newX = 0;
                       
                        m_player->setCoord(newX, m_player->getCoord().second);
                        mvtCursor = m_player->getCoord();
                    }
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    if (selectedUnitBool)
                    {
                        mvtCursor.first++;
                        if (mvtCursor.first > m_mapEngine->getWidth() - 1)
                            mvtCursor.first = m_mapEngine->getWidth() - 1;
                    }
                    else
                    {
                        int newX = m_player->getCoord().first + 1;

                        if (newX > m_mapEngine->getWidth() - 1)
                            newX = m_mapEngine->getWidth() - 1;
        
                        m_player->setCoord(newX, m_player->getCoord().second);
                        mvtCursor = m_player->getCoord();
                    }
                }
                else if (event.key.code == sf::Keyboard::Return && turn)
                {
                    Unit unit = m_world->getUnit(m_player->getCoord().first, m_player->getCoord().second);
                    
                    if (unit.getOwner() != NEUTRAL)
                    {
                        if (unit.getOwner() == m_player->getType())
                        {
                            selectedUnitBool = true;
                            selectedUnit = unit;
                            view = 2;
                        }
                    }
                    else
                    {    
                        Terrain ter = m_world->getTerrain(m_player->getCoord().first, m_player->getCoord().second);
                        if (ter.getOwner() == m_player->getType())
                        {
                            selectedTerrain = ter;
                            switch(ter.getType())
                            {
                                case 7:
                                    view = 1;
                                    break;
                                
                            }
                        }
                    }
                }
                else if (event.key.code == sf::Keyboard::Escape)
                {
                    if (view != 0)
                    {
                        view = 0;
                    }
                    selectedUnitBool = false;
                }
            }
            if(event.type == sf::Event::Closed)
                m_window->close();
        }
        m_graphicEngine->reload();
        m_graphicEngine->checkProperties(m_world);//mise à jour des buildings

	    if (view == 0)
        {
            m_graphicEngine->drawMap(m_world);
            m_graphicEngine->drawUnits(m_world);
            m_graphicEngine->refreshUserInterface(m_player, m_world, turn);
        }
        else if (view == 1)
        {
            m_graphicEngine->displayBaseInfo(m_player, selectedTerrain);
        }
        else if (view == 2)
        {
            m_graphicEngine->drawMap(m_world);
            m_graphicEngine->drawUnits(m_world);
            m_graphicEngine->displayUnitInfo(m_player, selectedUnit, mvtCursor, m_world);
        }
        m_window->display();
	
        sf::Time elapsed = clock.getElapsedTime();
        if (elapsed < framerate)
            sf::sleep(framerate - elapsed);

        clock.restart();
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
