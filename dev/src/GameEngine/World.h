#ifndef DEF_WORLD_H
#define DEF_WORLD_H

#include <vector>
#include <queue>
#include <list>
#include <algorithm>
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
			Terrain& getTerrain(unsigned int p_x, unsigned int p_y);
			Terrain& getTerrain(std::pair<unsigned int, unsigned int> p_coord);

			void addUnit(Unit p_unit);
			void removeUnit(Unit p_unit);
			void refreshVisibleMyProperty(Terrain p_terrain);
			void refreshVisibleUnit(Unit p_unit, int p_reinit);
			Unit& getUnit(unsigned int p_x, unsigned int p_y);
			Unit& getUnit(std::pair<unsigned int, unsigned int> p_coord);

			std::list<Unit>& getUnits();

			bool isVisible(unsigned int p_x, unsigned int p_y);
			bool isVisible(std::pair<unsigned int, unsigned int> p_coord);

			std::vector<std::pair<unsigned int, unsigned int>> getAccessible(Unit p_unit);
			std::vector<std::pair<unsigned int, unsigned int>> getIntermediaire(Unit p_unit, std::pair<unsigned int, unsigned int> p_whereTo);
			std::vector<std::pair<unsigned int,unsigned int>> getPortee(Unit p_unit);



			void moveUnit(Unit p_unit, std::pair<unsigned int, unsigned int> p_whereTo);
			void combatUnit(Unit p_attack, Unit p_defend);
			float getDamage(Unit p_attack, Unit p_defend, bool p_moy=false);
			unsigned int rand_interval(unsigned int min, unsigned int max);


		private:

			Terrain m_noneTerrain;
			Unit m_noneUnit;
			std::vector<Terrain> m_terrain;
			std::list<Unit> m_unit;
			std::vector<int> m_visible;

			int getI(unsigned int p_x, unsigned int p_y);
			int getI(std::pair<unsigned int, unsigned int> p_coord);

			int man(std::pair<unsigned int, unsigned int> a, std::pair<unsigned int, unsigned int> b);

			unsigned int m_width, m_height;
			PLAYER_TYPE m_player;
	};
}

#endif
