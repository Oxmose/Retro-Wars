#ifndef DEF_GRAPHICENGINE_H
#define DEF_GRAPHICENGINE_H

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

namespace nsGraphicEngine
{
    class GraphicEngine
    {
        public:
            
            GraphicEngine() noexcept;
            GraphicEngine(sf::RenderWindow* p_mainWindow) noexcept;
            ~GraphicEngine() noexcept;

            void reload() noexcept;

            void drawMap() noexcept;

        private:

            sf::RenderWindow* m_mainWindow;        
    };

}


#endif
