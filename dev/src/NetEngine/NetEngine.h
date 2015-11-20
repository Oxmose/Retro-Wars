#ifndef DEF_NETENGINE_H
#define DEF_NETENGINE_H

#include <iostream>
#include <string>
#include <atomic>
#include <thread>

#include <SFML/Network.hpp>

#include "Server.h"
#include "Structures.h"
#include "../Misc/Misc.h"
#include "NetException.h"

namespace nsNetEngine
{	
	class Server;
    class NetEngine
    {
        public:
           
            NetEngine(const std::string &p_ipAddress, const unsigned int &p_port) noexcept;
            ~NetEngine() noexcept;

            void launch(const std::string &p_playerName, const std::string &p_mapName = "NONE", const PLAYER_TYPE &p_player = NEUTRAL) throw (NetException);
            void joinServer() throw (NetException);
            void disconnect();
            
			void notify(const unsigned int &p_clientId, const NetPackage &p_package);
			
			void send(const NetPackage &p_package);
			void listen();
			
			void setIsServer(const bool &p_isServer);
        
		private:
		    void parseMessage(const std::string &p_message);
		    void manageError(const std::string &p_error);
		
			std::string 	m_ipAddress;
			unsigned int 	m_port;
			bool 			m_isServer;
			
			PLAYER_TYPE     m_playerType;
			std::string     m_playerName;
			
			std::atomic<bool> m_listenServer;

			Server* 		m_server;
			
			sf::TcpSocket   m_socket;
			
			std::thread*     m_listenerThread;
    };

}


#endif
