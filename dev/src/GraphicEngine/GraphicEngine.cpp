#include <string>

#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>

#include "GraphicEngine.h"
#define GxENGINE nsGraphicEngine::GraphicEngine


using namespace std;
using namespace nsMapEngine;
using namespace nsGameEngine;

GxENGINE::GraphicEngine() noexcept
{
}

GxENGINE::GraphicEngine(sf::RenderWindow* p_mainWindow, nsMapEngine::MapEngine* p_mapEngine) noexcept
{
    m_mainWindow = p_mainWindow;
    m_mapEngine = p_mapEngine;

    loadMap();
}

GxENGINE::~GraphicEngine() noexcept
{
}

sf::IntRect GxENGINE::property_gidToRect(int p_gid) noexcept
{
	return sf::IntRect(((p_gid-145)%7)*16,((p_gid-145)/7)*16,16,16);
}

sf::IntRect GxENGINE::terrain_gidToRect(int p_gid) noexcept
{
	return sf::IntRect(((p_gid-1)%18)*16,((p_gid-1)/18)*16,16,16);
}

sf::IntRect GxENGINE::unit_gidToRect(int p_gid) noexcept
{
	return sf::IntRect(((p_gid-229)%13)*16,((p_gid-229)/13)*16,16,16);
}

sf::IntRect GxENGINE::propertyToRect(Terrain p_property)
{
	int gid = 0;
	if(p_property.getType() == HQ)
	{
		switch(p_property.getOwner())
		{
			case RED:
				gid = 145+7;
				break;
			case BLUE:
				gid = 145+21;
				break;
			case GREEN:
				gid = 145+35;
				break;
			case YELLOW:
				gid = 145+49;
				break;
			case BLACK:
				gid = 145+63;
				break;
		}
	}

	if(p_property.getType() == CITY)
	{
		switch(p_property.getOwner())
		{
			case RED:
				gid = 145+8;
				break;
			case BLUE:
				gid = 145+22;
				break;
			case GREEN:
				gid = 145+36;
				break;
			case YELLOW:
				gid = 145+50;
				break;
			case BLACK:
				gid = 145+64;
				break;
			case NEUTRAL:
				gid = 145+78;
				break;
		}
	}

	if(p_property.getType() == BASE)
	{
		switch(p_property.getOwner())
		{
			case RED:
				gid = 145+9;
				break;
			case BLUE:
				gid = 145+23;
				break;
			case GREEN:
				gid = 145+37;
				break;
			case YELLOW:
				gid = 145+51;
				break;
			case BLACK:
				gid = 145+65;
				break;
			case NEUTRAL:
				gid = 145+79;
				break;
		}
	}

	return property_gidToRect(gid);
}

void GxENGINE::checkProperties(World* p_world)
{
	for(sf::Sprite &spt : m_map[2])
	{
		int x = spt.getPosition().x/16;
		int y = spt.getPosition().y/16;
		Terrain prop = p_world->getTerrain(x,y);

		if(prop.isProperty())
			spt.setTextureRect(propertyToRect(prop));
	}
}

void GxENGINE::loadMap() noexcept
{
	sf::Image image_tileset_terrain;//For transparency settings, sf:Image needed
	image_tileset_terrain.loadFromFile("maps/tilesets/terrain.bmp");
	image_tileset_terrain.createMaskFromColor(sf::Color(0,0,0));
	m_tileset_terrain.loadFromImage(image_tileset_terrain);

	sf::Image image_tileset_property;
	image_tileset_property.loadFromFile("maps/tilesets/property.bmp");
	image_tileset_property.createMaskFromColor(sf::Color(0,0,0));
	m_tileset_property.loadFromImage(image_tileset_property);
	

	sf::Image image_tileset_unit;
	image_tileset_unit.loadFromFile("maps/tilesets/unit.bmp");
	image_tileset_unit.createMaskFromColor(sf::Color(0,0,0));
	m_tileset_unit.loadFromImage(image_tileset_unit);
	
	printf("%d %d\n", m_mapEngine->getWidth(), m_mapEngine->getHeight());
	printf("%d %d\n", m_mapEngine->getLayerTiles(0).size(), 30*20);
	for(int iLayerTerrain = 0 ; iLayerTerrain < 4 ; iLayerTerrain++)
	{
		sf::Vector2f curr_position(0,0);
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
			if(curr_position.x >= m_mapEngine->getWidth()*16)
			{
				curr_position.x = 0;
				curr_position.y += 16;
			}
		}
	}
}


void GxENGINE::reload() noexcept
{
    m_mainWindow->clear();
}

void GxENGINE::drawMap(nsGameEngine::World* p_world) noexcept
{
	for(int iLayer = 0 ; iLayer < 4 ; iLayer++)
		for(sf::Sprite spt : m_map[iLayer])
			m_mainWindow->draw(spt);

	for(int x = 0 ; x < m_mapEngine->getWidth() ; x++)
		for(int y = 0 ; y < m_mapEngine->getHeight() ; y++)
		{
			if(!p_world->isVisible(x,y))
			{
				sf::RectangleShape rectangle(sf::Vector2f(16, 16));
				rectangle.setPosition(sf::Vector2f(x*16,y*16));
				rectangle.setFillColor(sf::Color(0,0,0,100));
				m_mainWindow->draw(rectangle);
			}
		}
}

void GxENGINE::drawUnits(nsGameEngine::World* p_world) noexcept
{
	for(auto unit: p_world->getUnits())
	{
		if(p_world->isVisible(unit.getCoord().first,unit.getCoord().second))
		{
			sf::Sprite spt;
			spt.setTexture(m_tileset_unit);
			spt.setTextureRect(unit_gidToRect(unit.getGid()));
			spt.setPosition(unit.getCoord().first*16,unit.getCoord().second*16);
			m_mainWindow->draw(spt);
		}
	}
}

void GxENGINE::refreshUserInterface(Player *p_player, World *p_world, bool p_turn) noexcept
{
	sf::Font font;
	if (!font.loadFromFile("./res/font.ttf"))
	{
		cerr << "Can't load display font!" << endl;
	}	

	displayBar(font, p_player);
    
    sf::RectangleShape cursor(sf::Vector2f(16, 16));
	cursor.setFillColor(sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(255), sf::Uint8(150)));
	cursor.setPosition(p_player->getCoord().first * 16, p_player->getCoord().second * 16);
	m_mainWindow->draw(cursor);

    // Get unit
    Unit unit = p_world->getUnit(p_player->getCoord().first, p_player->getCoord().second);
    if (unit.getOwner() != NEUTRAL)
    {
        sf::Text unitName(unit.getName(), font, 20);
        unitName.setPosition(140, m_mapEngine->getHeight() * 16 + 5);
        

        sf::Text unitOwner("Owner : " + getPlayerName(unit.getOwner()), font, 15);
        unitOwner.setPosition(140, m_mapEngine->getHeight() * 16 + 30);
        
        sf::Text info("Health : " + to_string(unit.getHp()), font, 15);
        info.setPosition(250, m_mapEngine->getHeight() * 16 + 10);

        if (unit.getOwner() == p_player->getType())
        {
            string ammo;
            if (unit.getAmmo() == -1)
                ammo = "Infinite";
            else
                ammo = to_string(unit.getAmmo());

            sf::Text ammoInfo("Ammo : " + ammo, font, 15);
            ammoInfo.setPosition(250, m_mapEngine->getHeight() * 16 + 30);
            m_mainWindow->draw(ammoInfo);
            
            if (unit.getType() != INFANTRY)
            {
                sf::Text fuelInfo("Fuel : " + to_string(unit.getFuel()), font, 15);
                fuelInfo.setPosition(250, m_mapEngine->getHeight() * 16 + 50);
                m_mainWindow->draw(fuelInfo);
            }
            
            sf::Text help("Press  enter  to  select", font, 15);
            help.setPosition(330, m_mapEngine->getHeight() * 16 + 50);
            m_mainWindow->draw(help);
        }

        m_mainWindow->draw(unitName);
        m_mainWindow->draw(unitOwner);
        m_mainWindow->draw(info);
    }
    else
    {
	    Terrain ter = p_world->getTerrain(p_player->getCoord().first, p_player->getCoord().second);
        TerrainType terType = ter.getType();
	    sf::Text terrainName(getName(terType), font, 20);
	    terrainName.setPosition(140, m_mapEngine->getHeight() * 16 + 5);
        sf::Text terrainOwner("Owner : " + getPlayerName(ter.getOwner()), font, 15);
        terrainOwner.setPosition(140, m_mapEngine->getHeight() * 16 + 30);
        
        sf::Text info("Health : " + to_string(ter.getHp()) + "\nDefense : " + to_string(ter.getDefense()), font, 15);
        info.setPosition(250, m_mapEngine->getHeight() * 16 + 10);

        if (terType == BASE)
        {
            info.setString(info.getString() + "\nPress  enter  to  use  the  " + getName(ter.getType()));
        }

	    m_mainWindow->draw(terrainName);
        m_mainWindow->draw(terrainOwner);
        if (ter.getOwner() == p_player->getType())
            m_mainWindow->draw(info);
    }

    // Turn info
    
    if (!p_turn)
    {
        sf::Text infoTurn("Not your turn" , font, 15);
        infoTurn.setPosition(m_mapEngine->getWidth() * 16 / 2 - infoTurn.getGlobalBounds().width / 2, 2);
        sf::RectangleShape turnRect(sf::Vector2f(100, 30));
	    turnRect.setFillColor(sf::Color(sf::Uint8(33), sf::Uint8(33), sf::Uint8(33), sf::Uint8(100)));
	    turnRect.setPosition(m_mapEngine->getWidth() * 16 / 2 - 50, 0);
        m_mainWindow->draw(turnRect);
        m_mainWindow->draw(infoTurn);
    }
    

    
}

void GxENGINE::displayUnitInfo(Player *p_player, Unit &p_unit, pair<int, int> &p_mvtCursor)
{
    sf::RectangleShape downBar(sf::Vector2f(m_mapEngine->getWidth() * 16, 75));
	downBar.setPosition(0, m_mapEngine->getHeight() * 16);
	downBar.setFillColor(sf::Color(sf::Uint8(75), sf::Uint8(75), sf::Uint8(75), sf::Uint8(150)));
	m_mainWindow->draw(downBar);

    sf::Font font;
	if (!font.loadFromFile("./res/font.ttf"))
	{
		cerr << "Can't load display font!" << endl;
	}	

	sf::Text unitName("Selected : " + p_unit.getName(), font, 20);
	unitName.setPosition(5, m_mapEngine->getHeight() * 16 + 5);	
	m_mainWindow->draw(unitName);

	
    
    sf::RectangleShape cursor(sf::Vector2f(16, 16));
	cursor.setFillColor(sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(255), sf::Uint8(150)));
	cursor.setPosition(p_player->getCoord().first * 16, p_player->getCoord().second * 16);
	m_mainWindow->draw(cursor);

    // Display possible movments
    sf::RectangleShape possibleMov(sf::Vector2f(16, 16));
    possibleMov.setFillColor(sf::Color(sf::Uint8(0), sf::Uint8(255), sf::Uint8(150), sf::Uint8(100)));
    
    possibleMov.setPosition((p_player->getCoord().first + 1) * 16, p_player->getCoord().second * 16);
	m_mainWindow->draw(possibleMov);

    possibleMov.setPosition((p_player->getCoord().first + 1) * 16, (p_player->getCoord().second + 1) * 16);
	m_mainWindow->draw(possibleMov);

    possibleMov.setPosition(p_player->getCoord().first * 16, (p_player->getCoord().second + 1) * 16);
	m_mainWindow->draw(possibleMov);
    
    possibleMov.setPosition((p_player->getCoord().first + 1) * 16, (p_player->getCoord().second - 1) * 16);
	m_mainWindow->draw(possibleMov);

    possibleMov.setPosition((p_player->getCoord().first - 1) * 16, p_player->getCoord().second * 16);
	m_mainWindow->draw(possibleMov);

    possibleMov.setPosition((p_player->getCoord().first - 1) * 16, (p_player->getCoord().second - 1) * 16);
	m_mainWindow->draw(possibleMov);

    possibleMov.setPosition(p_player->getCoord().first * 16, (p_player->getCoord().second - 1) * 16);
	m_mainWindow->draw(possibleMov);
    
    possibleMov.setPosition((p_player->getCoord().first - 1) * 16, (p_player->getCoord().second + 1) * 16);
	m_mainWindow->draw(possibleMov);
    

    // Movment cursor management
    sf::RectangleShape mvtCursor(sf::Vector2f(16, 16));
	mvtCursor.setFillColor(sf::Color(sf::Uint8(50), sf::Uint8(150), sf::Uint8(255), sf::Uint8(150)));
	mvtCursor.setPosition(p_mvtCursor.first * 16, p_mvtCursor.second * 16);
	m_mainWindow->draw(mvtCursor);

    sf::Text info("Health : " + to_string(p_unit.getHp()), font, 15);
    info.setPosition(250, m_mapEngine->getHeight() * 16 + 10);
    string ammo;
    if (p_unit.getAmmo() == -1)
        ammo = "Infinite";
    else
        ammo = to_string(p_unit.getAmmo());

    sf::Text ammoInfo("Ammo : " + ammo, font, 15);
    ammoInfo.setPosition(250, m_mapEngine->getHeight() * 16 + 30);
    m_mainWindow->draw(ammoInfo);
    
    if (p_unit.getType() != INFANTRY)
    {
        sf::Text fuelInfo("Fuel : " + to_string(p_unit.getFuel()), font, 15);
        fuelInfo.setPosition(250, m_mapEngine->getHeight() * 16 + 50);
        m_mainWindow->draw(fuelInfo);
    }
    m_mainWindow->draw(info);
}

void GxENGINE::displayBaseInfo(nsGameEngine::Player *p_player, nsGameEngine::Terrain p_terrain) noexcept
{
    sf::RectangleShape back(sf::Vector2f(m_mapEngine->getWidth() * 16, m_mapEngine->getHeight() * 16));
	back.setFillColor(sf::Color(sf::Uint8(225), sf::Uint8(225), sf::Uint8(225), sf::Uint8(200)));
	back.setPosition(0, 0);
    m_mainWindow->draw(back);

    sf::Font font;
	if (!font.loadFromFile("./res/font.ttf"))
	{
		cerr << "Can't load display font!" << endl;
	}

    displayBar(font, p_player);
    sf::Text quit("Press  escape  to  quit" , font, 15);
    quit.setPosition(140, m_mapEngine->getHeight() * 16 + 50);

	m_mainWindow->draw(quit);

    sf::Text title("Base", font, 25);
    title.setPosition(m_mapEngine->getWidth() * 16 / 2 - title.getGlobalBounds().width / 2, 2);

    sf::RectangleShape titleRect(sf::Vector2f(200, 40));
	titleRect.setFillColor(sf::Color(sf::Uint8(100), sf::Uint8(100), sf::Uint8(100), sf::Uint8(255)));
	titleRect.setPosition(m_mapEngine->getWidth() * 16 / 2 - 100, 0);
    m_mainWindow->draw(titleRect);
    m_mainWindow->draw(title);

    sf::Text info("This  is  your  base", font, 16);
    info.setPosition(5, 50);
    info.setColor(sf::Color(0, 0, 0, 255));
    m_mainWindow->draw(info);
}


string GxENGINE::getName(TerrainType terrain) noexcept
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
}

void GxENGINE::displayBar(sf::Font font, Player *p_player)
{
    sf::RectangleShape downBar(sf::Vector2f(m_mapEngine->getWidth() * 16, 75));
	downBar.setPosition(0, m_mapEngine->getHeight() * 16);
	downBar.setFillColor(sf::Color(sf::Uint8(75), sf::Uint8(75), sf::Uint8(75), sf::Uint8(150)));
	m_mainWindow->draw(downBar);

	sf::Text playerName("General " + p_player->getPlayerName(), font, 20);
	sf::Text playerMoney("Resources : " + std::to_string(p_player->getMoney()) + "$", font, 16);

	playerName.setPosition(5, m_mapEngine->getHeight() * 16 + 5);
	playerMoney.setPosition(5, m_mapEngine->getHeight() * 16 + 30);
	m_mainWindow->draw(playerName);
	m_mainWindow->draw(playerMoney);
}
