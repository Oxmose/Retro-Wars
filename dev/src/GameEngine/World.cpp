#include "World.h"

#define GENGINE_W nsGameEngine::World

using namespace nsGameEngine;

GENGINE_W::World(PLAYER_TYPE p_player, int p_width, int p_height)
{
	m_noneTerrain = Terrain(OTHER,-1,-1);
	m_noneUnit = Unit(INFANTRY,-1,-1,NEUTRAL,0);
	m_player = p_player;

	m_width = p_width;
	m_height = p_height;

	for(int y = 0 ; y < m_height ; y++)
		for(int x =  0 ; x < m_width ; x++)
			m_visible.push_back(0);
}

int GENGINE_W::getI(int p_x, int p_y)
{
	return p_y*m_width+p_x%m_width;
}

int GENGINE_W::getI(std::pair<int,int> p_coord)
{
	return getI(p_coord.first, p_coord.second);
}

void GENGINE_W::refreshVisibleMyProperty(Terrain p_terrain)
{
	
	if(p_terrain.isProperty() && p_terrain.getOwner() == m_player)
		m_visible[getI(p_terrain.getCoord())] = 1;

}

int GENGINE_W::man(std::pair<int,int> a, std::pair<int,int> b)
{
	return abs(a.first-b.first)+abs(a.second-b.second);
}

//p_reinit permet de supprimer les cases vu, utilise lors des deplacements
void GENGINE_W::refreshVisibleUnit(Unit p_unit, int p_reinit = 1)
{
	if(p_unit.getOwner() != m_player)
		return;

	std::queue<std::pair<int,int>> toVisit;
	toVisit.push(p_unit.getCoord());
	

	int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
	bool vu[m_height][m_width];
	for(int i = 0 ; i < m_height ; i++)
		for(int j = 0 ; j < m_width ; j++)
			vu[i][j] = false;

	vu[p_unit.getCoord().second][p_unit.getCoord().first] = true;

	int bonus = 0;
	if(getTerrain(p_unit.getCoord().first, p_unit.getCoord().second).getType() == MOUNTAIN)
		bonus = 2;
	if(getTerrain(p_unit.getCoord().first, p_unit.getCoord().second).getType() == WOODS)
		bonus = -1;

	while(!toVisit.empty())
	{

		auto coord = toVisit.front();
		
		toVisit.pop();
		
		if(man(coord,p_unit.getCoord()) <= p_unit.getVision()+bonus)
		{

			bool unitVoit = 
				(getTerrain(coord).getType() == WOODS) ? (man(coord,p_unit.getCoord()) <= 1) : true;
			if(unitVoit)
				m_visible[getI(coord)] += p_reinit;
			for(int iDir = 0 ; iDir < 4 ; iDir++)
			{
				auto voisin = std::make_pair(coord.first+dir[iDir][0], coord.second+dir[iDir][1]);
				if(voisin.first >= 0 && voisin.first < m_width && voisin.second >= 0 && voisin.second < m_height)
					if(!vu[voisin.second][voisin.first])
					{
						vu[voisin.second][voisin.first] = true;
						toVisit.push(voisin);
					}
			}
		}
	}

}

void GENGINE_W::addTerrain(Terrain p_terrain)
{
	m_terrain.push_back(p_terrain);
	refreshVisibleMyProperty(p_terrain);
}

void GENGINE_W::addUnit(Unit p_unit)
{
	m_unit.push_back(p_unit);
	refreshVisibleUnit(p_unit);
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


Terrain& GENGINE_W::getTerrain(std::pair<int,int> p_coord)
{
	return getTerrain(p_coord.first, p_coord.second);
}

Unit GENGINE_W::getUnit(int p_x, int p_y)
{
	bool found = false;
	for(Unit unit : m_unit)
		if(unit.getCoord().first == p_x && unit.getCoord().second == p_y)
			return unit;
	return m_noneUnit;	
}

Unit GENGINE_W::getUnit(std::pair<int,int> p_coord)
{
	return getUnit(p_coord.first, p_coord.second);	
}

bool GENGINE_W::isVisible(int p_x, int p_y)
{
	return m_visible[getI(p_x,p_y)] != 0;
}

bool GENGINE_W::isVisible(std::pair<int,int> p_coord)
{
	return isVisible(p_coord.first, p_coord.second);
}

std::vector<std::pair<int,int>> GENGINE_W::getAccessible(Unit p_unit)
{
	std::vector<std::pair<int,int>> toReturn;
	
	std::queue<std::pair<int,std::pair<int,int>>> toVisit;
	toVisit.push(make_pair(p_unit.getMvt(),p_unit.getCoord()));
	

	int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
	bool vu[m_height][m_width];
	for(int i = 0 ; i < m_height ; i++)
		for(int j = 0 ; j < m_width ; j++)
			vu[i][j] = false;

	vu[p_unit.getCoord().second][p_unit.getCoord().first] = true;

	while(!toVisit.empty())
	{
		int mp = toVisit.front().first;
		auto coord = toVisit.front().second;
		toVisit.pop();
		
		if(coord.first != p_unit.getCoord().first || coord.second != p_unit.getCoord().second)
			toReturn.push_back(coord);
		
		if(mp > 0)
		{
			for(int iDir = 0 ; iDir < 4 ; iDir++)
			{
				auto voisin = std::make_pair(coord.first+dir[iDir][0], coord.second+dir[iDir][1]);
				if(voisin.first >= 0 && voisin.first < m_width && voisin.second >= 0 && voisin.second < m_height)
					if(!vu[voisin.second][voisin.first] && getTerrain(voisin).getMvt()[p_unit.getMvtType()] != 0)
					{
						vu[voisin.second][voisin.first] = true;
						toVisit.push(make_pair(mp-getTerrain(voisin).getMvt()[p_unit.getMvtType()],voisin));
					}
			}
		}

	}
	
	return toReturn;
}

std::vector<std::pair<int,int>> GENGINE_W::getPortee(Unit p_unit)
{
	std::vector<std::pair<int,int>> toReturn;
	
	std::queue<std::pair<int,int>> toVisit;
	toVisit.push(p_unit.getCoord());

	int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
	bool vu[m_height][m_width];
	for(int i = 0 ; i < m_height ; i++)
		for(int j = 0 ; j < m_width ; j++)
			vu[i][j] = false;

	vu[p_unit.getCoord().second][p_unit.getCoord().first] = true;


	while(!toVisit.empty())
	{

		auto coord = toVisit.front();
		
		toVisit.pop();
		
		if(man(coord,p_unit.getCoord()) <= p_unit.getRange())
		{
			if(!getUnit(coord).isNoneUnit() && getUnit(coord).getOwner() != m_player && isVisible(coord))
				toReturn.push_back(coord);
			for(int iDir = 0 ; iDir < 4 ; iDir++)
			{
				auto voisin = std::make_pair(coord.first+dir[iDir][0], coord.second+dir[iDir][1]);
				if(voisin.first >= 0 && voisin.first < m_width && voisin.second >= 0 && voisin.second < m_height)
					if(!vu[voisin.second][voisin.first])
					{
						vu[voisin.second][voisin.first] = true;
						toVisit.push(voisin);
					}
			}
		}
	}


	return toReturn;
}


GENGINE_W::~World()
{
}
