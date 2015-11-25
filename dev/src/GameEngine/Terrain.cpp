#include "Terrain.h"

#define GENGINE_TER nsGameEngine::Terrain 

using namespace std;


GENGINE_TER::Terrain()
{
}

GENGINE_TER::Terrain(TerrainType p_type, int p_x, int p_y, int p_owner)
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

}

GENGINE_TER::~Terrain()
{

}