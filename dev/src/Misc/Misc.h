#ifndef DEF_MISC_H
#define DEF_MISC_H

// STD LIBS
#include <string>

// The type de player can have. It's kind of a token.
enum PLAYER_TYPE 
{
    NEUTRAL = 0,
    RED     = 1,
    BLUE    = 2,
    GREEN   = 3,
    YELLOW  = 4,
    BLACK   = 5 
}; // PLAYER_TYPE

// Return a string of the name of the token, depending on the value of the PLAYER_TYPE
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
} // inline getPlayerName()

#endif // DEF_MISC_H
