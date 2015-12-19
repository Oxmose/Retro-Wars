#ifndef DEF_NETENGINE_H
#define DEF_NETENGINE_H

#include <iostream>
#include <string>
#include <atomic>
#include <thread>

#include <SFML/Network.hpp>

#include "Server.h"
#include "Structures.h"

#include "../MapEngine/MapEngine.h"
#include "../GameEngine/GameEngine.h"
#include "../Misc/Misc.h"
#include "../Misc/Tools.h"

namespace nsGameEngine
{
    // Forward declaration
    class GameEngine;
} // nsGameEngine

namespace nsNetEngine
{    
    // Forward declaration
    class Server;

    // NetEngine class (runs threads)
    class NetEngine
    {
        public:
           
            // Constructor  Destructor
            NetEngine(const std::string &p_ipAddress, const unsigned int &p_port);
            ~NetEngine();

            // Launch NetEngine
            bool launch(const std::string &p_playerName, const PLAYER_TYPE &p_player = NEUTRAL, const nsMapEngine::MapEngine *p_map = nullptr);

            // Connection management
            void joinServer();
            void disconnect();
            
            // Send / receive management
            void send(const NetPackage &p_package, const bool &p_connect = false);
            void listen();
            
            // Basics settings
            void setIsServer(const bool &p_isServer);
            void setNotifier(nsGameEngine::GameEngine *p_gameEngine);

            std::pair<int,int> stringToCooord(const std::string &p_s);
        
        private:

            // Parse network message
            void parseMessage(const std::string &p_message);

            // Manage error codes
            void manageError(const std::string &p_error);
            
            // Basic settings
            std::string     m_ipAddress;
            unsigned int    m_port;
            bool            m_isServer;
        
            // Player settings
            PLAYER_TYPE     m_playerType;
            std::string     m_playerName;
        
            // Listener management
            std::atomic<bool>               m_listenServer;
            sf::TcpSocket                   m_socket;        
            std::thread                     *m_listenerThread;

            // Server management
            Server                          *m_server;        
            
            // Game mechanics management
            const nsMapEngine::MapEngine    *m_map;
            nsGameEngine::GameEngine        *m_gameEngine;
    }; // NetEngine

} // nsNetEngine


#endif
