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
    #define GRAPHIC_RES_IMG "./res/images/"

    class GraphicEngine
    {
        public:
            
            // Contructor / Destructor
            GraphicEngine();
            GraphicEngine(sf::RenderWindow* p_mainWindow, nsMapEngine::MapEngine* p_mapEngine);
            ~GraphicEngine();

            // Reload display
            void reload();

            // Draw map tiles and units
            void drawMap(nsGameEngine::World* p_world);
            void drawUnits(nsGameEngine::World* p_world);

            // Refresh user interface
            void refreshUserInterface(nsGameEngine::Player *p_player, nsGameEngine::World *p_world, bool p_turn);
            
            // Display info about base (also manage base menu) and units information (also manage unit movment display part)                 
            void displayBaseInfo(nsGameEngine::Player *p_player, const nsGameEngine::Terrain &p_terrain, const int &p_select);
            void displayUnitInfo(nsGameEngine::Player *p_player, nsGameEngine::Unit &p_unit, const std::pair<int, int> &p_mvtCursor, nsGameEngine::World* p_world, bool p_displayPorte); 

            // Display message
            void displayMessage(const std::string &p_message);
	   		void manageTurn(bool p_turn);

            // Display attack notification
            void notifyAttack(int p_attackStep, const std::pair<int, int> &p_where);

			// Display capture flags
			void captureFlags(const std::vector<std::pair<int, int>> &p_flags, nsGameEngine::World *p_world);

            void checkProperties(nsGameEngine::World* p_world);

        private:

            // Load game map
            void loadMap();

            // Load other resources
            void loadResources();

            // Util, get name of a terrain (string)
            std::string getName(nsGameEngine::TerrainType terrain);
            
            // Display GUI bar            
            void displayBar(nsGameEngine::Player *p_player);

            // Main window
            sf::RenderWindow *m_mainWindow; 
            
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

            // Other graphicResources
            sf::Texture m_explosionTexture;
            sf::Sprite  m_explosionSprite;
	        sf::Texture m_miscTextures;
            sf::Texture m_backgroundTexture;
            sf::Texture m_baseBgTexture;

            // Map dimenssions for display settings
            int m_mapWidth;
            int m_mapHeight;
            int m_relativeMapWidth;
            int m_relativeMapHeight;

            // Font used for display
            sf::Font m_font;  
    }; // GraphicEngine

} // nsGraphicEngine


#endif
