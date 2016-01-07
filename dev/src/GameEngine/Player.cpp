// STD LIB INCLUDES
#include <vector>
#include <string>

// OTHER INCLUDES FOM PROJECT
#include "../Misc/Misc.h"

// HEADER FILE INCLUDE
#include "Player.h"

#define GENGINE_PLAYER nsGameEngine::Player

GENGINE_PLAYER::Player(PLAYER_TYPE p_playerType) noexcept : m_playerType(p_playerType)
{
    m_money = 5000;
} // Player()

void GENGINE_PLAYER::setMoney(int p_money)
{
    m_money = p_money;
} // setMoney()

int GENGINE_PLAYER::getMoney()
{
    return m_money;
} // getMoney()

void GENGINE_PLAYER::setCoord(unsigned int p_x, unsigned int p_y)
{
    m_x = p_x;
    m_y = p_y;
} // setCoord()

std::pair<unsigned int, unsigned int> GENGINE_PLAYER::getCoord()
{
    return std::make_pair(m_x,m_y);
} // getCoord()

PLAYER_TYPE GENGINE_PLAYER::getType()
{
    return m_playerType;
} // getType()

void GENGINE_PLAYER::setCoord(const std::pair<unsigned int, unsigned int> &p_coord)
{
    setCoord(p_coord.first, p_coord.second);
} // setCoord()

std::string GENGINE_PLAYER::getPlayerName()
{
    switch(m_playerType)
    {
        case 0:
            return "Neutral";
        case 1:
            return "Red";
        case 2:
            return "Blue";
        case 3:
            return "Green";
        case 4:
            return "Yellow";
        case 5:
            return "Black";
        default:
            return "Neutral";
    }
} // getPlayerName()
