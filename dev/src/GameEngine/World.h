#ifndef DEF_WORLD_H
#define DEF_WORLD_H

#include <vector>
#include <queue>
#include <list>

#include "Terrain.h"
#include "Unit.h"

namespace nsGameEngine
{
	class World
	{
		public:
			World(PLAYER_TYPE p_player, int p_width, int p_height);
			~World();


			void addTerrain(Terrain p_terrain);
			Terrain& getTerrain(int p_x, int p_y);
			Terrain& getTerrain(std::pair<int,int> p_coord);

			void addUnit(Unit p_unit);
			void refreshVisibleMyProperty(Terrain p_terrain);
			void refreshVisibleUnit(Unit p_unit, int p_reinit);

			std::list<Unit>& getUnits();

			bool isVisible(int p_x, int p_y);
			bool isVisible(std::pair<int,int> p_coord);
			

		private:

			Terrain m_noneTerrain;
			std::vector<Terrain> m_terrain;
			std::list<Unit> m_unit;
			std::vector<int> m_visible;

			int getI(int p_x, int p_y);
			int getI(std::pair<int,int> p_coord);

			int man(std::pair<int,int> a, std::pair<int,int> b);

			int m_width, m_height;
			PLAYER_TYPE m_player;
	};
}

#endif