#ifndef DEF_WORLD_H
#define DEF_WORLD_H

// STD LIB INCLUDES
#include <vector>
#include <queue>
#include <list>
#include <algorithm>

// PACKAGE LIB INCLUDES
#include "Terrain.h"
#include "Unit.h"

namespace nsGameEngine
{
    typedef std::pair<std::pair<int, int>, std::pair<int, int>> forAcc;
    class World
    {
        public:
            // Constructor / Destructor
            World(PLAYER_TYPE p_player, int p_width, int p_height);
            ~World();

            // Terrain management
            void addTerrain(Terrain p_terrain);
            void refreshVisibleMyProperty(Terrain p_terrain, bool p_erase = false);
            Terrain& getTerrain(int p_x, int p_y);
            Terrain& getTerrain(std::pair<int, int> p_coord);            

            // Unit management
            void addUnit(Unit p_unit);
            void removeUnit(Unit p_unit);            
            void refreshVisibleUnit(Unit p_unit, int p_reinit);
            void moveUnit(Unit p_unit, std::pair<int, int> p_whereTo);
            void combatUnit(Unit p_attack, Unit p_defend);

            Unit& getUnit(int p_x, int p_y);
            Unit& getNoneUnit();
            Unit& getUnit(std::pair<int, int> p_coord);

            std::list<Unit>& getUnits();

            float getDamage(Unit p_attack, Unit p_defend, bool p_moy=false);

            // Vision manaement
            bool isVisible(int p_x, int p_y);
            bool isVisible(std::pair<int, int> p_coord);
            std::vector<std::pair<int, int>> getAccessible(Unit p_unit);
            std::vector<std::pair<int, int>> getIntermediaire(Unit p_unit, std::pair<int, int> p_whereTo);
            std::vector<std::pair<int,int>> getPortee(Unit p_unit);
            
            // Tools
            int rand_interval(int min, int max);
            int getNumberProperties();
            int getHQCount();
            bool capture(Unit p_unit, std::pair<int,int> p_toCapture);

        private:
            
            // Init members
            Terrain m_noneTerrain;
            Unit m_noneUnit;

            // World settings
            std::vector<Terrain> m_terrain;
            std::list<Unit> m_unit;
            std::vector<int> m_visible;

            // Tools
            int getI(int p_x, int p_y);
            int getI(std::pair<int, int> p_coord);
            int man(std::pair<int, int> a, std::pair<int, int> b);
            
            // Properties
            int m_width, m_height;
            PLAYER_TYPE m_player;
    }; // World
} // nsGameEngine

#endif // DEF_WORLD_H
