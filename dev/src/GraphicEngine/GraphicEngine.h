#ifndef DEF_GRAPHICENGINE_H
#define DEF_GRAPHICENGINE_H

#include <iostream>
#include <string>
#include <utility>

#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>

#include "../MapEngine/MapEngine.h"
#include "../GameEngine/Terrain.h"
#include "../GameEngine/World.h"
#include "../GameEngine/Player.h"
#include "../GameEngine/Unit.h"

namespace nsGraphicEngine
{
    class GraphicEngine
    {
        public:
            
            // Contructor / Destructor
            GraphicEngine();
            GraphicEngine(sf::RenderWindow* p_mainWindow, nsMapEngine::MapEngine* p_mapEngine);
            ~GraphicEngine();

            // Reload display
            void reload();

            // Load game map
            void loadMap();

            // Draw map tiles and units
            void drawMap(nsGameEngine::World* p_world);
            void drawUnits(nsGameEngine::World* p_world);

            // Refresh user interface
            void refreshUserInterface(nsGameEngine::Player *p_player, nsGameEngine::World *p_world, bool p_turn);
            
            // Display info about base (also manage base menu) and units information (also manage unit movment display part)                 
            void displayBaseInfo(nsGameEngine::Player *p_player, nsGameEngine::Terrain p_terrain);
            void displayUnitInfo(nsGameEngine::Player *p_player, nsGameEngine::Unit &p_unit, std::pair<int, int> &p_mvtCursor, nsGameEngine::World* p_world, bool p_displayPorte); 

            // Display message
            void displayMessage(const std::string &p_message);

            void checkProperties(nsGameEngine::World* p_world);

        private:

            // Util, get name of a terrain (string)
            std::string getName(nsGameEngine::TerrainType terrain);
            
            // Display GUI bar            
            void displayBar(sf::Font font, nsGameEngine::Player *p_player);

            // Main window
            sf::RenderWindow* m_mainWindow; 
            
            // Map engine            
            nsMapEngine::MapEngine* m_mapEngine; 
    
            // Tileset objects
            sf::Texture m_tileset_terrain;
            sf::Texture m_tileset_property;
            sf::Texture m_tileset_unit;

            // Utils function
            sf::IntRect terrain_gidToRect(int p_gid);
            sf::IntRect property_gidToRect(int p_gid);
            sf::IntRect unit_gidToRect(int p_gid);
            sf::IntRect propertyToRect(nsGameEngine::Terrain p_property);

            std::vector<sf::Sprite> m_map[4];   
    }; // GraphicEngine

} // nsGraphicEngine


#endif
