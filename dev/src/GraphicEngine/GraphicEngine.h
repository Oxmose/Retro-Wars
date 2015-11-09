#ifndef DEF_GRAPHICENGINE_H
#define DEF_GRAPHICENGINE_H

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

            void loadTest() noexcept;
            void drawTest() noexcept;

        private:

            sf::RenderWindow* m_mainWindow;
            sf::Sprite test;
            sf::Texture test_texture;        
    };

}


#endif
