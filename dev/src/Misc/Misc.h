#ifndef DEF_MISC_H
#define DEF_MISC_H

#include <string>

enum PLAYER_TYPE 
{
	NEUTRAL = 0,
	RED 	= 1,
	BLUE	= 2,
	GREEN	= 3,
	YELLOW 	= 4,
	BLACK	= 5 
};

inline std::string getPlayerName(PLAYER_TYPE p_playerType)
{
	switch(p_playerType)
	{
		case 0:
			return "Nobody";
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

#endif
