#ifndef DEF_TERRAIN_H
#define DEF_TERRAIN_H

#include <iostream>
#include <fstream>
#include <cstdio>

#include <array>

#include "../Misc/Misc.h"

namespace nsGameEngine
{
	enum TerrainType
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
	};



	class Terrain
	{
		public:
			Terrain();
			Terrain(TerrainType p_type, unsigned int p_x, unsigned int p_y, PLAYER_TYPE p_owner = NEUTRAL);
			~Terrain();

			std::pair<unsigned int, unsigned int> getCoord();
			bool isProperty();
			TerrainType getType() const;
			PLAYER_TYPE getOwner() const;
			void setOwner(PLAYER_TYPE p_owner);

			std::array<int,8> getMvt();

			bool isNoneTerrain();
			int getHp();
			int getDefense();
			void setHp(int p_hp);

		private:
			TerrainType m_type;

			int m_defense;
			std::array<int,8> m_mvt;

			unsigned int m_x;
			unsigned int m_y;

			bool m_property;
			PLAYER_TYPE m_owner;
			int m_hp;
	};
}
#endif
