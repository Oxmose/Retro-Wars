#ifndef DEF_PLAYER_H
#define DEF_PLAYER_H

// STD LIB INCLUDES
#include <vector>
#include <string>

// OTHER INCLUDES FOM PROJECT
#include "../Misc/Misc.h"

namespace nsGameEngine
{
    class Player
    {
        public:
            // Construcotr
            Player(PLAYER_TYPE p_playerType) noexcept;

            // Getters
            std::pair<unsigned int, unsigned int> getCoord();
            std::string getPlayerName();
            PLAYER_TYPE getType();
            int getMoney();
        
            // Setters
            void setMoney(int p_money);
            void setCoord(unsigned int p_x, unsigned int p_y);
            void setCoord(const std::pair<unsigned int, unsigned int> &p_coord);
            
        private:

            // Player properties
            PLAYER_TYPE m_playerType;

            // Player settings
            int m_money;
            int m_x;
            int m_y;

    }; // Player
} // nsGameEngine

#endif // DEF_PLAYER_H
