#ifndef DEF_NETENGINE_H
#define DEF_NETENGINE_H

#include <iostream>
#include <string>
#include <atomic>
#include <thread>

#include <SFML/Network.hpp>

#include "Server.h"
#include "Structures.h"
#include "NetException.h"

#include "../MapEngine/MapEngine.h"
#include "../GameEngine/GameEngine.h"
#include "../Misc/Misc.h"
#include "../Misc/Tools.h"

namespace nsGameEngine
{
    class GameEngine;
}
namespace nsNetEngine
{	
	class Server;
    class NetEngine
    {
        public:
           
            NetEngine(const std::string &p_ipAddress, const unsigned int &p_port) noexcept;
            ~NetEngine() noexcept;

            void launch(const std::string &p_playerName, const PLAYER_TYPE &p_player = NEUTRAL, const nsMapEngine::MapEngine *p_map = nullptr) throw (NetException);

            void joinServer() throw (NetException);
            void disconnect();
			
			void send(const NetPackage &p_package, const bool &p_connect = false);
			void listen();
			
			void setIsServer(const bool &p_isServer);
            void setNotifier(nsGameEngine::GameEngine *p_gameEngine);
        
		private:
		    void parseMessage(const std::string &p_message);
		    void manageError(const std::string &p_error);
		
			std::string 	m_ipAddress;
			unsigned int 	m_port;
			bool 			m_isServer;
		
			PLAYER_TYPE     m_playerType;
			std::string     m_playerName;
		
			std::atomic<bool>               m_listenServer;
			Server* 		                m_server;		
			sf::TcpSocket                   m_socket;		
			std::thread*                    m_listenerThread;
            
            const nsMapEngine::MapEngine    *m_map;

            nsGameEngine::GameEngine  *m_gameEngine;
    };

}


#endif
