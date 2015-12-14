#ifndef DEF_GRAPHICENGINE_H
#define DEF_GRAPHICENGINE_H

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "../MapEngine/MapEngine.h"
#include "../GameEngine/Terrain.h"
#include "../GameEngine/World.h"
#include "../GameEngine/Player.h"

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
			void refreshUserInterface(nsGameEngine::Player *p_player, nsGameEngine::World *p_world) noexcept;
            void checkProperties(nsGameEngine::World* p_world);

        private:

            sf::RenderWindow* m_mainWindow; 
            nsMapEngine::MapEngine* m_mapEngine; 

            sf::Texture m_tileset_terrain;
            sf::Texture m_tileset_property;
            sf::Texture m_tileset_unit;

            sf::IntRect terrain_gidToRect(int p_gid) noexcept;
            sf::IntRect property_gidToRect(int p_gid) noexcept;
            sf::IntRect propertyToRect(nsGameEngine::Terrain p_property);

            std::vector<sf::Sprite> m_map[4];   
    };

}


#endif
