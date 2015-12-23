#ifndef DEF_UNIT_H
#define DEF_UNIT_H

#include <vector>
#include <string>
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

	typedef struct UnitInfo UnitInfo;
	struct UnitInfo
	{
        int mvt;
		int ammo;
		int fuel;
		int vision;
		int range;
		MvtType mvtType;
		int cost;
		int hp;
		std::string message;
	};

	class Unit
	{
		public:
			Unit();
			Unit(UnitType p_type, int p_x, int p_y, PLAYER_TYPE p_owner, int p_gid);
			~Unit();

			static UnitInfo getUnitInfo(UnitType p_type);

			void fillBaseDamage();
			int getBaseDamage(Unit p_b);

			int getGid();
			std::pair<int,int> getCoord();
			void setCoord(int p_x, int p_y);
			PLAYER_TYPE getOwner();
			int getVision();
			int getHp();
			void setHp(int p_hp);
			std::string getName();
			int getMvt();
			int getAmmo();
			int getFuel();
			int getRange();
			MvtType getMvtType();
			UnitType getType();

			bool isNoneUnit();
			int getId();

            // Uniq id management
            static int m_lastId;

            bool operator == (Unit p_a) const
            {
            	return m_x == p_a.getCoord().first && m_y == p_a.getCoord().second;
            }
			

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
            
			int m_id;

			int m_baseDamage[9][9];


	};

}


#endif
