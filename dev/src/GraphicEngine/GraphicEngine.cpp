#include <string>

#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>

#include "GraphicEngine.h"
#define GxENGINE nsGraphicEngine::GraphicEngine


using namespace std;

GxENGINE::GraphicEngine() noexcept
{
}

GxENGINE::GraphicEngine(sf::RenderWindow* p_mainWindow) noexcept
{
    m_mainWindow = p_mainWindow;
    m_ml = new tmx::MapLoader("../res/maps/");
    m_ml->AddSearchPath("../res/maps/tilesets");
}

GxENGINE::~GraphicEngine() noexcept
{
	delete m_ml;
}

void GxENGINE::reload() noexcept
{
    m_mainWindow->clear();
}

void GxENGINE::loadMap(string mapName) noexcept
{
   	m_ml->Load(mapName);
}

void GxENGINE::drawMap() noexcept
{
    m_mainWindow->draw(*m_ml);
}



