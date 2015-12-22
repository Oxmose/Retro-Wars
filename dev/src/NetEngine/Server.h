#ifndef DEF_SERVER_H
#define DEF_SERVER_H

#include <string>
#include <vector>
#include <array>
#include <thread>
#include <mutex>
#include <iostream>
#include <atomic>
#include <map>
#include <utility>

#include <SFML/Network.hpp>

#include "../Misc/Misc.h"
#include "../Misc/Tools.h"

#include "Structures.h"
#include "NetEngine.h"

namespace nsNetEngine
{
    // Forward declaration
    class NetEngine;
    
    // Server class (runs threads)
    class Server
    {
        public:
           
            // Constructor / Destructor
            Server(const std::string &p_ipAddress, const unsigned int &p_port, NetEngine* p_netEngine, const std::vector<PLAYER_TYPE> &p_allowedPlayers);
            ~Server();

            // Launch server
            bool launch();
            
            // Disconect client
            void disconnectClient(const unsigned int &p_id, const bool &p_notErase = true);

            // Send messages functions
            void send(const NetPackage &p_package, const unsigned int &p_clientId, const bool &p_split);
            void sendAll(const NetPackage &p_package, const int &p_except = -1);

            // Getters
            unsigned int getClientsNumber();
            std::vector<Client> getClients();
        
        private:
            // Add client to connected clients
            void connectClient();
            
            // Disconnect all clients
            void disconnectClients();

            // Thread listening to clients
            void listenClients(unsigned int p_id);

            // Parse net messages
            void parseMessage(const unsigned int &p_id, const std::string &p_message);

            // Basic settings
            std::string                             m_ipAddress;
            unsigned int                            m_port;
            unsigned int                            m_maxPlayer;
            std::array<bool, 5>                     m_availablePositions;

            // Clients management
            std::map<unsigned int, Client>          m_clients;
            std::map<unsigned int, std::thread*>    m_listenClientsThreads;

            // Listen management
            sf::TcpListener                         m_listener; 
            std::thread*                            m_connectThread;

            // Atomic / Mutex
            std::atomic<bool>                       m_waitForClients;
            std::atomic<bool>                       m_listen;
            std::mutex                              m_clientListMutex;   
            std::mutex                              m_clientSocketListMutex;  
            
            // Last user id
            unsigned int                            m_lastId;    

            // NetEngine pointer        
            NetEngine*                              m_netEngine;
    }; // Server

} // nsNetEngine


#endif
