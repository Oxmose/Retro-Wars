#include "World.h"

#define GENGINE_W nsGameEngine::World

using namespace nsGameEngine;

GENGINE_W::World(PLAYER_TYPE p_player)
{
	m_noneTerrain = Terrain(OTHER,-1,-1);
	m_player = p_player;
}

void GENGINE_W::addTerrain(Terrain p_terrain)
{
	m_terrain.push_back(p_terrain);
}

void GENGINE_W::addUnit(Unit p_unit)
{
	m_unit.push_back(p_unit);
}

std::list<Unit>& GENGINE_W::getUnits()
{
	return m_unit;
}

Terrain& GENGINE_W::getTerrain(int p_x, int p_y)
{
	bool found = false;
	for(int i = 0 ; i < m_terrain.size() ; i++)
		if(m_terrain[i].getCoord().first == p_x && m_terrain[i].getCoord().second == p_y)
			return m_terrain[i];
	return m_noneTerrain;
}

bool GENGINE_W::isVisible(int p_x, int p_y)
{
	if(getTerrain(p_x,p_y).isProperty() && getTerrain(p_x,p_y).getOwner() == m_player)
		return true;

	bool woods = false;

	for(auto unit: m_unit)
		if(unit.getOwner() == m_player)
		{
			int bonus = 0;
			if(getTerrain(unit.getCoord().first, unit.getCoord().second).getType() == WOODS)
				bonus -= 1;
			if(getTerrain(unit.getCoord().first, unit.getCoord().second).getType() == MOUNTAIN)
				bonus += 2;

			if(abs(unit.getCoord().first-p_x)+abs(unit.getCoord().second-p_y) <= unit.getVision()+bonus &&
				getTerrain(p_x,p_y).getType() != WOODS)
				return true;
			woods = woods || abs(unit.getCoord().first-p_x)+abs(unit.getCoord().second-p_y) <= 1;
		}

	if(getTerrain(p_x,p_y).getType() == WOODS)
		return woods;


	return false;

}

GENGINE_W::~World()
{
}
