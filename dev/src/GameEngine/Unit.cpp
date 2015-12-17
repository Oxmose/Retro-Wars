#include "Unit.h"

#define GENGINE_UN nsGameEngine::Unit

GENGINE_UN::Unit()
{
	m_owner = NEUTRAL;
	m_id = m_lastId++;
}

GENGINE_UN::Unit(UnitType p_type, int p_x, int p_y, PLAYER_TYPE p_owner, int p_gid)
{
	m_type = p_type;
	m_x = p_x;
	m_y = p_y;
	m_gid = p_gid;
	m_hp = 10;
	m_id = m_lastId++;

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

	fillBaseDamage();
}

void GENGINE_UN::fillBaseDamage()
{
	m_baseDamage[INFANTRY][INFANTRY] = 55;
	m_baseDamage[INFANTRY][MDTANK] = 1;
	m_baseDamage[INFANTRY][RECON] = 12;
	m_baseDamage[INFANTRY][ARTILLERY] = 15;
	m_baseDamage[INFANTRY][NEOTANK] = 1;
	m_baseDamage[INFANTRY][MEGATANK] = 1;
	m_baseDamage[INFANTRY][MECH] = 45;
	m_baseDamage[INFANTRY][TANK] = 5;
	m_baseDamage[INFANTRY][ROCKET] = 25;

	m_baseDamage[MDTANK][INFANTRY] = 105;
	m_baseDamage[MDTANK][MDTANK] = 55;
	m_baseDamage[MDTANK][RECON] = 105;
	m_baseDamage[MDTANK][ARTILLERY] = 105;
	m_baseDamage[MDTANK][NEOTANK] = 45;
	m_baseDamage[MDTANK][MEGATANK] = 25;
	m_baseDamage[MDTANK][MECH] = 95;
	m_baseDamage[MDTANK][TANK] = 85;
	m_baseDamage[MDTANK][ROCKET] = 105;	

	m_baseDamage[RECON][INFANTRY] = 70;
	m_baseDamage[RECON][MDTANK] = 1;
	m_baseDamage[RECON][RECON] = 35;
	m_baseDamage[RECON][ARTILLERY] = 45;
	m_baseDamage[RECON][NEOTANK] = 1;
	m_baseDamage[RECON][MEGATANK] = 1;
	m_baseDamage[RECON][MECH] = 65;
	m_baseDamage[RECON][TANK] = 6;
	m_baseDamage[RECON][ROCKET] = 55;

	m_baseDamage[ARTILLERY][INFANTRY] = 90;
	m_baseDamage[ARTILLERY][MDTANK] = 45;
	m_baseDamage[ARTILLERY][RECON] = 80;
	m_baseDamage[ARTILLERY][ARTILLERY] = 75;
	m_baseDamage[ARTILLERY][NEOTANK] = 40;
	m_baseDamage[ARTILLERY][MEGATANK] = 15;
	m_baseDamage[ARTILLERY][MECH] = 85;
	m_baseDamage[ARTILLERY][TANK] = 70;
	m_baseDamage[ARTILLERY][ROCKET] = 80;

	m_baseDamage[NEOTANK][INFANTRY] = 125;
	m_baseDamage[NEOTANK][MDTANK] = 75;
	m_baseDamage[NEOTANK][RECON] = 125;
	m_baseDamage[NEOTANK][ARTILLERY] = 115;
	m_baseDamage[NEOTANK][NEOTANK] = 55;
	m_baseDamage[NEOTANK][MEGATANK] = 35;
	m_baseDamage[NEOTANK][MECH] = 115;
	m_baseDamage[NEOTANK][TANK] = 105;
	m_baseDamage[NEOTANK][ROCKET] = 125;

	m_baseDamage[MEGATANK][INFANTRY] = 135;
	m_baseDamage[MEGATANK][MDTANK] = 125;
	m_baseDamage[MEGATANK][RECON] = 195;
	m_baseDamage[MEGATANK][ARTILLERY] = 195;
	m_baseDamage[MEGATANK][NEOTANK] = 115;
	m_baseDamage[MEGATANK][MEGATANK] = 65;
	m_baseDamage[MEGATANK][MECH] = 125;
	m_baseDamage[MEGATANK][TANK] = 180;
	m_baseDamage[MEGATANK][ROCKET] = 195;

	m_baseDamage[MECH][INFANTRY] = 65;
	m_baseDamage[MECH][MDTANK] = 15;
	m_baseDamage[MECH][RECON] = 85;
	m_baseDamage[MECH][ARTILLERY] = 70;
	m_baseDamage[MECH][NEOTANK] = 15;
	m_baseDamage[MECH][MEGATANK] = 5;
	m_baseDamage[MECH][MECH] = 55;
	m_baseDamage[MECH][TANK] = 55;
	m_baseDamage[MECH][ROCKET] = 85;

	m_baseDamage[TANK][INFANTRY] = 75;
	m_baseDamage[TANK][MDTANK] = 15;
	m_baseDamage[TANK][RECON] = 85;
	m_baseDamage[TANK][ARTILLERY] = 70;
	m_baseDamage[TANK][NEOTANK] = 15;
	m_baseDamage[TANK][MEGATANK] = 10;
	m_baseDamage[TANK][MECH] = 70;
	m_baseDamage[TANK][TANK] = 55;
	m_baseDamage[TANK][ROCKET] = 85;

	m_baseDamage[ROCKET][INFANTRY] = 95;
	m_baseDamage[ROCKET][MDTANK] = 55;
	m_baseDamage[ROCKET][RECON] = 90;
	m_baseDamage[ROCKET][ARTILLERY] = 80;
	m_baseDamage[ROCKET][NEOTANK] = 50;
	m_baseDamage[ROCKET][MEGATANK] = 25;
	m_baseDamage[ROCKET][MECH] = 90;
	m_baseDamage[ROCKET][TANK] = 75;
	m_baseDamage[ROCKET][ROCKET] = 85;
}

int GENGINE_UN::getBaseDamage(Unit p_b)
{
	return m_baseDamage[m_type][p_b.getType()];
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

int GENGINE_UN::getId()
{
	return m_id;
}

void GENGINE_UN::setCoord(int p_x, int p_y)
{
	m_x = p_x;
	m_y = p_y;
}

void GENGINE_UN::setHp(int p_hp)
{
	m_hp = p_hp;
}

GENGINE_UN::~Unit()
{

}
