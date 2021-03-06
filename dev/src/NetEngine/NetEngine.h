#ifndef DEF_NETENGINE_H
#define DEF_NETENGINE_H

// STD LIBS
#include <iostream>
#include <string>
#include <atomic>
#include <thread>

// SFML
#include <SFML/Network.hpp>

// INCLUDE FROM PACKAGE
#include "NetEngine.h"
#include "Structures.h"

// OTHER INCLUDE FROM PROJECT
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
            bool joinServer();
            void disconnect();
            
            // Send / receive management
            void send(const NetPackage &p_package, const bool &p_connect = false);
            void listen();
            
            // Basics settings
            void setIsServer(const bool &p_isServer);
            void setNotifier(nsGameEngine::GameEngine *p_gameEngine);
            bool isServer();

            std::pair<int,int> stringToCooord(const std::string &p_s);

            // Return map name if not host
            std::string getMapName();
            std::string getMapHash();
        
        private:

            // Parse network message
            void parseMessage(const std::string &p_message);

            // Manage error codes
            void manageError(const std::string &p_error);
            
            // Basic settings
            std::string     m_ipAddress;
            unsigned int    m_port;
            bool            m_isServer;
            std::string     m_mapName;
            std::string     m_mapHash;
        
            // Player settings
            PLAYER_TYPE     m_playerType;
            std::string     m_playerName;
        
            // Listener management
            std::atomic<bool>               m_listenServer;
            sf::TcpSocket                   m_socket;        
            std::thread                     *m_listenerThread;
            std::atomic<bool>                m_connected;

            // Server management
            Server                          *m_server;        
            
            // Game mechanics management
            const nsMapEngine::MapEngine    *m_map;
            nsGameEngine::GameEngine        *m_gameEngine;
    }; // NetEngine

} // nsNetEngine


#endif // DEF_NETENGINE_H
