#ifndef DEF_GRAPHICENGINE_H
#define DEF_GRAPHICENGINE_H

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>

namespace nsGraphicEngine
{
    class GraphicEngine
    {
        public:
            
            GraphicEngine() noexcept;
            GraphicEngine(sf::RenderWindow* p_mainWindow, tmx::MapLoader *p_ml) noexcept;
            ~GraphicEngine() noexcept;

            void reload() noexcept;

            void drawMap() noexcept;

        private:

            sf::RenderWindow* m_mainWindow;    
            tmx::MapLoader* m_ml;       
    };

}


#endif
