#include <string>

#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>

#include "GraphicEngine.h"
#define GxENGINE nsGraphicEngine::GraphicEngine


using namespace std;

GxENGINE::GraphicEngine() noexcept
{
}

GxENGINE::GraphicEngine(sf::RenderWindow* p_mainWindow, tmx::MapLoader *p_ml) noexcept
{
    m_mainWindow = p_mainWindow;
    m_ml = p_ml;
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
    m_mainWindow->draw(*m_ml);
}



