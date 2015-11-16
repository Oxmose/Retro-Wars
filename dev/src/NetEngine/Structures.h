#ifndef DEF_STRUCTURES_H
#define DEF_STRUCTURES_H

#include <SFML/Network.hpp>
#include "../Misc/Misc.h"

namespace nsNetEngine
{
	typedef struct NetPackage NetPackage; 
	struct NetPackage
	{
		std::string message;
	};

    typedef struct Client Client;
    struct Client
    {
        std::string     ipAddress;
        unsigned int    port;
        std::string     playerName;
        PLAYER_TYPE     playerType;
	sf::TcpSocket 	socket;
    };
}

#endif
