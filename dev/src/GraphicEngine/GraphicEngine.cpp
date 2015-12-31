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

    // Load map graphics
    loadMap();

    // Load other graphic resources
    loadResources();

    // Load properties
    m_mapWidth = m_mapEngine->getWidth();
    m_mapHeight = m_mapEngine->getHeight();

    m_relativeMapWidth = m_mapWidth * 16;
    m_relativeMapHeight = m_mapHeight * 16;
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
			default:
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

void GxENGINE::loadResources()
{
    // Explosion texture
    if (!m_explosionTexture.loadFromFile(string(GRAPHIC_RES_IMG) + "explosion.png"))
    {
        cerr << "Can't load explosion texture!" << endl;
    }
    m_explosionTexture.setSmooth(true);
    m_explosionSprite.setTexture(m_explosionTexture);

    // Load font
    if (!m_font.loadFromFile("./res/font.ttf"))
    {
        cerr << "Can't load display font!" << endl;
    }   

    // Load background textures;
    if(!m_backgroundTexture.loadFromFile(string(GRAPHIC_RES_IMG) + "bg.jpg"))
    {
        cerr << "Can't load background resources!" << endl;
    }
    m_backgroundTexture.setSmooth(true);
    m_backgroundTexture.setRepeated(true);

    if(!m_baseBgTexture.loadFromFile(string(GRAPHIC_RES_IMG) + "basebg.jpg"))
    {
        cerr << "Can't load background resources!" << endl;
    }
    m_baseBgTexture.setSmooth(true);
    m_baseBgTexture.setRepeated(true);

    // Load misc textures
    sf::Image miscImage;
    miscImage.loadFromFile(string(GRAPHIC_RES_IMG) + "misc.png");
    miscImage.createMaskFromColor(sf::Color(0, 128, 128, 255));
    if(!m_miscTextures.loadFromImage(miscImage))
    {
        cerr << "Can't load misc resources!" << endl;
    }
    m_miscTextures.setSmooth(true);
} // loadResources()

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
    cursor.setFillColor(sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(255), sf::Uint8(200)));
    cursor.setOutlineThickness(2);
    cursor.setOutlineColor(sf::Color(220, 220, 220, 150));
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

        // Draw health bar
        int life = unit.getHp();
        int remainPercent = (((float)life / (float)Unit::getUnitInfo(unit.getType()).hp) * 100.0) / 2.0;
        int lostPercent = 50 - remainPercent;

        sf::RectangleShape lifeBar(sf::Vector2f(52, 12));
        lifeBar.setPosition(230, m_relativeMapHeight + 13);
        m_mainWindow->draw(lifeBar);
    
        sf::RectangleShape lifeBarFillGreen(sf::Vector2f(remainPercent, 10));
        lifeBarFillGreen.setFillColor(sf::Color(0, 255, 0, 255));
        lifeBarFillGreen.setPosition(231, m_relativeMapHeight + 14);
        m_mainWindow->draw(lifeBarFillGreen);
    
        sf::RectangleShape lifeBarFillRed(sf::Vector2f(lostPercent, 10));
        lifeBarFillRed.setFillColor(sf::Color(255, 0, 0, 255));
        lifeBarFillRed.setPosition(231 + remainPercent, m_relativeMapHeight + 14);
        m_mainWindow->draw(lifeBarFillRed);

        sf::Text info(to_string(remainPercent * 2) + " %", m_font, 15);
        info.setPosition(285, m_relativeMapHeight + 10);
        m_mainWindow->draw(info);

        // Draw separator
        sf::RectangleShape separator(sf::Vector2f(2, 65));
        separator.setPosition(335, m_relativeMapHeight + 5);
        m_mainWindow->draw(separator);

        if (unit.getOwner() == p_player->getType())
        {
            // Display unit message
        
            sf::Text message("\"" + Unit::getUnitInfo(unit.getType()).message + "\"", m_font, 14);
            message.setPosition(345, m_relativeMapHeight + 5);
            m_mainWindow->draw(message);

            sf::Text help("Enter  to  select", m_font, 15);
            help.setPosition(345, m_relativeMapHeight + 50);
            m_mainWindow->draw(help);

            string ammo;
            if (unit.getAmmo() == -1)
                ammo = "Infinite";
            else
                ammo = to_string(unit.getAmmo());

            // Display ammo information
            sf::Text ammoInfo("Ammo : " + ammo, m_font, 15);
            ammoInfo.setPosition(140, m_relativeMapHeight + 30);
            m_mainWindow->draw(ammoInfo);
            
            if (unit.getType() != INFANTRY)
            {
                // Display unit fuel
                sf::Text fuelInfo("Fuel : " + to_string(unit.getFuel()), m_font, 15);
                fuelInfo.setPosition(140, m_relativeMapHeight + 50);
                m_mainWindow->draw(fuelInfo);
            }           
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

        // Draw health bar
        if(terType == BASE || terType == HQ || terType == CITY)
        {
            int life = ter.getHp();
            int remainPercent = ((float)life / 20.0 * 100.0) / 2.0;
            int lostPercent = 50 - remainPercent;

            sf::RectangleShape lifeBar(sf::Vector2f(52, 12));
            lifeBar.setPosition(140, m_relativeMapHeight + 33);
            m_mainWindow->draw(lifeBar);
        
            sf::RectangleShape lifeBarFillGreen(sf::Vector2f(remainPercent, 10));
            lifeBarFillGreen.setFillColor(sf::Color(0, 255, 0, 255));
            lifeBarFillGreen.setPosition(141, m_relativeMapHeight + 34);
            m_mainWindow->draw(lifeBarFillGreen);
        
            sf::RectangleShape lifeBarFillRed(sf::Vector2f(lostPercent, 10));
            lifeBarFillRed.setFillColor(sf::Color(255, 0, 0, 255));
            lifeBarFillRed.setPosition(141 + remainPercent, m_relativeMapHeight + 34);
            m_mainWindow->draw(lifeBarFillRed);

            sf::Text info(to_string(remainPercent * 2) + " %", m_font, 15);
            info.setPosition(195, m_relativeMapHeight + 29);
            m_mainWindow->draw(info);
        }

        // Draw separator
        sf::RectangleShape separator(sf::Vector2f(2, 65));
        separator.setPosition(335, m_relativeMapHeight + 5);
        m_mainWindow->draw(separator);

        // If player owns the terrain
        if (ter.getOwner() == p_player->getType())
        {
            // Display terrain information
            sf::Text infoDef("Defense : " + to_string(ter.getDefense()), m_font, 15);
            infoDef.setPosition(140, m_relativeMapHeight + 50);
            m_mainWindow->draw(infoDef);
            if (terType == BASE)
            {
                sf::Text help("Press  enter  to  use", m_font, 15);
                help.setPosition(345, m_relativeMapHeight + 50);
                m_mainWindow->draw(help);
            }       
            
        }
    }

    manageTurn(p_turn);
} // refreshUserInterface()

void GxENGINE::displayUnitInfo(Player *p_player, Unit &p_unit, const pair<int, int> &p_mvtCursor, nsGameEngine::World* p_world, bool p_displayPorte)
{
    displayBar(p_player);

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
			if((p_mvtCursor.first * 16 + 50) < m_relativeMapWidth)
            	damageInfo.setPosition(p_mvtCursor.first * 16 + 16, p_mvtCursor.second * 16 - 5);
			else
				damageInfo.setPosition(p_mvtCursor.first * 16 + -59, p_mvtCursor.second * 16 - 5);

            m_mainWindow->draw(damageInfo);

            sf::Text damageInfoText(to_string(p_world->getDamage(p_unit, p_world->getUnit(p_mvtCursor), true)).substr(0, 4) + "%", m_font, 15);

			if((p_mvtCursor.first * 16 + 50) < m_relativeMapWidth)
            	damageInfoText.setPosition(p_mvtCursor.first * 16 + 25, p_mvtCursor.second * 16 - 5);
			else
				damageInfoText.setPosition(p_mvtCursor.first * 16 - 50, p_mvtCursor.second * 16 - 5);
	
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

    // Display unit name
    sf::Text unitName(p_unit.getName(), m_font, 20);
    unitName.setPosition(140, m_relativeMapHeight + 5);
    m_mainWindow->draw(unitName);

    // Draw health bar
    int life = p_unit.getHp();
    int remainPercent = (((float)life / (float)Unit::getUnitInfo(p_unit.getType()).hp) * 100.0) / 2.0;
    int lostPercent = 50 - remainPercent;

    sf::RectangleShape lifeBar(sf::Vector2f(52, 12));
    lifeBar.setPosition(230, m_relativeMapHeight + 13);
    m_mainWindow->draw(lifeBar);

    sf::RectangleShape lifeBarFillGreen(sf::Vector2f(remainPercent, 10));
    lifeBarFillGreen.setFillColor(sf::Color(0, 255, 0, 255));
    lifeBarFillGreen.setPosition(231, m_relativeMapHeight + 14);
    m_mainWindow->draw(lifeBarFillGreen);

    sf::RectangleShape lifeBarFillRed(sf::Vector2f(lostPercent, 10));
    lifeBarFillRed.setFillColor(sf::Color(255, 0, 0, 255));
    lifeBarFillRed.setPosition(231 + remainPercent, m_relativeMapHeight + 14);
    m_mainWindow->draw(lifeBarFillRed);

    sf::Text info(to_string(remainPercent * 2) + " %", m_font, 15);
    info.setPosition(285, m_relativeMapHeight + 10);
    m_mainWindow->draw(info);

    // Draw separator
    sf::RectangleShape separator(sf::Vector2f(2, 65));
    separator.setPosition(335, m_relativeMapHeight + 5);
    m_mainWindow->draw(separator);

    // Display unit help and message
    sf::Text message("\"" + Unit::getUnitInfo(p_unit.getType()).message + "\"", m_font, 14);
    message.setPosition(345, m_relativeMapHeight + 5);
    m_mainWindow->draw(message);

	string ability;
	int position;
	if(p_unit.getType() == MECH || p_unit.getType() == INFANTRY)
	{
		ability = "C  to  capture\nW  for  attack  range\nEscape  to  deselect";
		position = m_relativeMapHeight + 25;
	}
	else
	{
		ability = "W  for  attack  range\nEscape  to  deselect";
		position = m_relativeMapHeight + 35;
	}
    sf::Text help(ability, m_font, 14);
    help.setPosition(345, position);
    m_mainWindow->draw(help);

    string ammo;
    if (p_unit.getAmmo() == -1)
        ammo = "Infinite";
    else
        ammo = to_string(p_unit.getAmmo());

    // Display ammo information
    sf::Text ammoInfo("Ammo : " + ammo, m_font, 15);
    ammoInfo.setPosition(140, m_relativeMapHeight + 30);
    m_mainWindow->draw(ammoInfo);
    
    if (p_unit.getType() != INFANTRY)
    {
        // Display unit fuel
        sf::Text fuelInfo("Fuel : " + to_string(p_unit.getFuel()), m_font, 15);
        fuelInfo.setPosition(140, m_relativeMapHeight + 50);
        m_mainWindow->draw(fuelInfo);
    }           
    manageTurn(true);
} // displayUnitInfo()

void GxENGINE::displayBaseInfo(nsGameEngine::Player *p_player, const nsGameEngine::Terrain &p_terrain, const int &p_select) 
{
    // Background
    sf::Sprite back;
    back.setTexture(m_baseBgTexture);   
    back.setColor(sf::Color(75, 75, 75, 150));
    back.setTextureRect(sf::IntRect(0, 0, m_relativeMapWidth, m_relativeMapHeight));
    m_mainWindow->draw(back);

    displayBar(p_player);
    sf::Text quit("Press  escape  to  quit" , m_font, 15);

    quit.setPosition(350, m_relativeMapHeight + 50);
    m_mainWindow->draw(quit);

    // Draw separator
    sf::RectangleShape separatorText(sf::Vector2f(2, 65));
    separatorText.setPosition(335, m_relativeMapHeight + 5);
    m_mainWindow->draw(separatorText);

    // DIsplay title
    sf::Text title("Base", m_font, 25);
    title.setPosition(5, 2);
    m_mainWindow->draw(title);

    // Display information
    sf::Text info("Create  new  unit  :", m_font, 16);
    info.setPosition(5, 50);
    m_mainWindow->draw(info);

    // ###########################################  Units menu
    int colorSelector;
    if(p_player->getType() == RED)
    {
        colorSelector = 0;
    }
    else if(p_player->getType() == BLUE)
    {
        colorSelector = 2;
    }
    
    sf::RectangleShape cursor(sf::Vector2f(80, 75));
    cursor.setFillColor(sf::Color(255, 255, 255, 50));
    cursor.setOutlineColor(sf::Color(75, 75, 75, 50));
    cursor.setOutlineThickness(2);

    sf::RectangleShape separator (sf::Vector2f(2, 65));
    separator.setPosition(140, m_relativeMapHeight + 5);

    // Retrive informations
    UnitInfo infInfo = Unit::getUnitInfo(INFANTRY);
    UnitInfo mdtInfo = Unit::getUnitInfo(MDTANK);
    UnitInfo recInfo = Unit::getUnitInfo(RECON);
    UnitInfo artInfo = Unit::getUnitInfo(ARTILLERY);
    UnitInfo netInfo = Unit::getUnitInfo(NEOTANK);
    UnitInfo mgtInfo = Unit::getUnitInfo(MEGATANK);
    UnitInfo mecInfo = Unit::getUnitInfo(MECH);
    UnitInfo takInfo = Unit::getUnitInfo(TANK);
    UnitInfo rocInfo = Unit::getUnitInfo(ROCKET);

    int playerMoney = p_player->getMoney();

    sf::Sprite mineral;
    mineral.setTexture(m_miscTextures);
    mineral.setTextureRect(sf::IntRect(0, 0, 47, 50));
    mineral.setScale(0.35, 0.35);

    // ############### Infantry button
    sf::Sprite infantryBtn;
    infantryBtn.setTexture(m_tileset_unit);
    infantryBtn.setTextureRect(sf::IntRect(0, colorSelector * 16, 16, 16));
    infantryBtn.setPosition(27, 80);
    infantryBtn.setScale(3, 3); 
    if(playerMoney < infInfo.cost)
        infantryBtn.setColor(sf::Color(80, 80, 80, 255));
  
    sf::Text infantryCost(to_string(infInfo.cost), m_font, 15);
    infantryCost.setPosition(36, 130);
    mineral.setPosition(16, 130);
    m_mainWindow->draw(mineral);
    

    // ############### MdTank button
    sf::Sprite mdTankBtn;
    mdTankBtn.setTexture(m_tileset_unit);
    mdTankBtn.setTextureRect(sf::IntRect(16, colorSelector * 16, 16, 16));
    mdTankBtn.setPosition(116, 80);
    mdTankBtn.setScale(3, 3);
    if(playerMoney < mdtInfo.cost)
        mdTankBtn.setColor(sf::Color(80, 80, 80, 255));
     
  
    sf::Text mdTankCost(to_string(mdtInfo.cost), m_font, 15);
    mdTankCost.setPosition(123, 130);
    mineral.setPosition(103, 130);
    m_mainWindow->draw(mineral);
    
    // ############### Recon button
    sf::Sprite recBtn;
    recBtn.setTexture(m_tileset_unit);
    recBtn.setTextureRect(sf::IntRect(32, colorSelector * 16, 16, 16));
    recBtn.setPosition(211, 80);
    recBtn.setScale(3, 3);
    if(playerMoney < recInfo.cost)
        recBtn.setColor(sf::Color(80, 80, 80, 255));
  
    sf::Text recCost(to_string(recInfo.cost), m_font, 15);
    recCost.setPosition(216, 130);
    mineral.setPosition(196, 130);
    m_mainWindow->draw(mineral);

    // ############### Artillery button
    sf::Sprite artBtn;
    artBtn.setTexture(m_tileset_unit);
    artBtn.setTextureRect(sf::IntRect(48, colorSelector * 16, 16, 16));
    artBtn.setPosition(306, 80);
    artBtn.setScale(3, 3);
    if(playerMoney < artInfo.cost)
        artBtn.setColor(sf::Color(80, 80, 80, 255));
  
    sf::Text artCost(to_string(artInfo.cost), m_font, 15);
    artCost.setPosition(309, 130);
    mineral.setPosition(289, 130);
    m_mainWindow->draw(mineral);

    // ############### NeoTank button
    sf::Sprite neoTankBtn;
    neoTankBtn.setTexture(m_tileset_unit);
    neoTankBtn.setTextureRect(sf::IntRect(144, colorSelector * 16, 16, 16));
    neoTankBtn.setPosition(409, 80);
    neoTankBtn.setScale(3, 3);
    if(playerMoney < netInfo.cost)
        neoTankBtn.setColor(sf::Color(80, 80, 80, 255));
    
    sf::Text neoTankCost(to_string(netInfo.cost), m_font, 15);
    neoTankCost.setPosition(410, 130);
    mineral.setPosition(390, 130);
    m_mainWindow->draw(mineral);    

    // ############### MegaTank button
    sf::Sprite mgTankBtn;
    mgTankBtn.setTexture(m_tileset_unit);
    mgTankBtn.setTextureRect(sf::IntRect(160, colorSelector * 16, 16, 16));
    mgTankBtn.setPosition(25, 180);
    mgTankBtn.setScale(3, 3);
    if(playerMoney < mgtInfo.cost)
        mgTankBtn.setColor(sf::Color(80, 80, 80, 255));
  
    sf::Text mgTankCost(to_string(mgtInfo.cost), m_font, 15);
    mgTankCost.setPosition(28, 230); 
    mineral.setPosition(8, 230);
    m_mainWindow->draw(mineral);

    // ############### Mech button
    sf::Sprite mechBtn;
    mechBtn.setTexture(m_tileset_unit);
    mechBtn.setTextureRect(sf::IntRect(0, (colorSelector + 1) * 16, 16, 16));
    mechBtn.setPosition(113, 180);
    mechBtn.setScale(3, 3);
    if(playerMoney < mecInfo.cost)
        mechBtn.setColor(sf::Color(80, 80, 80, 255));
  
    sf::Text mechCost(to_string(mecInfo.cost), m_font, 15);
    mechCost.setPosition(125, 230); 
    mineral.setPosition(105, 230);
    m_mainWindow->draw(mineral);

    // ############### Tank button
    sf::Sprite tankBtn;
    tankBtn.setTexture(m_tileset_unit);
    tankBtn.setTextureRect(sf::IntRect(16, (colorSelector + 1) * 16, 16, 16));
    tankBtn.setPosition(205, 180);
    tankBtn.setScale(3, 3);
    if(playerMoney < takInfo.cost)
        tankBtn.setColor(sf::Color(80, 80, 80, 255));
  
    sf::Text tankCost(to_string(takInfo.cost), m_font, 15);
    tankCost.setPosition(216, 230); 
    mineral.setPosition(196, 230);
    m_mainWindow->draw(mineral);

    // ############### Rocket button
    sf::Sprite rocketBtn;
    rocketBtn.setTexture(m_tileset_unit);
    rocketBtn.setTextureRect(sf::IntRect(48, (colorSelector + 1) * 16, 16, 16));
    rocketBtn.setPosition(300, 180);
    rocketBtn.setScale(3, 3);
    if(playerMoney < rocInfo.cost)
        rocketBtn.setColor(sf::Color(80, 80, 80, 255));
  
    sf::Text rocketCost(to_string(rocInfo.cost), m_font, 15);
    rocketCost.setPosition(309, 230); 
    mineral.setPosition(289, 230);
    m_mainWindow->draw(mineral);   

    // ################ UNIT INFO    
    sf::Text unitName("Unit", m_font, 20);
    unitName.setPosition(140, m_relativeMapHeight + 5);
    sf::Text unitInfo1("Unit", m_font, 15);
    unitInfo1.setPosition(140, m_relativeMapHeight + 25);
    sf::Text unitInfo2("Unit", m_font, 15);
    unitInfo2.setPosition(275, m_relativeMapHeight + 25);

    if(p_select == 0)
    {
        cursor.setPosition(8, 75);
        // Infantry info
        string ammo;
        if(infInfo.ammo == -1)
            ammo = "Infinite";
        else
            ammo = to_string(infInfo.ammo);

        unitName.setString("Infantry");

        unitInfo1.setString("Movment:  " + to_string(infInfo.mvt) + 
                           "\nAmmo:  " + ammo + 
                           "\nRange:  " + to_string(infInfo.range));
        unitInfo2.setString("Vision: " + to_string(infInfo.vision)); 

        if(p_player->getMoney() < infInfo.cost)
            cursor.setFillColor(sf::Color(255, 50, 50, 50));        
    }
    else if(p_select == 1)
    {
        cursor.setPosition(98, 75);

        string ammo;
        if(mdtInfo.ammo == -1)
            ammo = "Infinite";
        else
            ammo = to_string(mdtInfo.ammo);

        unitName.setString("MDTank");

        unitInfo1.setString("Movment:  " + to_string(mdtInfo.mvt) + 
                           "\nAmmo:  " + ammo + 
                           "\nRange:  " + to_string(mdtInfo.range));
        unitInfo2.setString("Vision: " + to_string(mdtInfo.vision) +
                            "\nFuel: " + to_string(mdtInfo.fuel));  

        if(p_player->getMoney() < mdtInfo.cost)
            cursor.setFillColor(sf::Color(255, 50, 50, 50));      
    }
    else if(p_select == 2)
    {
        cursor.setPosition(190, 75);

        string ammo;
        if(recInfo.ammo == -1)
            ammo = "Infinite";
        else
            ammo = to_string(recInfo.ammo);

        unitName.setString("Recon");

        unitInfo1.setString("Movment:  " + to_string(recInfo.mvt) + 
                           "\nAmmo:  " + ammo + 
                           "\nRange:  " + to_string(recInfo.range));
        unitInfo2.setString("Vision: " + to_string(recInfo.vision) +
                            "\nFuel: " + to_string(recInfo.fuel)); 

        if(p_player->getMoney() < recInfo.cost)
            cursor.setFillColor(sf::Color(255, 50, 50, 50));        
    }
    else if(p_select == 3)
    {
        cursor.setPosition(283, 75);

        string ammo;
        if(artInfo.ammo == -1)
            ammo = "Infinite";
        else
            ammo = to_string(artInfo.ammo);

        unitName.setString("Artillery");

        unitInfo1.setString("Movment:  " + to_string(artInfo.mvt) + 
                           "\nAmmo:  " + ammo + 
                           "\nRange:  " + to_string(artInfo.range));
        unitInfo2.setString("Vision: " + to_string(artInfo.vision) +
                            "\nFuel: " + to_string(artInfo.fuel)); 

        if(p_player->getMoney() < artInfo.cost)
            cursor.setFillColor(sf::Color(255, 50, 50, 50));        
    }
    else if(p_select == 4)
    {
        cursor.setPosition(391, 75);

        string ammo;
        if(netInfo.ammo == -1)
            ammo = "Infinite";
        else
            ammo = to_string(netInfo.ammo);

        unitName.setString("NeoTank");

        unitInfo1.setString("Movment:  " + to_string(netInfo.mvt) + 
                           "\nAmmo:  " + ammo + 
                           "\nRange:  " + to_string(netInfo.range));
        unitInfo2.setString("Vision: " + to_string(netInfo.vision) +
                            "\nFuel: " + to_string(netInfo.fuel)); 

        if(p_player->getMoney() < netInfo.cost)
            cursor.setFillColor(sf::Color(255, 50, 50, 50));        
    }
    else if(p_select == 5)
    {
        cursor.setPosition(8, 175);

        string ammo;
        if(mgtInfo.ammo == -1)
            ammo = "Infinite";
        else
            ammo = to_string(mgtInfo.ammo);

        unitName.setString("MegaTank");

        unitInfo1.setString("Movment:  " + to_string(mgtInfo.mvt) + 
                           "\nAmmo:  " + ammo + 
                           "\nRange:  " + to_string(mgtInfo.range));
        unitInfo2.setString("Vision: " + to_string(mgtInfo.vision) +
                            "\nFuel: " + to_string(mgtInfo.fuel)); 

        if(p_player->getMoney() < mgtInfo.cost)
            cursor.setFillColor(sf::Color(255, 50, 50, 50));        
    }
    else if(p_select == 6)
    {
        cursor.setPosition(98, 175);

        string ammo;
        if(mecInfo.ammo == -1)
            ammo = "Infinite";
        else
            ammo = to_string(mecInfo.ammo);

        unitName.setString("Mech");

        unitInfo1.setString("Movment:  " + to_string(mecInfo.mvt) + 
                           "\nAmmo:  " + ammo + 
                           "\nRange:  " + to_string(mecInfo.range));
        unitInfo2.setString("Vision: " + to_string(mecInfo.vision) +
                            "\nFuel: " + to_string(mecInfo.fuel)); 

        if(p_player->getMoney() < mecInfo.cost)
            cursor.setFillColor(sf::Color(255, 50, 50, 50));        
    }
    else if(p_select == 7)
    {
        cursor.setPosition(190, 175);

        string ammo;
        if(takInfo.ammo == -1)
            ammo = "Infinite";
        else
            ammo = to_string(takInfo.ammo);

        unitName.setString("Tank");

        unitInfo1.setString("Movment:  " + to_string(takInfo.mvt) + 
                           "\nAmmo:  " + ammo + 
                           "\nRange:  " + to_string(takInfo.range));
        unitInfo2.setString("Vision: " + to_string(takInfo.vision) +
                            "\nFuel: " + to_string(takInfo.fuel)); 

        if(p_player->getMoney() < takInfo.cost)
            cursor.setFillColor(sf::Color(255, 50, 50, 50));        
    }
    else if(p_select == 8)
    {
        cursor.setPosition(283, 175);

        string ammo;
        if(rocInfo.ammo == -1)
            ammo = "Infinite";
        else
            ammo = to_string(rocInfo.ammo);

        unitName.setString("Rocket");

        unitInfo1.setString("Movment:  " + to_string(rocInfo.mvt) + 
                           "\nAmmo:  " + ammo + 
                           "\nRange:  " + to_string(rocInfo.range));
        unitInfo2.setString("Vision: " + to_string(rocInfo.vision) +
                            "\nFuel: " + to_string(rocInfo.fuel)); 

        if(p_player->getMoney() < rocInfo.cost)
            cursor.setFillColor(sf::Color(255, 50, 50, 50));        
    }


    // Manage the order drawables are displayed

    // Display cursor behind the units and separator
    m_mainWindow->draw(cursor);

    // Display buttons and costs
    m_mainWindow->draw(infantryBtn);
    m_mainWindow->draw(infantryCost);
    m_mainWindow->draw(mdTankBtn);
    m_mainWindow->draw(mdTankCost);
    m_mainWindow->draw(recBtn);
    m_mainWindow->draw(recCost);
    m_mainWindow->draw(artBtn);
    m_mainWindow->draw(artCost);
    m_mainWindow->draw(neoTankBtn);
    m_mainWindow->draw(neoTankCost);
    m_mainWindow->draw(mgTankBtn);
    m_mainWindow->draw(mgTankCost);
    m_mainWindow->draw(mechBtn);
    m_mainWindow->draw(mechCost);
    m_mainWindow->draw(tankBtn);
    m_mainWindow->draw(tankCost);
    m_mainWindow->draw(rocketBtn);
    m_mainWindow->draw(rocketCost);

    // Display selected unit info
    m_mainWindow->draw(unitName);
    m_mainWindow->draw(unitInfo1);
    m_mainWindow->draw(unitInfo2);

    manageTurn(true);

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
	return "Other";
} // getName()

void GxENGINE::displayBar(Player *p_player)
{
    // Display black back
    sf::Sprite downBar;
    downBar.setPosition(0, m_relativeMapHeight);
    downBar.setColor(sf::Color(sf::Uint8(75), sf::Uint8(75), sf::Uint8(75), sf::Uint8(150)));    
    downBar.setTexture(m_backgroundTexture);
    downBar.setTextureRect(sf::IntRect(0, 0, m_relativeMapWidth, 75));
    m_mainWindow->draw(downBar);
    //m_miscTextures.setRepeated(false);

    // Display information about the player
    sf::Text playerName("General  " + p_player->getPlayerName(), m_font, 20);
    sf::Text playerMoney(std::to_string(p_player->getMoney()), m_font, 16);

    playerName.setPosition(5, m_relativeMapHeight + 5);
    playerMoney.setPosition(45, m_relativeMapHeight + 40);
    
    sf::Sprite mineral;
    mineral.setTexture(m_miscTextures);
    mineral.setTextureRect(sf::IntRect(0, 0, 47, 50));
    mineral.setPosition(5, m_relativeMapHeight + 35);
    mineral.setScale(0.6, 0.6);

    sf::RectangleShape separator (sf::Vector2f(2, 65));
    separator.setPosition(130, m_relativeMapHeight + 5);

    m_mainWindow->draw(mineral);
    m_mainWindow->draw(separator);
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

void GxENGINE::manageTurn(bool p_turn)
{
    // Turn info    
    if (p_turn)
    {
        sf::Text infoTurn("Your  turn  (press  t  to  end  turn)" , m_font, 16);
        infoTurn.setPosition(m_relativeMapWidth / 2 - infoTurn.getGlobalBounds().width / 2, m_relativeMapHeight + 72);
        infoTurn.setColor(sf::Color(0, 0, 0, 255));

        sf::RectangleShape turnRect(sf::Vector2f(m_relativeMapWidth, 15));
        turnRect.setFillColor(sf::Color(sf::Uint8(33), sf::Uint8(255), sf::Uint8(150), sf::Uint8(200)));
        turnRect.setPosition(0, m_relativeMapHeight + 75);

        m_mainWindow->draw(turnRect);
        m_mainWindow->draw(infoTurn);
    }
    else
    {
        sf::Text infoTurn("Not  your  turn" , m_font, 16);
        infoTurn.setPosition(m_relativeMapWidth / 2 - infoTurn.getGlobalBounds().width / 2, m_relativeMapHeight + 72);
        infoTurn.setColor(sf::Color(255, 255, 255, 255));

        sf::RectangleShape turnRect(sf::Vector2f(m_relativeMapWidth, 15));
        turnRect.setFillColor(sf::Color(sf::Uint8(255), sf::Uint8(33), sf::Uint8(33), sf::Uint8(200)));
        turnRect.setPosition(0, m_relativeMapHeight + 75);

        m_mainWindow->draw(turnRect);
        m_mainWindow->draw(infoTurn);
    }
}

void GxENGINE::notifyAttack(int p_attackStep, const pair<int, int> &p_where)
{
    p_attackStep = 72 - p_attackStep;
    int column = p_attackStep % 8;
    int line = p_attackStep / 8;
    while(line >= 9)
    {
        line = line - 9;
    }

    m_explosionSprite.setTextureRect(sf::IntRect(column * 16, line * 16, 16, 16));
    m_explosionSprite.setPosition(p_where.first * 16, p_where.second * 16);
    m_mainWindow->draw(m_explosionSprite);
} // notifyAttack()

void GxENGINE::captureFlags(const vector<pair<int, int>> &p_flags, World *p_world)
{
	for(pair<int, int> coord : p_flags)
	{
		float xPosition = coord.first * 16 - 40 / 2 + 8;
		float yPosition = coord.second * 16 - 12;

		float remainingLife = 100 - p_world->getTerrain(coord).getHp() * 5;

		//Test if overflow on left / right
		if(xPosition <= 0)
		{
			for(;xPosition <= 0;++xPosition);
		}
		else if(xPosition + 40 >= m_relativeMapWidth)
		{
			for(;xPosition + 40 >= m_relativeMapWidth; --xPosition);
		}

		// Test if overflow on top/bottom
		if(yPosition <= 0)
		{
			for(;yPosition <= 0; ++yPosition);
		}
		else if(yPosition + 10 >= m_relativeMapHeight)
		{
			for(;yPosition + 10 >= m_relativeMapHeight; --yPosition);
		}
	
        sf::RectangleShape rect(sf::Vector2f(40, 10));	
        rect.setFillColor(sf::Color(sf::Uint8(33), sf::Uint8(33), sf::Uint8(33), sf::Uint8(150)));
        rect.setPosition(xPosition, yPosition);

		sf::RectangleShape remainingRect(sf::Vector2f((36.0 / 100.0) * remainingLife, 6));
		remainingRect.setFillColor(sf::Color(sf::Uint8(0), sf::Uint8(255), sf::Uint8(100), sf::Uint8(150)));
        remainingRect.setPosition(xPosition + 2, yPosition + 2);

        m_mainWindow->draw(rect);
        m_mainWindow->draw(remainingRect);

	}
} // captureFlags()
