#include "World.h"

#define GENGINE_W nsGameEngine::World

using namespace nsGameEngine;

GENGINE_W::World(PLAYER_TYPE p_player, int p_width, int p_height)
{
	m_noneTerrain = Terrain(OTHER,-1,-1);
	m_noneUnit = Unit(INFANTRY,-1,-1,NEUTRAL,0);
	m_noneUnit.setHp(-1);
	m_player = p_player;

	m_width = p_width;
	m_height = p_height;

	for(int y = 0 ; y < m_height ; y++)
		for(int x =  0 ; x < m_width ; x++)
			m_visible.push_back(0);

	srand(time(NULL));
}

int GENGINE_W::getI(int p_x, int p_y)
{
	return p_y*m_width+p_x%m_width;
}

int GENGINE_W::getI(std::pair<int, int> p_coord)
{
	return getI(p_coord.first, p_coord.second);
}

void GENGINE_W::refreshVisibleMyProperty(Terrain p_terrain)
{
	
	if(p_terrain.isProperty() && p_terrain.getOwner() == m_player)
		m_visible[getI(p_terrain.getCoord())] = 1;

}

int GENGINE_W::man(std::pair<int, int> a, std::pair<int, int> b)
{
	return abs(a.first-b.first)+abs(a.second-b.second);
}

//Unit dans bois voit pas à cote
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
				std::pair<int, int> voisin = std::make_pair(coord.first+dir[iDir][0], coord.second+dir[iDir][1]);
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

void GENGINE_W::removeUnit(Unit p_unit)
{

	if(p_unit.getOwner() == m_player)
		refreshVisibleUnit(p_unit,-1);
	m_unit.remove(p_unit);
}

std::list<Unit>& GENGINE_W::getUnits()
{
	return m_unit;
}

Terrain& GENGINE_W::getTerrain(int p_x, int p_y)
{
	for(int i = 0 ; i < m_terrain.size() ; i++)
		if(m_terrain[i].getCoord().first == p_x && m_terrain[i].getCoord().second == p_y)
			return m_terrain[i];
	return m_noneTerrain;
}


Terrain& GENGINE_W::getTerrain(std::pair<int, int> p_coord)
{
	return getTerrain(p_coord.first, p_coord.second);
}

Unit& GENGINE_W::getUnit(int p_x, int p_y)
{
	for(Unit& unit : m_unit)
		if(unit.getCoord().first == p_x && unit.getCoord().second == p_y)
			return unit;
	return m_noneUnit;	
}

Unit& GENGINE_W::getUnit(std::pair<int, int> p_coord)
{
	return getUnit(p_coord.first, p_coord.second);	
}

bool GENGINE_W::isVisible(int p_x, int p_y)
{
	return m_visible[getI(p_x,p_y)] != 0;
}

bool GENGINE_W::isVisible(std::pair<int, int> p_coord)
{
	return isVisible(p_coord.first, p_coord.second);
}

typedef std::pair<std::pair<int, int>, std::pair<int, int>> forAcc;

static bool comp(const forAcc& A, const forAcc& B)
{
	return A.first.first > B.first.first;
}

//TODO : bizarre que rocket puisse pas aller au dessus factory
std::vector<std::pair<int, int>> GENGINE_W::getAccessible(Unit p_unit)
{
	std::vector<std::pair<int, int>> toReturn;
	
	std::priority_queue<forAcc,std::vector<forAcc>,decltype(&comp)> toVisit(&comp); //dist,mp,coord
	toVisit.push(std::make_pair(std::make_pair(0,p_unit.getMvt()),p_unit.getCoord()));
	

	int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
	bool vu[m_height][m_width];
	for(int i = 0 ; i < m_height ; i++)
		for(int j = 0 ; j < m_width ; j++)
			vu[i][j] = false;

	vu[p_unit.getCoord().second][p_unit.getCoord().first] = true;


	while(!toVisit.empty())
	{	
		int mp = toVisit.top().first.second;
		auto coord = toVisit.top().second;
		toVisit.pop();
		if(getUnit(coord).isNoneUnit() && (coord.first != p_unit.getCoord().first || coord.second != p_unit.getCoord().second) && mp >= 0)
			toReturn.push_back(coord);
		
		if(mp > 0)
		{
			for(int iDir = 0 ; iDir < 4 ; iDir++)
			{
				std::pair<int, int> voisin = std::make_pair(coord.first+dir[iDir][0], coord.second+dir[iDir][1]);
				if(voisin.first >= 0 && voisin.first < m_width && voisin.second >= 0 && voisin.second < m_height)
					if(!vu[voisin.second][voisin.first] && getTerrain(voisin).getMvt()[p_unit.getMvtType()] != 0)
					{
						vu[voisin.second][voisin.first] = true;
						toVisit.push(std::make_pair(std::make_pair(getTerrain(voisin).getMvt()[p_unit.getMvtType()],mp-getTerrain(voisin).getMvt()[p_unit.getMvtType()]),voisin));
					}
			}
		}

	}

	return toReturn;
}

std::vector<std::pair<int, int>> GENGINE_W::getIntermediaire(Unit p_unit, std::pair<int, int> p_whereTo)
{
	std::vector<std::pair<int, int>> toReturn;
	
	std::priority_queue<forAcc,std::vector<forAcc>,decltype(&comp)> toVisit(&comp); //dist,mp,coord
	toVisit.push(std::make_pair(std::make_pair(0,p_unit.getMvt()),p_unit.getCoord()));
	

	int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
	bool vu[m_height][m_width];
	int tdist[m_height][m_width];
	const int INFINI = 1000*1000*1000;
	for(int i = 0 ; i < m_height ; i++)
		for(int j = 0 ; j < m_width ; j++)
		{
			vu[i][j] = false;
			tdist[i][j] = INFINI;
		}

	vu[p_unit.getCoord().second][p_unit.getCoord().first] = true;
	tdist[p_unit.getCoord().second][p_unit.getCoord().first] = 0;


	while(!toVisit.empty())
	{
		int mp = toVisit.top().first.second;
		auto coord = toVisit.top().second;
		
		toVisit.pop();
		
		if(mp > 0)
		{
			for(int iDir = 0 ; iDir < 4 ; iDir++)
			{
				auto voisin = std::make_pair(coord.first+dir[iDir][0], coord.second+dir[iDir][1]);
				if(voisin.first >= 0 && voisin.first < m_width && voisin.second >= 0 && voisin.second < m_height)
					if(!vu[voisin.second][voisin.first] && getTerrain(voisin).getMvt()[p_unit.getMvtType()] != 0)
					{
						vu[voisin.second][voisin.first] = true;
						tdist[voisin.second][voisin.first] = tdist[coord.second][coord.first]+getTerrain(voisin).getMvt()[p_unit.getMvtType()];
						toVisit.push(std::make_pair(std::make_pair(getTerrain(voisin).getMvt()[p_unit.getMvtType()],mp-getTerrain(voisin).getMvt()[p_unit.getMvtType()]),voisin));
					}
			}
		}

	}

	auto coord = p_whereTo;

	while(coord != p_unit.getCoord())
	{
		toReturn.push_back(coord);
		int minDist = INFINI;
		auto minVoisin = coord;
		for(int iDir = 0 ; iDir < 4 ; iDir++)
		{
			auto voisin = std::make_pair(coord.first+dir[iDir][0], coord.second+dir[iDir][1]);
			if(voisin.first >= 0 && voisin.first < m_width && voisin.second >= 0 && voisin.second < m_height)
				if(tdist[voisin.second][voisin.first] < minDist)
				{
					minDist = tdist[voisin.second][voisin.first];
					minVoisin = voisin;
				}
		}

		coord = minVoisin;
	}

	std::reverse(toReturn.begin(), toReturn.end());
	return toReturn;
}

std::vector<std::pair<int, int>> GENGINE_W::getPortee(Unit p_unit)
{
	std::vector<std::pair<int, int>> toReturn;
	
	std::queue<std::pair<int, int>> toVisit;
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


int GENGINE_W::rand_interval(int min, int max)
{
    int r;
    const int range = 1 + max - min;
    const int buckets = RAND_MAX / range;
    const int limit = buckets * range;

    /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}


void GENGINE_W::moveUnit(Unit p_unit, std::pair<int, int> p_whereTo)
{

	refreshVisibleUnit(p_unit,-1);
	getUnit(p_unit.getCoord()).setCoord(p_whereTo.first,p_whereTo.second);
	p_unit.setCoord(p_whereTo.first, p_whereTo.second);
	refreshVisibleUnit(p_unit);

}


bool GENGINE_W::capture(Unit p_unit, std::pair<int,int> p_toCapture)
{
	int currHp = getTerrain(p_toCapture).getHp();
	getTerrain(p_toCapture).setHp(std::max(currHp-p_unit.getHp(),0));

	if(getTerrain(p_toCapture).getHp() == 0)
	{
		getTerrain(p_toCapture).setOwner(m_player);
		return true;
	}

	return false;
}

float GENGINE_W::getDamage(Unit p_attack, Unit p_defend, bool p_moy)
{
	float B = float(p_attack.getBaseDamage(p_defend));
	float ACO = 1.0;
	float R = float(rand_interval(0,9));
	if(p_moy)
		R = float(5.0);
	float AHP = float(p_attack.getHp());
	float DCO = 1.0;
	float DTR = float(getTerrain(p_defend.getCoord()).getDefense());
	float DHP = p_defend.getHp();
	return  std::min(std::max((B*ACO/DCO)*(AHP/10)-R*((200-(DCO+DTR*DHP))/100),float(0)),float(100));
}

void GENGINE_W::combatUnit(Unit p_attack, Unit p_defend)
{
	float damage1 = getDamage(p_attack, p_defend)/100;
	int newHealth1 = p_defend.getHp()-int(damage1*p_defend.getHp())-((damage1 > 0.05) ? 1 : 0);
	p_defend.setHp(newHealth1);
	getUnit(p_defend.getCoord()).setHp(newHealth1);

	if(newHealth1 == 0)
		removeUnit(p_defend);
	else
	{
		if(man(p_attack.getCoord(),p_defend.getCoord()) <= p_defend.getRange())
		{
			float damage2 = getDamage(p_defend, p_attack)/100;
			int newHealth2 = p_attack.getHp()-int(damage2*p_attack.getHp())-((damage2 > 0.05) ? 1 : 0);
			p_attack.setHp(newHealth2);
			getUnit(p_attack.getCoord()).setHp(newHealth2);
			if(newHealth2 == 0)
				removeUnit(p_attack);
		}
	}

}

int GENGINE_W::getNumberProperties()
{
	int toReturn = 0;
	for(auto ter : m_terrain)
		if(ter.isProperty() && ter.getOwner() == m_player)
			toReturn ++;
	return toReturn;
}

Unit& GENGINE_W::getNoneUnit()
{
	return m_noneUnit;	
}

int GENGINE_W::getHQCount()
{
	int toReturn = 0;
	for(auto ter : m_terrain)
		if(ter.isProperty() && ter.getOwner() == m_player && ter.getType() == HQ)
			toReturn ++;
	return toReturn;
}

GENGINE_W::~World()
{
}
