#ifndef DEF_UNIT_H
#define DEF_UNIT_H

// STD LIB INCLUDES
#include <vector>
#include <string>

// OTHER INCLUDES FROM PROJECT
#include "../Misc/Misc.h"

namespace nsGameEngine
{
    enum UNITTYPE
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
    }; // UNITTYPE

    enum MVTTYPE
    {
        FOOT = 0,
        BOOTS,
        TREADS,
        TIRES,
        AIR,
        SEA,
        LANDER,
        PIPE
    }; // MvtType

    typedef struct UnitInfo UnitInfo;
    struct UnitInfo
    {
        int mvt;
        int ammo;
        int fuel;
        int vision;
        int range;
        int cost;
        int hp;
        MVTTYPE mvtType;
        std::string message;
    }; // UnitInfo

    class Unit
    {
        public:
            // Contructors / Destructor
            Unit();
            Unit(UNITTYPE p_type, int p_x, int p_y, PLAYER_TYPE p_owner, int p_gid);
            ~Unit();

            // Static function : get unit information
            static UnitInfo getUnitInfo(UNITTYPE p_type);

            void fillBaseDamage();
            int getBaseDamage(Unit p_b);

            // Properties getters
            PLAYER_TYPE getOwner();
            MVTTYPE getMvtType();
            UNITTYPE getType();
            
            // Getters
            std::pair<int, int> getCoord();
            std::string getName();
            int getVision();
            int getHp();
            int getGid();
            int getMvt();
            int getAmmo();
            int getFuel();
            int getRange();
            
            // Setters
            void setCoord(int p_x, int p_y);
            void setHp(int p_hp);    

            // Test function
            bool isNoneUnit();

            // Uniq id management
            static int m_lastId;
            int getId();

            // Comparators
            bool operator == (Unit p_a) const
            {
                return m_x == p_a.getCoord().first && m_y == p_a.getCoord().second && m_gid == p_a.getGid() && m_ammo == p_a.getAmmo() && m_fuel == p_a.getFuel();
            }

            bool operator != (Unit p_a) const
            {
                return (!operator==(p_a));
            }
                        

        private:
            // Unit ID
            int m_id;

            // Unit properties
            UNITTYPE    m_type;
            PLAYER_TYPE m_owner;
            MVTTYPE     m_mvtType;

            // Unit settings
            int m_x;
            int m_y;            
            int m_gid;
            int m_hp;
            int m_mvt;
            int m_ammo;
            int m_fuel;
            int m_vision;
            int m_range;            
            int m_cost;            
            int m_baseDamage[9][9];
    }; // Unit
} // nsGameEngine

#endif // DEF_UNIT_H
