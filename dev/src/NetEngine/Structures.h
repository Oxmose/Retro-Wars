#ifndef DEF_STRUCTURES_H
#define DEF_STRUCTURES_H

#include <SFML/Network.hpp>

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
} // nsNetEngine

#endif
