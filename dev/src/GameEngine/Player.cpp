#include "Player.h"

#define GENGINE_PLAYER nsGameEngine::Player

GENGINE_PLAYER::Player(PLAYER_TYPE p_playerType) noexcept : m_playerType(p_playerType)
{
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