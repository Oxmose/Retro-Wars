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
			World();
			~World();

		private:

			std::vector<Terrain> terrains;
			std::vector<Unit> units;
	};
}

#endif