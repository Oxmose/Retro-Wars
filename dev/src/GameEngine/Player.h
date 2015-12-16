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

			void setCoord(int p_x, int p_y);
			void setCoord(const std::pair<int, int> &p_coord);
			std::pair<int,int> getCoord();
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
