// STD LIB INCLUDES
#include <fstream>
#include <cstdio>
#include <array>

// OTHER INCLUDES FROM PROJECT
#include "../Misc/Misc.h"

// HEADER FILE INCLUDE
#include "Terrain.h"

#define GENGINE_TER nsGameEngine::Terrain 

using namespace std;
using namespace nsGameEngine;

GENGINE_TER::Terrain()
{
} // Terrain()

GENGINE_TER::Terrain(TERRAINTYPE p_type, int p_x, int p_y, PLAYER_TYPE p_owner)
{
	m_type = p_type;

	m_x = p_x;
	m_y = p_y;

	m_mvt[0] = 0;//foot
	m_mvt[1] = 0;//boots
	m_mvt[2] = 0;//treads
	m_mvt[3] = 0;//tires
	m_mvt[4] = 0;//air
	m_mvt[5] = 0;//sea
	m_mvt[6] = 0;//lander
	m_mvt[7] = 0;//pipe

	m_property = false;
	m_defense = 0;
	m_owner = p_owner;
	m_hp = 0;

	if(p_type == PLAIN)
	{
		m_property = false;
		m_defense = 1;

		m_mvt = {1,1,1,2,1,0,0,0};
	}

	if(p_type == MOUNTAIN)
	{
		m_property = false;
		m_defense = 4;

		m_mvt = {2,1,0,0,1,0,0,0};
	}

	if(p_type == WOODS)
	{
		m_property = false;
		m_defense = 2;

		m_mvt = {1,1,2,3,1,0,0,0};
	}

	if(p_type == ROADS || p_type == BRIDGES)
	{
		m_property = false;
		m_defense = 0;

		m_mvt = {1,1,1,1,1,0,0,0};
	}

	if(p_type == CITY || p_type == BASE)
	{
		m_property = true;
		m_owner = p_owner;

		m_defense = 3;

		m_mvt = {1,1,1,1,1,0,0,0};
	}

	if(p_type == HQ)
	{
		m_property = true;
		m_owner = p_owner;

		m_defense = 4;

		m_mvt = {1,1,1,1,1,0,0,0};
	}

	if(m_property)
		m_hp = 20;

} // Terrain()


std::array<int,8> GENGINE_TER::getMvt()
{
	return m_mvt;
} // getMvt()

pair<int, int> GENGINE_TER::getCoord()
{
	return make_pair(m_x,m_y);
} // getCoord()

TERRAINTYPE GENGINE_TER::getType() const
{
	return m_type;
} // getType()

bool GENGINE_TER::isProperty()
{
	return m_property;
} // isProperty()

bool GENGINE_TER::isNoneTerrain()
{
	return m_type == OTHER && m_x == -1  && m_y == -1;
} // isNoneTerrain()

PLAYER_TYPE GENGINE_TER::getOwner() const
{
	return m_owner;
} // getOwner()

void GENGINE_TER::setOwner(PLAYER_TYPE p_owner) 
{
	m_owner = p_owner;
} // setOwner()

GENGINE_TER::~Terrain()
{
} // ~Terrain()

int GENGINE_TER::getHp()
{
	return m_hp;
} // getHp()

int GENGINE_TER::getDefense()
{
    return m_defense;
} // getDefense()

void GENGINE_TER::setHp(int p_hp)
{
	m_hp = p_hp;
} // setHp()

void GENGINE_TER::resetHp()
{
	setHp(20);
} // resetHp()
