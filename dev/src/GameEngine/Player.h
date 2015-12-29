#ifndef DEF_PLAYER_H
#define DEF_PLAYER_H

#include <vector>
#include <string>
#include "../Misc/Misc.h"

namespace nsGameEngine
{
	class Player
	{
		public:

			Player(PLAYER_TYPE p_playerType) noexcept;

			void setMoney(int p_money);
			int getMoney();

			void setCoord(unsigned int p_x, unsigned int p_y);
			void setCoord(const std::pair<unsigned int, unsigned int> &p_coord);
			std::pair<unsigned int, unsigned int> getCoord();
			std::string getPlayerName();
			PLAYER_TYPE getType();
			
		private:

			PLAYER_TYPE m_playerType;
			int m_money;
			int m_x;
			int m_y;

	};
}

#endif
