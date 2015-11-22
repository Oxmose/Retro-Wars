#ifndef DEF_TERRAIN_H
#define DEF_TERRAIN_H

#include <iostream>
#include <fstream>
#include <cstdio>

#include <array>

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
			Terrain(TerrainType p_type, int p_x, int p_y, int p_owner = 0);
			~Terrain();

		private:
			TerrainType m_type;

			int m_defense;
			std::array<int,8> m_mvt;

			int m_x;
			int m_y;

			bool m_property;
			int m_owner;
			int m_hp;
	};
}
#endif