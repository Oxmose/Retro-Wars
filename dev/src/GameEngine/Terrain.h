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
			Terrain(TerrainType p_type, int p_x, int p_y, PLAYER_TYPE p_owner = NEUTRAL);
			~Terrain();

			std::pair<int,int> getCoord();
			bool isProperty();
			TerrainType getType();
			PLAYER_TYPE getOwner();
			void setOwner(PLAYER_TYPE p_owner);

			bool isNoneTerrain();
			int getHp();
			int getDefense();

		private:
			TerrainType m_type;

			int m_defense;
			std::array<int,8> m_mvt;

			int m_x;
			int m_y;

			bool m_property;
			PLAYER_TYPE m_owner;
			int m_hp;
	};
}
#endif
