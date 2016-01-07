#ifndef DEF_TERRAIN_H
#define DEF_TERRAIN_H

// STD LIB INCLUDES
#include <fstream>
#include <cstdio>
#include <array>

// OTHER INCLUDES FROM PROJECT
#include "../Misc/Misc.h"

namespace nsGameEngine
{
    enum TERRAINTYPE
    {
        PLAIN = 0,
        MOUNTAIN,
        WOODS,
        ROADS,
        BRIDGES,
        CITY,
        HQ,
        BASE,
        OTHER
    }; // TERRAINTYPE

    class Terrain
    {
        public:
            // Constructors / Destructors
            Terrain();
            Terrain(TERRAINTYPE p_type, int p_x, int p_y, PLAYER_TYPE p_owner = NEUTRAL);
            ~Terrain();

            // Getters
            std::array<int,8> getMvt();
            std::pair<int, int> getCoord();
            bool isProperty();
            TERRAINTYPE getType() const;
            PLAYER_TYPE getOwner() const;
            bool isNoneTerrain();
            int  getHp();
            int  getDefense();

            // Setters
            void setOwner(PLAYER_TYPE p_owner);
            void setHp(int p_hp);
            void resetHp();

        private:
            // Terrain Properties
            TERRAINTYPE m_type;
            PLAYER_TYPE m_owner;
            
            // Terrain settings
            std::array<int,8> m_mvt;
            int m_x;
            int m_y;
            int m_defense;
            bool m_property;
            int m_hp;
    }; // Terrain
} // nsGameEngine
#endif // DEF_TERRAIN_H
