#ifndef DEF_SERVER_H
#define DEF_SERVER_H

// STD LIBS
#include <string>
#include <vector>
#include <array>
#include <thread>
#include <mutex>
#include <iostream>
#include <atomic>
#include <map>
#include <utility>

// SFML
#include <SFML/Network.hpp>

// INCLUDE FROM PACKAGE
#include "NetEngine.h"
#include "Structures.h"

// OTHER INCLUDES FROM PROJECT
#include "../Misc/Misc.h"
#include "../Misc/Tools.h"

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
            bool launch(const std::string &p_mapName, const std::string &p_mapHash);
            
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

            // Allow to timeout (non blocking forever the thread)
            sf::Socket::Status receiveTime(sf::TcpSocket &p_socket, char* p_buffer, const unsigned int p_limit, size_t &p_received);
            sf::Socket::Status acceptTime(sf::TcpListener &p_listener, sf::TcpSocket &p_client);

            // Parse net messages
            void parseMessage(const unsigned int &p_id, const std::string &p_message);

            // Basic settings
            std::string                             m_ipAddress;
            unsigned int                            m_port;
            unsigned int                            m_maxPlayer;
            std::array<bool, 5>                     m_availablePositions;
        
            std::string                             m_mapName;
            std::string                             m_mapHash;

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
