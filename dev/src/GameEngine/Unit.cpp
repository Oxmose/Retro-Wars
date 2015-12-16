#include "Unit.h"

#define GENGINE_UN nsGameEngine::Unit

GENGINE_UN::Unit()
{
	m_owner = NEUTRAL;
}

GENGINE_UN::Unit(UnitType p_type, int p_x, int p_y, PLAYER_TYPE p_owner, int p_gid)
{
	m_type = p_type;
	m_x = p_x;
	m_y = p_y;
	m_gid = p_gid;
	m_hp = 10;

	m_owner = p_owner;

	if(p_type == INFANTRY)
	{
		m_mvt = 3;
		m_ammo = -1;//infinite
		m_fuel = 99;
		m_vision = 2;
		m_range = 1;
		m_mvtType = FOOT;
		m_cost = 1000;
	}

	if(p_type == MDTANK)
	{
		m_mvt = 5;
		m_ammo = 8;
		m_fuel = 50;
		m_vision = 1;
		m_range = 1;
		m_mvtType = TREADS;
		m_cost = 16000;
	}

	if(p_type == RECON)
	{
		m_mvt = 8;
		m_ammo = -1;
		m_fuel = 80;
		m_vision = 5;
		m_range = 1;
		m_mvtType = TIRES;
		m_cost = 4000;
	}

	if(p_type == ARTILLERY)
	{
		m_mvt = 5;
		m_ammo = 9;
		m_fuel = 50;
		m_vision = 1;
		m_range = 3;
		m_mvtType = TREADS;
		m_cost = 6000;
	}

	if(p_type == NEOTANK)
	{
		m_mvt = 6;
		m_ammo = 9;
		m_fuel = 99;
		m_vision = 1;
		m_range = 1;
		m_mvtType = TREADS;
		m_cost = 220000;
	}

	if(p_type == MEGATANK)
	{
		m_mvt = 4;
		m_ammo = 3;
		m_fuel = 50;
		m_vision = 1;
		m_range = 1;
		m_mvtType = TREADS;
		m_cost = 280000;
	}

	if(p_type == MECH)
	{
		m_mvt = 2;
		m_ammo = 3;
		m_fuel = 70;
		m_vision = 2;
		m_range = 1;
		m_mvtType = BOOTS;
		m_cost = 3000;
	}

	if(p_type == TANK)
	{
		m_mvt = 6;
		m_ammo = 9;
		m_fuel = 70;
		m_vision = 3;
		m_range = 1;
		m_mvtType = TREADS;
		m_cost = 7000;
	}

	if(p_type == ROCKET)
	{
		m_mvt = 5;
		m_ammo = 6;
		m_fuel = 50;
		m_vision = 1;
		m_range = 5;
		m_mvtType = TIRES;
		m_cost = 15000;
	}
}

int GENGINE_UN::getGid()
{
	return m_gid;
}

nsGameEngine::MvtType GENGINE_UN::getMvtType()
{
	return m_mvtType;
}

PLAYER_TYPE GENGINE_UN::getOwner()
{
	return m_owner;
}
			
int GENGINE_UN::getVision()
{
	return m_vision;
}

std::pair<int,int> GENGINE_UN::getCoord()
{
	return std::make_pair(m_x,m_y);
}

int GENGINE_UN::getHp()
{
	return m_hp;
}
std::string GENGINE_UN::getName()
{
	switch(m_type)
	{
		case INFANTRY:
			return "Infantry";
		case MDTANK:
			return "MdTank";
		case RECON:
			return "Recon";
		case ARTILLERY:
			return "Artillery";
		case NEOTANK:
			return "Neotank";
		case MEGATANK:
			return "Megatank";
		case MECH:
			return "Mech";
		case TANK:
			return "Tank";
		case ROCKET:
			return "Rocket";
	}
}
int GENGINE_UN::getMvt()
{
	return m_mvt;
}
int GENGINE_UN::getAmmo()
{
	return m_ammo;
}

int GENGINE_UN::getRange()
{
	return m_range;
}
int GENGINE_UN::getFuel()
{
	return m_fuel;
}

bool GENGINE_UN::isNoneUnit()
{
	return m_type == INFANTRY && m_x == -1 && m_y == -1 && m_owner == NEUTRAL && m_gid == 0;
}

nsGameEngine::UnitType GENGINE_UN::getType()
{
	return m_type;
}
GENGINE_UN::~Unit()
{

}
