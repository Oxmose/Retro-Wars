// STD LIB INCLUDES
#include <string>
#include <utility>
#include <atomic>
#include <tuple>

// SFML LIB INCLUDES
#include <SFML/Graphics.hpp> 

// INCLUDES FROM PACKAGE
#include "World.h"
#include "Player.h"

// OTHER INCLUDES FOM PROJECT
#include "../GraphicEngine/GraphicEngine.h"
#include "../MapEngine/MapEngine.h"
#include "../NetEngine/NetEngine.h"
#include "../Misc/Misc.h"

// HEADER FILE INCLUDE
#include "GameEngine.h"


#define GENGINE nsGameEngine::GameEngine

using namespace nsMapEngine;
using namespace nsGameEngine;
using namespace nsGraphicEngine;
using namespace nsNetEngine;
using namespace std;

GENGINE::GameEngine(const int & p_width, const int & p_height, const string & p_title, 
                    MapEngine* p_mapEngine, PLAYER_TYPE p_playerType, NetEngine *p_netEngine)
{
    // Init basic settings
    m_windowDim = sf::VideoMode(p_width, p_height);
    m_windowTitle    = p_title;
    m_fps = 25;

    m_window = new sf::RenderWindow(m_windowDim, m_windowTitle);

    m_mapEngine = p_mapEngine;
    m_netEngine = p_netEngine;
    

    m_player = new Player(p_playerType);

    // INIT UNIT ID
    Unit::m_lastId = 0;

    // Load world
    m_world = new World(p_playerType, m_mapEngine->getWidth(), m_mapEngine->getHeight());
    loadWorld();

    // Search for HQ and set cursor's position
    bool found = false;
    for (unsigned int i = 0; i < m_mapEngine->getWidth() && !found; ++i)
    {
        for (unsigned int j = 0; j < m_mapEngine->getHeight() && !found; ++j)
        {
            Terrain tmp_ter = m_world->getTerrain(i, j);
            if (tmp_ter.getType() == HQ && tmp_ter.getOwner() == p_playerType)
            {
                m_player->setCoord(i, j);
                found = true;
            }
        }
    }
    
    // Create graphic engine
    m_graphicEngine = new GraphicEngine(m_window, m_mapEngine);

    // Test is server
    if(m_netEngine->isServer())
        m_turn = true;
    else
        m_turn = false;

    // Init members
    m_waitingForPlayers = true;
    m_moveUnit = false;
    m_win = false;
    m_loose = false;

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
} // gidToTerrain()

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
} // gidToUnit()

int GENGINE::unitNPlayerTypeToGid(UNITTYPE p_UNITTYPE, PLAYER_TYPE p_playerType)
{
    switch(p_playerType)
    {
        case BLUE:
            switch(p_UNITTYPE)
            {
                case INFANTRY:
                    return 255;
                case MDTANK:
                    return 256;
                case RECON:
                    return 257;
                case ARTILLERY:
                    return 258;
                case NEOTANK:
                    return 264;
                case MEGATANK:
                    return 265;
                case MECH:
                    return 268;
                case TANK:
                    return 269;
                case ROCKET:
                    return 271;
            }
            break;
        case RED:
            switch(p_UNITTYPE)
            {
                case INFANTRY:
                    return 229;
                case MDTANK:
                    return 230;
                case RECON:
                    return 231;
                case ARTILLERY:
                    return 232;
                case NEOTANK:
                    return 238;
                case MEGATANK:
                    return 239;
                case MECH:
                    return 242;
                case TANK:
                    return 243;
                case ROCKET:
                    return 245;

            }
            break;
        default:
            return 0;
    }
    return 0;
} // unitNPlayerTypeToGid()

void GENGINE::loadWorld()
{
    unsigned int x = 0;
    unsigned int y = 0;
    
    // Load layer0 terrains
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

    // Load layer1 terrains
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

    // Load Units
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
} // loadWorld()

std::string GENGINE::coordToString(std::pair<int,int> p_coord)
{
    return string("("+std::to_string(p_coord.first)+","+std::to_string(p_coord.second)+")");
} // coordToString()

void GENGINE::frame()
{
    // Init settings
    int view = 0;

    bool selectedUnitBool   = false;
    bool displayPorte       = false;
    bool validateEndTurn    = false;
    m_attackNotify          = false;
    bool displayMessage     = false;    
    bool validateBuy        = true;
    bool cleared            = false;

    // Resources management
    bool isPaid             = false;
    
    // Selection management
    Terrain selectedTerrain;
    Unit selectedUnit;
    
    // Set cursor for movment
    pair<int, int> mvtCursor = make_pair(0, 0);

    // Moved unit this turn
    vector<int> movedUnits;
    
    // Set seelcted base id
    int selectedUnitBase = 0;

    // Massage Management
    int messageTimer = m_fps * 4;    
    string message; 
    
    // Set move animation
    m_attackNotifyStep = m_fps * 2.88;

    // Ask for already connected players
    NetPackage np;
    np.message = "205";
    m_netEngine->send(np);
    
    // Captured flags
    vector<pair<int, int>> prevCaptureFlags;

    // Set framerate
    sf::Time framerate = sf::milliseconds(1000 / m_fps);
    sf::Clock clock;

    // While game is open : GAMELOOP
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

        // Manage movment animation
        if(m_attackNotify)
        {
            --m_attackNotifyStep;
            if(m_attackNotifyStep == 0)
            {
                m_attackNotify = false;
                m_attackNotifyStep = m_fps * 2.88;
            }
        }

        // Give money to player that turn
        if(!isPaid && m_turn)
        {
            m_player->setMoney(m_player->getMoney() + 1000 * m_world->getNumberProperties());
            isPaid = true;
        }

        // Reset vars
        if (!m_turn  && !cleared)
        {
            movedUnits.clear();
            cleared = true;
            isPaid = false;

            for(vector<tuple<pair<int, int>, Unit, bool>>::iterator iter = m_capturingBuilding.begin(); iter != m_capturingBuilding.end(); ++iter)
            {
                get<2>(*iter) = false;
            }
        }
    
        // Test for events
        sf::Event event;
        while(m_window->pollEvent(event))
        {
            // While nobody has won or lost
            if(!m_win && !m_loose && !m_moveUnit)
            {
                //If a key is pressed and everybody is in the game
                if(event.type == sf::Event::KeyPressed && !m_waitingForPlayers)
                {
                    // UPKEY
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        // If unit is selected, then move movment cursor
                        if(selectedUnitBool)
                        {
                            mvtCursor.second--;
                            if (mvtCursor.second < 0)
                                mvtCursor.second = 0;
                        }
                        // Else move player cursor
                        else
                        {
                            unsigned int newY = m_player->getCoord().second - 1;

                            if (m_player->getCoord().second == 0)
                                newY = 0;
            
                            m_player->setCoord(m_player->getCoord().first, newY);
                            mvtCursor = m_player->getCoord();
                        }
                    }
                    // DOWNKEY
                    else if (event.key.code == sf::Keyboard::Down)
                    {
                        if (selectedUnitBool)
                        {
                            mvtCursor.second++;
                            if ((unsigned int)mvtCursor.second > m_mapEngine->getHeight() - 1)
                                mvtCursor.second = m_mapEngine->getHeight() - 1;
                        }
                        else
                        {
                            unsigned int newY = m_player->getCoord().second + 1;

                            if (newY > m_mapEngine->getHeight() - 1)
                                newY = m_mapEngine->getHeight() - 1;
            
                            m_player->setCoord(m_player->getCoord().first, newY);
                            mvtCursor = m_player->getCoord();
                        }
                    }
                    // LEFTKEY
                    else if (event.key.code == sf::Keyboard::Left)
                    {
                        // If in the base menu, then move the unit selector
                        if(view == 1)
                        {
                            selectedUnitBase--;
                            if(selectedUnitBase < 0)
                                selectedUnitBase = 0;
                            validateBuy = true; 
                        }
                        // Else...
                        else if (selectedUnitBool)
                        {
                            mvtCursor.first--;
                            if (mvtCursor.first < 0)
                                mvtCursor.first = 0;
                        }
                        else
                        {
                            unsigned int newX = m_player->getCoord().first - 1;

                            if (m_player->getCoord().first == 0)
                                newX = 0;
                           
                            m_player->setCoord(newX, m_player->getCoord().second);
                            mvtCursor = m_player->getCoord();
                        }
                    }
                    // RIGHTKEY
                    else if (event.key.code == sf::Keyboard::Right)
                    {
                        // If in the base menu, then move the unit selector
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
                            if ((unsigned int)mvtCursor.first > m_mapEngine->getWidth() - 1)
                                mvtCursor.first = m_mapEngine->getWidth() - 1;
                        }
                        else
                        {
                            unsigned int newX = m_player->getCoord().first + 1;

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
                            int cost = Unit::getUnitInfo((UNITTYPE)selectedUnitBase).cost;
                            if(m_player->getMoney() >= cost)
                            {
                                // Ask user if he is sure to buy the unie
                                if(validateBuy)
                                {
                                    messageTimer = m_fps * 100;
                                    message = "Are you sure you want to buy this?\n(enter to validate / escape to cancel)";
                                    displayMessage = true;
                                    validateBuy = false;
                                    
                                }
                                else
                                {
                                    // Pay unit
                                    m_player->setMoney(m_player->getMoney() - cost);
                                    validateBuy = true;

                                    // Close message box
                                    messageTimer = m_fps * 4;
                                    displayMessage = false;

                                    // Create unit and close view
                                    pair<int, int> availableCoord = selectedTerrain.getCoord();
                                    Unit unit ((UNITTYPE)selectedUnitBase, availableCoord.first, availableCoord.second, m_player->getType(), unitNPlayerTypeToGid((UNITTYPE)selectedUnitBase, m_player->getType()));
                                    m_world->addUnit(unit);
                                    movedUnits.push_back(unit.getId());
                                    selectedUnitBase = 0;
                                    view = 0;

                                    // Send message
                                    NetPackage np;
                                    np.message = "5::" + coordToString(availableCoord) + "::" + to_string(selectedUnitBase) + "::" + to_string(m_player->getType());
                                    m_netEngine->send(np);
                                }
                            }
                        }
                        else if(selectedUnitBool && view == 2)
                        {
                            // Player wants to move the unit
                            if((unsigned int) mvtCursor.first != m_player->getCoord().first || (unsigned int) mvtCursor.second != m_player->getCoord().second)
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
                                        // Move unit and notify network
                                        NetPackage np;
                                        
                                        
                                        // Prepare movment animation
                                        m_interMove = m_world->getIntermediaire(selectedUnit, mvtCursor);

                                        m_counter = 0;
                                        m_interPos = -1;
                                        m_movingUnit = selectedUnit;
                                        
                                        np.message = "0::"+coordToString(selectedUnit.getCoord())+"::"+coordToString(mvtCursor);
                                        m_netEngine->send(np);

                                        // Move cursor and set moved unit
                                        m_player->setCoord(mvtCursor);
                                        movedUnits.push_back(selectedUnit.getId());

                                        cleared = false;
                                        selectedUnitBool = false;
                                        displayPorte = false;
                                        m_moveUnit = true;

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
                                            // Send message to server
                                            NetPackage np;
                                            np.message = "1::"+coordToString(selectedUnit.getCoord())+"::"+coordToString(mvtCursor);                                            
                                            m_world->combatUnit(selectedUnit, m_world->getUnit(mvtCursor));
                                            np.message += "::"+std::to_string(m_world->getUnit(selectedUnit.getCoord()).getHp())+"::"+std::to_string(m_world->getUnit(mvtCursor).getHp());
                                            m_netEngine->send(np);

                                            // Move cursor
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
                                        default:
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
                    else if(event.key.code == sf::Keyboard::T && m_turn && view != 1)
                    {

                        // Validate turn change
                        if(validateEndTurn)
                        {
                                m_turn = false;

                                // Search for next player
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
                                int nextPlayer = ((index + 1) == players.size() ? players[0] : players[index + 1]);

                                // Send message to network
                                NetPackage np;
                                np.message = "2::" + to_string(nextPlayer);
                                m_netEngine->send(np);
                                displayMessage = false;
                                messageTimer = m_fps * 4;
                                validateEndTurn = false;
                                view = 0;
                                selectedUnitBool = false;
                                displayPorte = false;
                                selectedUnitBase = 0;
                        }
                        else
                        {
                            // Ask vo validation on turn change
                            validateEndTurn = true;
                            message = "Are  you  sure  to  end  the  turn?\n(t to validate / escape to cancel)";
                            displayMessage = true;
                        }
                    }
                    else if(event.key.code == sf::Keyboard::C && selectedUnitBool && (selectedUnit.getType() == MECH || selectedUnit.getType() == INFANTRY))
                    {
                        // Selected unit can capture property
                        Terrain currentTerrain = m_world->getTerrain(selectedUnit.getCoord());
                        if(currentTerrain.getOwner() != m_player->getType() && (currentTerrain.getType() == BASE || currentTerrain.getType() == HQ || currentTerrain.getType() == CITY))
                        {
                            bool foundBuilding = false;
                            for(tuple<pair<int, int>, Unit, bool> buildPos : m_capturingBuilding)
                                if(get<0>(buildPos) == currentTerrain.getCoord())
                                    foundBuilding = true;
            
                            if(!foundBuilding)
                                m_capturingBuilding.push_back(make_tuple(currentTerrain.getCoord(), selectedUnit, true));

                        }
                        selectedUnitBool = false;
                        view = 0;
                    }
                }
            }
            if(event.type == sf::Event::Closed)
                m_window->close();
        }

        

        // Capture management
        vector<pair<int, int>> captureFlags;
        if(m_turn)
        {
            cleared = false;

            vector<vector<tuple<pair<int, int>, Unit, bool>>::iterator> captured;
            vector<vector<tuple<pair<int, int>, Unit, bool>>::iterator> gone;

            for(vector<tuple<pair<int, int>, Unit, bool>>::iterator iter = m_capturingBuilding.begin(); iter != m_capturingBuilding.end(); ++iter)
            {
                // Test if unit still here
                if(m_world->getUnit(get<0>(*iter)) == m_world->getNoneUnit() || m_world->getUnit(get<0>(*iter)).getOwner() != m_player->getType())
                {
                    gone.push_back(iter);
                    get<2>(*iter) = true;    
                }
                if(!get<2>(*iter))
                {
                    Terrain currentTerrain = m_world->getTerrain(get<0>(*iter));
                    get<2>(*iter) = true;
                    if(m_world->capture(get<1>(*iter), get<0>(*iter)))
                    {
                        captured.push_back(iter);
                        NetPackage np;
                        np.message = "6::"+coordToString(get<0>(*iter))+"::"+to_string((int)(m_player->getType()));
                        m_netEngine->send(np);
                    }
                }
                captureFlags.push_back(get<0>(*iter));
            }
        
            for(vector<tuple<pair<int, int>, Unit, bool>>::iterator iter : gone)
            {
                m_world->getTerrain(get<0>(*iter)).resetHp();
                m_capturingBuilding.erase(iter);
            }
            gone.clear();            

            for(vector<tuple<pair<int, int>, Unit, bool>>::iterator iter : captured)
            {
                m_world->getTerrain(get<0>(*iter)).resetHp();
                m_capturingBuilding.erase(iter);
            }
            captured.clear();
        }
        
        // Clear screen
        m_graphicEngine->reload();

        // Update buildings
        m_graphicEngine->checkProperties(m_world);

        // Win managment
        if(m_win)
        {
            m_graphicEngine->drawMap(m_world);
            m_graphicEngine->drawUnits(m_world);
            displayMessage = true;
            messageTimer = m_fps / 25;
            message = "You  win!";
        }    
        else if(m_loose)
        {
            m_graphicEngine->drawMap(m_world);
            m_graphicEngine->drawUnits(m_world);
            displayMessage = true;
            messageTimer = m_fps / 25;
            message = "You  loose!";
        }
    
        if (view == 0)
        {
            // Display map and normal downbar
            m_graphicEngine->drawMap(m_world);
            m_graphicEngine->drawUnits(m_world);
            m_graphicEngine->refreshUserInterface(m_player, m_world, m_turn);

            // Capture flags
            if(!m_turn)
                captureFlags = prevCaptureFlags;

            m_graphicEngine->captureFlags(captureFlags, m_world);
                
        }
        else if (view == 1)
        {
            // Display base menu
            m_graphicEngine->displayBaseInfo(m_player, selectedTerrain, selectedUnitBase);
        }
        else if (view == 2)
        {
            // Display unit downbar and map
            m_graphicEngine->drawMap(m_world);
            m_graphicEngine->drawUnits(m_world);
            m_graphicEngine->displayUnitInfo(m_player, selectedUnit, mvtCursor, m_world, displayPorte);

            // Capture flags
            if(!m_turn)
                captureFlags = prevCaptureFlags;

            m_graphicEngine->captureFlags(captureFlags, m_world);
        }

        // If waiting for players
        if(m_waitingForPlayers)
        {
            displayMessage = true;
            messageTimer = m_fps / 25;
            message = "Waiting  for  " + to_string(m_playerLeft) + "  more  player.";
        }
    
        // If our turn
        if(m_turn)    
            prevCaptureFlags = captureFlags;
        captureFlags.clear();        

        // If message is to be displayed
        if(displayMessage)
            m_graphicEngine->displayMessage(message);

        // Animation movment
        if(m_moveUnit)
        {                    
            if((m_counter % 10) == 0)
            {    
                        
                ++m_interPos;
                
                Unit newmovingUnit = m_world->getUnit(m_interMove[m_interPos]);
                while(newmovingUnit != m_world->getNoneUnit())
                {
                    newmovingUnit = m_world->getUnit(m_interMove[++m_interPos]);
                }                
            
                m_world->moveUnit(m_movingUnit, m_interMove[m_interPos]);
                m_movingUnit = m_world->getUnit(m_interMove[m_interPos]);
            }

            if((unsigned int) m_interPos == m_interMove.size() - 1)
                m_moveUnit = false;

            ++m_counter;
        }

        // If being atacked
        if(m_attackNotify)
        {
            m_graphicEngine->notifyAttack(m_attackNotifyStep, m_attackPos);
            m_graphicEngine->notifyAttack(m_attackNotifyStep, m_attackFrom);
        }

        // Display changed screen
        m_window->display();
    
        // Framerate management
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
        // Notify a moving unit
        m_interMove = m_world->getIntermediaire(m_world->getUnit(p_action.coord[0]), p_action.coord[1]);
        m_moveUnit = true;
        m_counter = 0;
        m_interPos = -1;
        m_movingUnit = m_world->getUnit(p_action.coord[0]);
    }
    else if(p_action.type == ATTACK)
    {
        // Notify an attacking unit
        m_attackPos = p_action.coord[1];
        m_attackFrom = p_action.coord[0];
        m_attackNotifyStep = m_fps * 2.88;
        m_attackNotify = true;

        for(int i = 0 ; i < 2 ; i++)
        {
            // If attacked is dead
            if(p_action.data[i] == -1)
                m_world->removeUnit(m_world->getUnit(p_action.coord[i]));
            else
                m_world->getUnit(p_action.coord[i]).setHp(p_action.data[i]);
        }
    }
    else if(p_action.type == CH_TURN)
    {
        // Notify a turn move
        if(p_action.data[0] == m_player->getType())
            m_turn = true;
        else
            m_turn = false;
    }
    else if(p_action.type == NEW_PLAYER)
    {
        // Notify a new player
        if((unsigned int)p_action.data[0] == m_mapEngine->getPlayers().size())
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
        // Notify Win on diconnect
        m_win = true;
    }
    else if(p_action.type == NEW_UNIT)
    {
        // Notify newly created unit
        UNITTYPE type = (UNITTYPE)p_action.data[0];
        PLAYER_TYPE playerType = (PLAYER_TYPE)p_action.data[1];
        Unit unit (type, p_action.coord[0].first, p_action.coord[0].second, playerType, unitNPlayerTypeToGid(type, playerType));
        m_world->addUnit(unit);
    }
    else if(p_action.type == CAPTURE)
    {
        // Notify a captured building
        m_world->getTerrain(p_action.coord[0]).setOwner((PLAYER_TYPE)p_action.data[0]);
        m_world->refreshVisibleMyProperty(m_world->getTerrain(p_action.coord[0]),true);
        winCondition();
    }
    else if(p_action.type == WIN)
    {
        // Notify win
        m_win = true;
    }
} // notify()

void GENGINE::winCondition()
{
    // Test if all HQ were lost
    if(m_world->getHQCount() == 0)
    {
        m_loose = true;
        NetPackage np;
        np.message = "7::" + to_string(m_player->getType());
        m_netEngine->send(np);    
    }
} // winCondition()
