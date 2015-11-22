#ifndef DEF_UNIT_H
#define DEF_UNIT_H

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
			Unit(UnitType p_type, int p_x, int p_y, int p_owner);
			~Unit();

		private:
			UnitType m_type;
			int m_x;
			int m_y;
			int m_owner;

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