#include "Player.h"

#define GENGINE_PLAYER nsGameEngine::Player

GENGINE_PLAYER::Player(PLAYER_TYPE p_playerType) noexcept : m_playerType(p_playerType)
{
	// TEST
	m_money = 5000;
}

void GENGINE_PLAYER::setMoney(int p_money)
{
	m_money = p_money;
}

int GENGINE_PLAYER::getMoney()
{
	return m_money;
}

void GENGINE_PLAYER::setCoord(int p_x, int p_y)
{
	m_x = p_x;
	m_y = p_y;
}

std::pair<int,int> GENGINE_PLAYER::getCoord()
{
	return std::make_pair(m_x,m_y);
}

PLAYER_TYPE GENGINE_PLAYER::getType()
{
	return m_playerType;
}

void GENGINE_PLAYER::setCoord(const std::pair<int, int> &p_coord)
{
	setCoord(p_coord.first, p_coord.second);
}

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
	}
}
