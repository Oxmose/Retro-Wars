#include <iostream>
#include <string>
#include <utility>

#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>

#include "../MapEngine/MapEngine.h"
#include "../GameEngine/Terrain.h"
#include "../GameEngine/World.h"
#include "../GameEngine/Player.h"
#include "../GameEngine/Unit.h"

#include "GraphicEngine.h"

#define GxENGINE nsGraphicEngine::GraphicEngine


using namespace std;
using namespace nsMapEngine;
using namespace nsGameEngine;

GxENGINE::GraphicEngine() 
{
} // GraphicEngine()

GxENGINE::GraphicEngine(sf::RenderWindow* p_mainWindow, nsMapEngine::MapEngine* p_mapEngine) 
{
    m_mainWindow = p_mainWindow;
    m_mapEngine = p_mapEngine;

    loadMap();

    // Load properties
    m_mapWidth = m_mapEngine->getWidth();
    m_mapHeight = m_mapEngine->getHeight();

    m_relativeMapWidth = m_mapWidth * 16;
    m_relativeMapHeight = m_mapHeight * 16;

    // Load font
    m_font;
    if (!m_font.loadFromFile("./res/font.ttf"))
    {
        cerr << "Can't load display font!" << endl;
    }   

} // GraphicEngine()

GxENGINE::~GraphicEngine() 
{
} // ~GraphicEngine()

sf::IntRect GxENGINE::property_gidToRect(int p_gid) 
{
    return sf::IntRect(((p_gid - 145) % 7) * 16, ((p_gid - 145) / 7) * 16, 16, 16);
} // property_gidToRect()

sf::IntRect GxENGINE::terrain_gidToRect(int p_gid) 
{
    return sf::IntRect(((p_gid - 1) % 18 ) * 16, ((p_gid - 1) / 18) * 16, 16, 16);
} // terrain_gidToRect()

sf::IntRect GxENGINE::unit_gidToRect(int p_gid) 
{
    return sf::IntRect(((p_gid - 229) % 13) * 16, ((p_gid - 229) / 13) * 16, 16, 16);
} // unit_gidToRect()

sf::IntRect GxENGINE::propertyToRect(Terrain p_property)
{
    int gid = 0;
    if(p_property.getType() == HQ)
    {
        switch(p_property.getOwner())
        {
            case RED:
                gid = 145 + 7;
                break;
            case BLUE:
                gid = 145 + 21;
                break;
            case GREEN:
                gid = 145 + 35;
                break;
            case YELLOW:
                gid = 145 + 49;
                break;
            case BLACK:
                gid = 145 + 63;
                break;
        }
    }

    if(p_property.getType() == CITY)
    {
        switch(p_property.getOwner())
        {
            case RED:
                gid = 145 + 8;
                break;
            case BLUE:
                gid = 145 + 22;
                break;
            case GREEN:
                gid = 145 + 36;
                break;
            case YELLOW:
                gid = 145 + 50;
                break;
            case BLACK:
                gid = 145 + 64;
                break;
            case NEUTRAL:
                gid = 145 + 78;
                break;
        }
    }

    if(p_property.getType() == BASE)
    {
        switch(p_property.getOwner())
        {
            case RED:
                gid = 145 + 9;
                break;
            case BLUE:
                gid = 145 + 23;
                break;
            case GREEN:
                gid = 145+37;
                break;
            case YELLOW:
                gid = 145 + 51;
                break;
            case BLACK:
                gid = 145 + 65;
                break;
            case NEUTRAL:
                gid = 145 + 79;
                break;
        }
    }

    return property_gidToRect(gid);
} // propertyToRect()

void GxENGINE::checkProperties(World* p_world)
{
    for(sf::Sprite &spt : m_map[2])
    {
        int x = spt.getPosition().x / 16;
        int y = spt.getPosition().y / 16;
        Terrain prop = p_world->getTerrain(x, y);

        if(prop.isProperty())
            spt.setTextureRect(propertyToRect(prop));
    }
} // checkProperties

void GxENGINE::loadMap() 
{
    // Load terrain
    //For transparency settings, sf:Image needed
    sf::Image image_tileset_terrain;
    image_tileset_terrain.loadFromFile("maps/tilesets/terrain.bmp");
    image_tileset_terrain.createMaskFromColor(sf::Color(0, 0, 0));
    m_tileset_terrain.loadFromImage(image_tileset_terrain);

    // Load properties
    sf::Image image_tileset_property;
    image_tileset_property.loadFromFile("maps/tilesets/property.bmp");
    image_tileset_property.createMaskFromColor(sf::Color(0, 0, 0));
    m_tileset_property.loadFromImage(image_tileset_property);
    
    // Load units
    sf::Image image_tileset_unit;
    image_tileset_unit.loadFromFile("maps/tilesets/unit.bmp");
    image_tileset_unit.createMaskFromColor(sf::Color(0, 0, 0));
    m_tileset_unit.loadFromImage(image_tileset_unit);
    

    for(int iLayerTerrain = 0; iLayerTerrain < 4; ++iLayerTerrain)
    {
        sf::Vector2f curr_position(0, 0);
        for(int gid : m_mapEngine->getLayerTiles(iLayerTerrain))
        {
            if(gid != 0)
            {
                sf::Sprite curr_tile;
                if(iLayerTerrain < 2)
                {
                    curr_tile.setTexture(m_tileset_terrain);
                    curr_tile.setTextureRect(terrain_gidToRect(gid));
                }
                if(iLayerTerrain == 2 || iLayerTerrain == 3)
                {
                    curr_tile.setTexture(m_tileset_property);
                    curr_tile.setTextureRect(property_gidToRect(gid));
                }
                curr_tile.setPosition(curr_position);
                m_map[iLayerTerrain].push_back(curr_tile);
            }
            curr_position.x += 16;
            if(curr_position.x >= m_mapEngine->getWidth() * 16)
            {
                curr_position.x = 0;
                curr_position.y += 16;
            }
        }
    }
} // loadMap()


void GxENGINE::reload() 
{
    // Refresh the screen
    m_mainWindow->clear();
} // reload()

void GxENGINE::drawMap(nsGameEngine::World* p_world) 
{
    for(int iLayer = 0; iLayer < 4; ++iLayer)
        for(sf::Sprite spt : m_map[iLayer])
            m_mainWindow->draw(spt);

    for(int x = 0; x < m_mapWidth; ++x)
        for(int y = 0 ; y < m_mapHeight; ++y)
        {
            if(!p_world->isVisible(x, y))
            {
                sf::RectangleShape rectangle(sf::Vector2f(16, 16));
                rectangle.setPosition(sf::Vector2f(x * 16, y * 16));
                rectangle.setFillColor(sf::Color(0, 0, 0, 100));
                m_mainWindow->draw(rectangle);
            }
        }
} // drawMap()

void GxENGINE::drawUnits(nsGameEngine::World* p_world) 
{
    for(auto unit: p_world->getUnits())
    {
        if(p_world->isVisible(unit.getCoord().first,unit.getCoord().second))
        {
            sf::Sprite spt;
            spt.setTexture(m_tileset_unit);
            spt.setTextureRect(unit_gidToRect(unit.getGid()));
            spt.setPosition(unit.getCoord().first * 16,unit.getCoord().second * 16);
            m_mainWindow->draw(spt);
        }
    }
} // drawUnits()

void GxENGINE::refreshUserInterface(Player *p_player, World *p_world, bool p_turn) 
{
    // Display bottom bar
    displayBar(p_player);
    
    int playerX = p_player->getCoord().first;
    int playerY = p_player->getCoord().second;
    
    // Display player cursor
    sf::RectangleShape cursor(sf::Vector2f(16, 16));
    cursor.setFillColor(sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(255), sf::Uint8(150)));
    cursor.setPosition(playerX * 16, playerY * 16);
    m_mainWindow->draw(cursor);

    // Get unit
    Unit unit = p_world->getUnit(playerX, playerY);
    if (unit.getOwner() != NEUTRAL)
    {
        // Display unit name
        sf::Text unitName(unit.getName(), m_font, 20);
        unitName.setPosition(140, m_relativeMapHeight + 5);
        m_mainWindow->draw(unitName);

        // Display unit owner
        sf::Text unitOwner("Owner : " + getPlayerName(unit.getOwner()), m_font, 15);
        unitOwner.setPosition(140, m_relativeMapHeight + 30);
        m_mainWindow->draw(unitOwner);

        // Display unti information
        sf::Text info("Health : " + to_string(unit.getHp()), m_font, 15);
        info.setPosition(250, m_relativeMapHeight + 10);
        m_mainWindow->draw(info);

        if (unit.getOwner() == p_player->getType())
        {
            /*string ammo;
            if (unit.getAmmo() == -1)
                ammo = "Infinite";
            else
                ammo = to_string(unit.getAmmo());

            // Display ammo information
            sf::Text ammoInfo("Ammo : " + ammo, m_font, 15);
            ammoInfo.setPosition(250, m_relativeMapHeight + 30);
            m_mainWindow->draw(ammoInfo);
            
            if (unit.getType() != INFANTRY)
            {
                // Display unit fuel
                sf::Text fuelInfo("Fuel : " + to_string(unit.getFuel()), m_font, 15);
                fuelInfo.setPosition(250, m_relativeMapHeight + 50);
                m_mainWindow->draw(fuelInfo);
            }
            */
            
            // Display unit help
            sf::Text help("Press  enter  to  select", m_font, 15);
            help.setPosition(330, m_relativeMapHeight + 50);
            m_mainWindow->draw(help);
        }
    }
    else
    {
        // Get terrain
        Terrain ter = p_world->getTerrain(playerX, playerY);
        TerrainType terType = ter.getType();

        // Display terrain name
        sf::Text terrainName(getName(terType), m_font, 20);
        terrainName.setPosition(140, m_relativeMapHeight + 5);
        m_mainWindow->draw(terrainName);

        // Display terrain owner
        sf::Text terrainOwner("Owner : " + getPlayerName(ter.getOwner()), m_font, 15);
        terrainOwner.setPosition(140, m_relativeMapHeight + 30);
        m_mainWindow->draw(terrainOwner);

        // If player owns the terrain
        if (ter.getOwner() == p_player->getType())
        {
            // Display terrain information
            sf::Text info("Health : " + to_string(ter.getHp()) + "\nDefense : " + to_string(ter.getDefense()), m_font, 15);
            info.setPosition(250, m_relativeMapHeight + 10);
            if (terType == BASE)
            {
                info.setString(info.getString() + "\nPress  enter  to  use  the  " + getName(ter.getType()));
            }       
            m_mainWindow->draw(info);
        }
    }

    // Turn info    
    if (!p_turn)
    {
        sf::Text infoTurn("Not your turn" , m_font, 15);
        infoTurn.setPosition(m_relativeMapWidth / 2 - infoTurn.getGlobalBounds().width / 2, 2);

        sf::RectangleShape turnRect(sf::Vector2f(100, 30));
        turnRect.setFillColor(sf::Color(sf::Uint8(33), sf::Uint8(33), sf::Uint8(33), sf::Uint8(100)));
        turnRect.setPosition(m_relativeMapWidth / 2 - 50, 0);

        m_mainWindow->draw(turnRect);
        m_mainWindow->draw(infoTurn);
    }
} // refreshUserInterface()

void GxENGINE::displayUnitInfo(Player *p_player, Unit &p_unit, const pair<int, int> &p_mvtCursor, nsGameEngine::World* p_world, bool p_displayPorte)
{
    // Display black back
    sf::RectangleShape downBar(sf::Vector2f(m_relativeMapWidth, 75));
    downBar.setPosition(0, m_relativeMapHeight);
    downBar.setFillColor(sf::Color(sf::Uint8(75), sf::Uint8(75), sf::Uint8(75), sf::Uint8(150)));
    m_mainWindow->draw(downBar);

    // Display select unit info
    sf::Text unitName("Selected : " + p_unit.getName(), m_font, 20);
    unitName.setPosition(5, m_relativeMapHeight + 5);    
    m_mainWindow->draw(unitName);

    // Display player cursor    
    sf::RectangleShape cursor(sf::Vector2f(16, 16));
    cursor.setFillColor(sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(255), sf::Uint8(200)));
    cursor.setPosition(p_player->getCoord().first * 16, p_player->getCoord().second * 16);
    m_mainWindow->draw(cursor);

    // Display possible movments
    sf::RectangleShape possibleMove(sf::Vector2f(16, 16));
    possibleMove.setOutlineColor(sf::Color(sf::Uint8(0), sf::Uint8(255), sf::Uint8(100), sf::Uint8(255)));
    possibleMove.setOutlineThickness(0.5);
    possibleMove.setFillColor(sf::Color(sf::Uint8(0), sf::Uint8(255), sf::Uint8(100), sf::Uint8(100)));
    
    vector<pair<int, int>> accessible = p_world->getAccessible(p_unit);
    vector<pair<int, int>> enemies = p_world->getPortee(p_unit);

    for (pair<int, int> Coord : accessible)
    {
        possibleMove.setPosition(Coord.first * 16, Coord.second * 16);
        m_mainWindow->draw(possibleMove);
    }
    

    // Movment cursor management
    sf::RectangleShape mvtCursor(sf::Vector2f(16, 16));

    bool colored = false;
    
    // If cursor is over an enemy
    for (pair<int, int> Coord : enemies)
    {
        if (p_mvtCursor.first == Coord.first && p_mvtCursor.second == Coord.second)
        {
            mvtCursor.setFillColor(sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(50), sf::Uint8(200)));

            sf::RectangleShape damageInfo(sf::Vector2f(50, 20));
            damageInfo.setFillColor(sf::Color(sf::Uint8(75), sf::Uint8(75), sf::Uint8(75), sf::Uint8(200)));
            damageInfo.setPosition(p_mvtCursor.first * 16 + 16, p_mvtCursor.second * 16 - 8);
            m_mainWindow->draw(damageInfo);

            sf::Text damageInfoText(to_string(p_world->getDamage(p_unit, p_world->getUnit(p_mvtCursor), true)).substr(0, 4) + "%", m_font, 15);
            damageInfoText.setPosition(p_mvtCursor.first * 16 + 25, p_mvtCursor.second * 16 - 8);
            m_mainWindow->draw(damageInfoText);
            colored = true;
            break;
        }
    }
    
    if (!colored)
    {
        bool acces = false;      
        for (pair<int, int> Coord : accessible)
        {
            if (p_mvtCursor.first == Coord.first && p_mvtCursor.second == Coord.second)
            {
                mvtCursor.setFillColor(sf::Color(sf::Uint8(50), sf::Uint8(150), sf::Uint8(255), sf::Uint8(200)));
                acces = true;
                break;
            }
        }  
        if (!acces && p_mvtCursor.first == p_player->getCoord().first && p_mvtCursor.second == p_player->getCoord().second)
            mvtCursor.setFillColor(sf::Color(sf::Uint8(0), sf::Uint8(0), sf::Uint8(0), sf::Uint8(50)));
        else if (!acces)
            mvtCursor.setFillColor(sf::Color(sf::Uint8(255), sf::Uint8(100), sf::Uint8(100), sf::Uint8(200)));            
        
    }
    
    mvtCursor.setPosition(p_mvtCursor.first * 16, p_mvtCursor.second * 16);
    m_mainWindow->draw(mvtCursor);

    // Display enemies that can be reached
    if (p_displayPorte)
    {
        sf::RectangleShape enemiesRect(sf::Vector2f(16, 16));
        enemiesRect.setFillColor(sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(50), sf::Uint8(200)));
        for (pair<int, int> Coord : enemies)
        {
            enemiesRect.setPosition(Coord.first * 16, Coord.second * 16);
            m_mainWindow->draw(enemiesRect);
        }
    }

    sf::Text info("Health : " + to_string(p_unit.getHp()), m_font, 15);
    info.setPosition(250, m_relativeMapHeight + 10);
    m_mainWindow->draw(info);

    /*string ammo;

    if (p_unit.getAmmo() == -1)
        ammo = "Infinite";
    else
        ammo = to_string(p_unit.getAmmo());

    sf::Text ammoInfo("Ammo : " + ammo, m_font, 15);
    ammoInfo.setPosition(250, m_relativeMapHeight + 30);
    m_mainWindow->draw(ammoInfo);
    
    if (p_unit.getType() != INFANTRY)
    {
        sf::Text fuelInfo("Fuel : " + to_string(p_unit.getFuel()), m_font, 15);
        fuelInfo.setPosition(250, m_relativeMapHeight + 50);
        m_mainWindow->draw(fuelInfo);
    }
    */
} // displayUnitInfo()

void GxENGINE::displayBaseInfo(nsGameEngine::Player *p_player, const nsGameEngine::Terrain &p_terrain) 
{
    // Background
    sf::RectangleShape back(sf::Vector2f(m_relativeMapWidth, m_relativeMapHeight));
    back.setFillColor(sf::Color(sf::Uint8(225), sf::Uint8(225), sf::Uint8(225), sf::Uint8(200)));
    back.setPosition(0, 0);
    m_mainWindow->draw(back);

    displayBar(p_player);
    sf::Text quit("Press  escape  to  quit" , m_font, 15);
    quit.setPosition(140, m_relativeMapHeight + 50);

    m_mainWindow->draw(quit);

    // DIsplay title
    sf::Text title("Base", m_font, 25);
    title.setPosition(m_relativeMapWidth / 2 - title.getGlobalBounds().width / 2, 2);

    sf::RectangleShape titleRect(sf::Vector2f(200, 40));
    titleRect.setFillColor(sf::Color(sf::Uint8(100), sf::Uint8(100), sf::Uint8(100), sf::Uint8(255)));
    titleRect.setPosition(m_relativeMapWidth / 2 - 100, 0);
    m_mainWindow->draw(titleRect);
    m_mainWindow->draw(title);

    // Display information
    sf::Text info("This  is  your  base", m_font, 16);
    info.setPosition(5, 50);
    info.setColor(sf::Color(0, 0, 0, 255));
    m_mainWindow->draw(info);
} // displayBaseInfo()


string GxENGINE::getName(TerrainType terrain) 
{
    switch(terrain)
    {
        case 0:
            return "Plain";
        case 1:
            return "Mountain";
        case 2:
            return "Woods";
        case 3:
            return "Roads";
        case 4:
            return "Bridges"; 
        case 5:
            return "City";
        case 6:
            return "Headquarter";
        case 7:
            return "Base";
        case 8:
            return "Other";
    }
} // getName()

void GxENGINE::displayBar(Player *p_player)
{
    // Display black back
    sf::RectangleShape downBar(sf::Vector2f(m_relativeMapWidth, 75));
    downBar.setPosition(0, m_relativeMapHeight);
    downBar.setFillColor(sf::Color(sf::Uint8(75), sf::Uint8(75), sf::Uint8(75), sf::Uint8(150)));
    m_mainWindow->draw(downBar);

    // Display inforation about the player
    sf::Text playerName("General " + p_player->getPlayerName(), m_font, 20);
    sf::Text playerMoney("Resources : " + std::to_string(p_player->getMoney()) + "$", m_font, 16);

    playerName.setPosition(5, m_relativeMapHeight + 5);
    playerMoney.setPosition(5, m_relativeMapHeight + 30);
    m_mainWindow->draw(playerName);
    m_mainWindow->draw(playerMoney);
} // displayBar()

void GxENGINE::displayMessage(const std::string &p_message)
{
    // Display a message in the middle of the screen
    sf::RectangleShape back(sf::Vector2f(300, 50));
    back.setPosition(m_relativeMapWidth / 2 - 150, m_relativeMapHeight / 2 - 25);
    back.setFillColor(sf::Color(sf::Uint8(75), sf::Uint8(75), sf::Uint8(75), sf::Uint8(225)));
    m_mainWindow->draw(back);

    sf::Text message(p_message, m_font, 16);
    message.setPosition(m_relativeMapWidth / 2 - message.getGlobalBounds().width / 2, m_relativeMapHeight / 2 - message.getGlobalBounds().height / 2 - 5);

    m_mainWindow->draw(message);
} // displayMessage()
