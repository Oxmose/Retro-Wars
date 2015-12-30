#ifndef DEF_STRUCTURES_H
#define DEF_STRUCTURES_H

#include <SFML/Network.hpp>
#include <vector>

#include "../Misc/Misc.h"

namespace nsNetEngine
{
    // NetPackage structure, may be extended later
    typedef struct NetPackage NetPackage; 
    struct NetPackage
    {
        std::string message;
    }; // NetPackage

    // Client structure
    typedef struct Client Client;
    struct Client
    {
        // Basic info
        bool            status;
        std::string     ipAddress;
        unsigned int    port;
        unsigned int    id;

        // In game info
        std::string     playerName;
        PLAYER_TYPE     playerType;

        // Network socket
        sf::TcpSocket   *socket;        
    }; // Client

	
    enum ACTION_TYPE
    {
        MOVE = 0,
        ATTACK,
		CH_TURN,
		NEW_PLAYER,
		DISCONNECTED,
		NEW_UNIT,
        CAPTURE,
		WIN
    };

    typedef struct Action Action;
    struct Action
    {
        ACTION_TYPE type;
        std::vector<std::pair<int, int>> coord;
        std::vector<int> data;
    };
} // nsNetEngine

#endif
