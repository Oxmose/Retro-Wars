#include "Unit.h"

#define GENGINE_UN nsGameEngine::Unit

GENGINE_UN::Unit()
{
}

GENGINE_UN::Unit(UnitType p_type, int p_x, int p_y, int p_owner)
{
	m_type = p_type;
	m_x = p_x;
	m_y = p_y;

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

GENGINE_UN::~Unit()
{

}
