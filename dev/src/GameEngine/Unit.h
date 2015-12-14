#ifndef DEF_UNIT_H
#define DEF_UNIT_H

#include <vector>
#include "../Misc/Misc.h"

namespace nsGameEngine
{
	enum UnitType
	{
		INFANTRY = 0,
		MDTANK,
		RECON,
		ARTILLERY,
		NEOTANK,
		MEGATANK,
		MECH,
		TANK,
		ROCKET
	};

	enum MvtType
	{
		FOOT = 0,
		BOOTS,
		TREADS,
		TIRES,
		AIR,
		SEA,
		LANDER,
		PIPE
	};

	class Unit
	{
		public:
			Unit();
			Unit(UnitType p_type, int p_x, int p_y, PLAYER_TYPE p_owner, int p_gid);
			~Unit();

			int getGid();
			std::pair<int,int> getCoord();
		private:
			UnitType m_type;
			int m_x;
			int m_y;
			PLAYER_TYPE m_owner;
			int m_gid;

			int m_hp;

			int m_mvt;
			int m_ammo;
			int m_fuel;
			int m_vision;
			int m_range;
			MvtType m_mvtType;
			int m_cost;
	};

}


#endif