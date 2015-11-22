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
	    bool		    status;
        std::string     ipAddress;
        unsigned int    port;
	    unsigned int	id;
	    sf::TcpSocket	*socket;

        std::string     playerName;
        PLAYER_TYPE     playerType;
    };
}

#endif
