#include <SFML/Graphics.hpp>
#include "GraphicEngine.h"
#define GxENGINE nsGraphicEngine::GraphicEngine


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

void GxENGINE::loadTest() noexcept
{
    test_texture.loadFromFile("cute_image.png");
    test = sf::Sprite(test_texture);
}

void GxENGINE::drawTest() noexcept
{
   m_mainWindow->draw(test); 
}



