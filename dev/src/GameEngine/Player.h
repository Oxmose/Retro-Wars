#ifndef DEF_PLAYER_H
#define DEF_PLAYER_H

#include <vector>
#include "../Misc/Misc.h"

namespace nsGameEngine
{
	class Player
	{
		public:

			Player(PLAYER_TYPE p_playerType) noexcept;

			void setMoney(int p_money);
			int getMoney();
		private:

			PLAYER_TYPE m_playerType;
			int m_money;

	};
}

#endif