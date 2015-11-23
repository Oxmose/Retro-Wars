#include <string>

#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>

#include "GraphicEngine.h"
#define GxENGINE nsGraphicEngine::GraphicEngine


using namespace std;
using namespace nsMapEngine;

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

void GxENGINE::loadMap()
{
	cout << "hello" << endl;	

}


void GxENGINE::reload() noexcept
{
    m_mainWindow->clear();
}

void GxENGINE::drawMap() noexcept
{
}



