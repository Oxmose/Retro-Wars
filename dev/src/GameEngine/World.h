#ifndef DEF_WORLD_H
#define DEF_WORLD_H

#include <vector>

#include "Terrain.h"
#include "Unit.h"

namespace nsGameEngine
{
	class World
	{
		public:
			World(PLAYER_TYPE p_player);
			~World();


			void addTerrain(Terrain p_terrain);
			Terrain& getTerrain(int p_x, int p_y);

			void addUnit(Unit p_unit);

			std::vector<Unit>& getUnits();

			bool isVisible(int p_x, int p_y);

		private:

			Terrain m_noneTerrain;
			std::vector<Terrain> m_terrain;
			std::vector<Unit> m_unit;

			PLAYER_TYPE m_player;
	};
}

#endif