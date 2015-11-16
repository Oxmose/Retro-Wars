#ifndef DEF_NETENGINE_H
#define DEF_NETENGINE_H

#include <string>
#include <vector>
#include <thread>

#include <SFML/Network.hpp>

#include "../Misc/Misc.h"
#include "Structures.h"

namespace nsNetEngine
{
    class Server
    {
        public:
           
            Server(const std::string &p_ipAddress, const unsigned int &p_port) noexcept;
            ~Server() noexcept;

            void launch();
			void send(const NetPackage &p_package, const unsigned int &p_clientId);
        
		private:
            void connectClient();
            void disconnectClients();
            void listenClients();

			std::string 	             m_ipAddress;
			unsigned int 	             m_port;

            std::vector<sf::TcpSocket*>  m_clients;  
            sf::TcpListener              m_listener; 
            std::thread*                 m_connectThread; 
            std::thread*                 m_listenClientsThread; 

            bool                         m_waitForClients;
            bool                         m_listen;      
    };

}


#endif
