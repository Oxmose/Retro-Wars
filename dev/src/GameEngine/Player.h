#ifndef DEF_PLAYER_H
#define DEF_PLAYER_H

#include <vector>

namespace nsGameEngine
{
	class Player
	{
		public:

			Player(const unsigned int & p_playerType) noexcept;

		private:

			const unsigned int m_playerType;

	};
}

#endif