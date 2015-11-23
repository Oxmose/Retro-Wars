#ifndef DEF_SERVER_H
#define DEF_SERVER_H

#include <string>
#include <vector>
#include <thread>
#include <iostream>
#include <atomic>
#include <map>
#include <array>
#include <utility>

#include <SFML/Network.hpp>

#include "../Misc/Misc.h"

#include "NetEngine.h"
#include "Structures.h"
#include "NetException.h"

namespace nsNetEngine
{
    class NetEngine;
    class Server
    {
        public:
           
            Server(const std::string &p_ipAddress, const unsigned int &p_port, NetEngine* p_netEngine, const std::vector<PLAYER_TYPE> &p_allowedPlayers) noexcept;
            ~Server() noexcept;

            void launch() throw (NetException);
            
            void disconnectClient(const unsigned int &p_id);

			void send(const NetPackage &p_package, const unsigned int &p_clientId);
            void sendAll(const NetPackage &p_package);

            unsigned int getClientsNumber();
            std::vector<Client> getClients();
        
		private:
            void connectClient();
            void disconnectClients();
            void listenClients(unsigned int p_id) throw (NetException);
            void parseMessage(const unsigned int &p_id, const std::string &p_message);

			std::string 	                        m_ipAddress;
			unsigned int 	                        m_port;

            std::map<unsigned int, Client>          m_clients;
            sf::TcpListener                         m_listener; 

            std::thread*                            m_connectThread; 
            std::map<unsigned int, std::thread*>    m_listenClientsThreads; 

            std::atomic<bool>                       m_waitForClients;
            std::atomic<bool>                       m_listen;     
            
            unsigned int                            m_lastId;
            
            NetEngine*                              m_netEngine;
            
            // Game management
            unsigned int                            m_maxPlayer;
            std::array<bool, 5>                     m_availablePositions;
    };

}


#endif
