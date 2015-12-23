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
    m_fps = 25;

	m_window = new sf::RenderWindow(m_windowDim, m_windowTitle);

    m_mapEngine = p_mapEngine;
	m_netEngine = p_netEngine;
	

    m_player = new Player(p_playerType);

    // INIT UNIT ID
    Unit::m_lastId = 0;

    m_world = new World(p_playerType, m_mapEngine->getWidth(), m_mapEngine->getHeight());


    loadWorld();

    bool found = false;
    for (int i = 0; i < m_mapEngine->getWidth() && !found; ++i)
    {
        for (int j = 0; j < m_mapEngine->getHeight() && !found; ++j)
        {
            Terrain tmp_ter = m_world->getTerrain(i, j);
            if (tmp_ter.getType() == HQ && tmp_ter.getOwner() == p_playerType)
            {
                m_player->setCoord(i, j);
                found = true;
            }
        }
    }
	m_graphicEngine = new GraphicEngine(m_window, m_mapEngine);

    if(m_netEngine->isServer())
        m_turn = true;
    else
        m_turn = false;

    m_waitingForPlayers = true;

    m_win = false;

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
}

std::string GENGINE::coordToString(std::pair<int,int> p_coord)
{
    return string("("+std::to_string(p_coord.first)+","+std::to_string(p_coord.second)+")");
}

void GENGINE::frame()
{
    int view = 0;

    Terrain selectedTerrain;
    Unit selectedUnit;
    bool selectedUnitBool = false;
    bool displayPorte = false;

    bool validateEndTurn = false;

    sf::Time framerate = sf::milliseconds(1000 / m_fps);
    
    pair<int, int> mvtCursor = make_pair(0, 0);
    vector<int> movedUnits;
    bool cleared;

    int selectedUnitBase = 0;

    bool validateBuy = true;

    // Timer for 5s
    int messageTimer = m_fps * 4;
    bool displayMessage = false;
    string message; 
    
    m_attackNotifyStep = m_fps * 2.88;
    m_attackNotify = false;

    // Ask for player already connected 
    NetPackage np;
    np.message = "205";
    m_netEngine->send(np);

    sf::Clock clock;
    while(m_window->isOpen())
    {	
        if(displayMessage)
        {
            --messageTimer;
            if(messageTimer == 0)
            {
                messageTimer = m_fps * 4;
                displayMessage = false;
            }
        }

        if(m_attackNotify)
        {
            --m_attackNotifyStep;
            if(m_attackNotifyStep == 0)
            {
                m_attackNotify = false;
                m_attackNotifyStep = m_fps * 2.88;
            }
        }

        // Reset vars
        if (!m_turn  && !cleared)
        {
            movedUnits.clear();
            cleared = true;
        }
       
        sf::Event event;
        while(m_window->pollEvent(event))
        {
            if(!m_win)
            {
                // Key event
                if(event.type == sf::Event::KeyPressed && !m_waitingForPlayers)
                {
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        if(selectedUnitBool)
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
                        if(view == 1)
                        {
                            selectedUnitBase--;
                            if(selectedUnitBase < 0)
                                selectedUnitBase = 0;
                            validateBuy = true; 
                        }
                        else if (selectedUnitBool)
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
                        if(view == 1)
                        {
                            selectedUnitBase++;
                            if(selectedUnitBase > 8)
                                selectedUnitBase = 8;
                            validateBuy = true; 
                        }
                        else if (selectedUnitBool)
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
                    else if (event.key.code == sf::Keyboard::Return && m_turn)
                    {
                        if(view == 1)
                        {
                            // BASE VIEW
                            int cost = Unit::getUnitInfo((UnitType)selectedUnitBase).cost;
                            if(m_player->getMoney() >= cost)
                            {
                                if(validateBuy)
                                {
                                    messageTimer = m_fps * 100;
                                    message = "Are you sure you want to buy this?\n(enter to validate / escape to cancel)";
                                    displayMessage = true;
                                    validateBuy = false;
                                }
                                else
                                {
                                    m_player->setMoney(m_player->getMoney() - cost);
                                    validateBuy = true;
                                    messageTimer = m_fps * 4;
                                    displayMessage = false;
                                    pair<int, int> availableCoord = getAvailableSpawnCoord();
                                    Unit unit ((UnitType)selectedUnitBase, availableCoord.first, availableCoord.second, m_player->getType(), 229);
                                    m_world->addUnit(unit);
                                }
                            }
                        }
		                else if(selectedUnitBool && view == 2)
                        {
                            // Player wants to move the unit
                            if(mvtCursor.first != m_player->getCoord().first || mvtCursor.second != m_player->getCoord().second)
                            {
                                bool moved = false;
                                for(int id : movedUnits)
                                {
                                    if(selectedUnit.getId() == id)
                                        moved = true;
                                }
                                if(moved)
                                {
                                    displayMessage = true;
                                    messageTimer = m_fps * 4;
                                    message = "Unit already used this turn!";
                                }
                                else
                                {
                                    vector<pair<int, int>> accessible = m_world->getAccessible(selectedUnit);
                                    // Check if user can move there
                                    bool move = false;
                                    for(pair<int, int> Coord : accessible)
                                    {
                                        if(Coord.first == mvtCursor.first && Coord.second == mvtCursor.second)
                                        {
                                            move = true;
                                            break;
                                        }
                                    }
                                    if(move)
                                    {
                                        NetPackage np;
                                        np.message = "0::"+coordToString(selectedUnit.getCoord())+"::"+coordToString(mvtCursor);
                                        m_world->moveUnit(selectedUnit, mvtCursor);
									
									    m_netEngine->send(np);
                                        m_player->setCoord(mvtCursor);
                                        movedUnits.push_back(selectedUnit.getId());
                                        cleared = false;
                                        selectedUnitBool = false;
                                        displayPorte = false;
                                        view = 0;
                                    }
                                    else
                                    {
                                        // Check if user wanted to attack a unit
                                        vector<pair<int, int>> enemies = m_world->getPortee(selectedUnit);
                                        bool attack = false;
                                        for(pair<int, int> Coord : enemies)
                                        {
                                            if(Coord.first == mvtCursor.first && Coord.second == mvtCursor.second)
                                            {
                                                attack = true;
                                                break;
                                            }
                                        }
                                        if(attack)
                                        {
                                            NetPackage np;
                                            np.message = "1::"+coordToString(selectedUnit.getCoord())+"::"+coordToString(mvtCursor);
                                            
                                            m_world->combatUnit(selectedUnit, m_world->getUnit(mvtCursor));
                                            np.message += "::"+std::to_string(m_world->getUnit(selectedUnit.getCoord()).getHp())+"::"+std::to_string(m_world->getUnit(mvtCursor).getHp());
                                            m_netEngine->send(np);
                                            m_player->setCoord(mvtCursor);
                                            movedUnits.push_back(selectedUnit.getId());
                                            cleared = false;
                                            selectedUnitBool = false;
                                            displayPorte = false;
                                            
                                            m_attackNotify = true;
                                            m_attackPos = mvtCursor;
                                            m_attackFrom = selectedUnit.getCoord();

                                            view = 0;
                                        }
                                        else
                                        {
                                            displayMessage = true;
                                            messageTimer = m_fps * 4;
                                            message = "You cannot move here!";
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            Unit unit = m_world->getUnit(m_player->getCoord().first, m_player->getCoord().second);
                        
                            if(unit.getOwner() != NEUTRAL)
                            {
                                if (unit.getOwner() == m_player->getType())
                                {
                                    bool moved = false;
                                    for(int id : movedUnits)
                                    {
                                        if(unit.getId() == id)
                                            moved = true;
                                    } 
                                    if(moved)
                                    {
                                        displayMessage = true;
                                        messageTimer = m_fps * 4;
                                        message = "Unit already used this turn!";
                                    }
                                    else
                                    {
                                        selectedUnitBool = true;
                                        selectedUnit = unit;
                                        view = 2;
                                    }
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
                    }
                    else if (event.key.code == sf::Keyboard::Escape)
                    {
                        if((view == 1 && displayMessage) || !validateBuy )
                        {
                            validateBuy = true; 
                            displayMessage = false;
                            messageTimer = m_fps * 4;
                        }
                        else
                        {
                            displayMessage = false;
                            messageTimer = m_fps * 4;

                            if (view != 0)
                            {
                                view = 0;
                            }
                            selectedUnitBool = false;
                            displayPorte = false;
                            validateEndTurn = false;
                            selectedUnitBase = 0;
                        }
                        
                    }
                    else if (event.key.code == sf::Keyboard::W)
                    {
                        if (selectedUnitBool && view == 2)
                        {
                            displayPorte = !displayPorte;
                        }
                    }
		            else if(event.key.code == sf::Keyboard::T && m_turn)
		            {

		                if(validateEndTurn)
		                {
		                        m_turn = false;
		                        vector<PLAYER_TYPE> players = m_mapEngine->getPlayers();
		                        unsigned int index;
		                        for(unsigned int i = 0; i < players.size(); ++i)
		                        {
		                            if(players[i] == m_player->getType())
		                            {
		                                index = i;
		                                break;
		                            }
		                        }		
		                        unsigned int nextPlayer = ((index + 1) == players.size() ? players[0] : players[index + 1]);
		                        NetPackage np;
		                        np.message = "2::" + to_string(nextPlayer);
		                        m_netEngine->send(np);
                                displayMessage = false;
                                messageTimer = m_fps * 4;
                                validateEndTurn = false;
                                view = 0;
		                }
                        else
                        {
                            validateEndTurn = true;
                            message = "Are  you  sure  to  end  the  turn?\n(t to validate / escape to cancel)";
                            displayMessage = true;
                        }
                    }
                }
            }
            if(event.type == sf::Event::Closed)
                m_window->close();
        }

        m_graphicEngine->reload();
        m_graphicEngine->checkProperties(m_world);//mise à jour des buildings

        if(m_win)
        {
            m_graphicEngine->drawMap(m_world);
            m_graphicEngine->drawUnits(m_world);
            displayMessage = true;
            messageTimer = m_fps / 25;
            message = "You  win!";
        }	    
        if (view == 0)
        {
            m_graphicEngine->drawMap(m_world);
            m_graphicEngine->drawUnits(m_world);
            m_graphicEngine->refreshUserInterface(m_player, m_world, m_turn);
        }
        else if (view == 1)
        {
            m_graphicEngine->displayBaseInfo(m_player, selectedTerrain, selectedUnitBase);
        }
        else if (view == 2)
        {
            m_graphicEngine->drawMap(m_world);
            m_graphicEngine->drawUnits(m_world);
            m_graphicEngine->displayUnitInfo(m_player, selectedUnit, mvtCursor, m_world, displayPorte);
        }

        if(m_waitingForPlayers)
        {
            displayMessage = true;
            messageTimer = m_fps / 25;
            message = "Waiting  for  " + to_string(m_playerLeft) + "  more  player.";
        }


        if(displayMessage)
            m_graphicEngine->displayMessage(message);

        if(m_attackNotify)
        {
            m_graphicEngine->notifyAttack(m_attackNotifyStep, m_attackPos);
            m_graphicEngine->notifyAttack(m_attackNotifyStep, m_attackFrom);
        }
        m_window->display();
	
        sf::Time elapsed = clock.getElapsedTime();
        if (elapsed < framerate)
            sf::sleep(framerate - elapsed);

        clock.restart();
    }
} // frame();

GENGINE::~GameEngine()
{
    delete m_player;
    delete m_world;
    delete m_window;
    delete m_graphicEngine;
} // ~GameEngine()

void GENGINE::notify(const Action &p_action)
{
    if(p_action.type == MOVE)
    {
        m_world->moveUnit(m_world->getUnit(p_action.coord[0]), p_action.coord[1]);
    }
    else if(p_action.type == ATTACK)
    {
        m_attackPos = p_action.coord[1];
        m_attackFrom = p_action.coord[0];
        m_attackNotifyStep = m_fps * 2.88;
        m_attackNotify = true;

        for(int i = 0 ; i < 2 ; i++)
        {
            if(p_action.data[i] == -1)
                m_world->removeUnit(m_world->getUnit(p_action.coord[i]));
            else
                m_world->getUnit(p_action.coord[i]).setHp(p_action.data[i]);
        }
    }
    else if(p_action.type == CH_TURN)
    {
        if(p_action.data[0] == m_player->getType())
            m_turn = true;
        else
            m_turn = false;

        m_player->setMoney(m_player->getMoney() + 1000);
    }
    else if(p_action.type == NEW_PLAYER)
    {
        if(p_action.data[0] == m_mapEngine->getPlayers().size())
        {
            m_waitingForPlayers = false;
        }
        else
        {
            m_playerLeft = m_mapEngine->getPlayers().size() - p_action.data[0];
        }
    }
    else if(p_action.type == DISCONNECTED)
    {
        m_win = true;
    }
} // notify()

pair<int, int> GENGINE::getAvailableSpawnCoord()
{
    PLAYER_TYPE playerType = m_player->getType();
    bool found = false;
    pair<int, int> base;
    for (int i = 0; i < m_mapEngine->getWidth() && !found; ++i)
    {
        for (int j = 0; j < m_mapEngine->getHeight() && !found; ++j)
        {
            Terrain tmp_ter = m_world->getTerrain(i, j);
            if (tmp_ter.getType() == BASE && tmp_ter.getOwner() == playerType)
            {
                base = make_pair(i, j);
                found = true;
            }
        }
    }
    for(int i = -1; i < 2; ++i)
    {
        for(int j = -1; j < 2; ++j)
        {
            TerrainType type = m_world->getTerrain(base.first + i, base.second + j).getType();
            if((type == PLAIN || type == ROADS) && m_world->getUnit(base.first + i, base.second + j).getOwner() == NEUTRAL)                
            {
                return make_pair(base.first + i, base.second + j);
            }
        }
        
        return base;
    }
} // getAvailableSpawnCoord()
