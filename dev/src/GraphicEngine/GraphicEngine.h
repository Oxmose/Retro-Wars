#ifndef DEF_GRAPHICENGINE_H
#define DEF_GRAPHICENGINE_H

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "../MapEngine/MapEngine.h"

namespace nsGraphicEngine
{
    class GraphicEngine
    {
        public:
            
            GraphicEngine() noexcept;
            GraphicEngine(sf::RenderWindow* p_mainWindow, nsMapEngine::MapEngine* p_mapEngine) noexcept;
            ~GraphicEngine() noexcept;

            void reload() noexcept;

            void loadMap() noexcept;
            void drawMap() noexcept;

        private:

            sf::RenderWindow* m_mainWindow; 
            nsMapEngine::MapEngine* m_mapEngine; 

            sf::Texture m_tileset_terrain;
            sf::Texture m_tileset_property;
            sf::Texture m_tileset_unit;     
    };

}


#endif
