#include "World.h"

#define GENGINE_W nsGameEngine::World

using namespace nsGameEngine;

GENGINE_W::World()
{
	m_noneTerrain = Terrain(OTHER,-1,-1);
}

void GENGINE_W::addTerrain(Terrain p_terrain)
{
	m_terrain.push_back(p_terrain);
}

Terrain& GENGINE_W::getTerrain(int p_x, int p_y)
{
	bool found = false;
	for(int i = 0 ; i < m_terrain.size() ; i++)
		if(m_terrain[i].getCoord().first == p_x && m_terrain[i].getCoord().second == p_y)
			return m_terrain[i];
	return m_noneTerrain;
}

GENGINE_W::~World()
{
}