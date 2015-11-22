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
}

GxENGINE::~GraphicEngine() noexcept
{
}

void GxENGINE::reload() noexcept
{
    m_mainWindow->clear();
}

void GxENGINE::drawMap() noexcept
{
}



