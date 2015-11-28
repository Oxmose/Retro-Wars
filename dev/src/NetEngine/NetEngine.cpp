#include <iostream>
#include <string>
#include <atomic>
#include <thread>

#include <SFML/Network.hpp>

#include "NetEngine.h"
#include "Server.h"
#include "Structures.h"
#include "NetException.h"

#include "../MapEngine/MapEngine.h"
#include "../GameEngine/GameEngine.h"
#include "../Misc/Misc.h"
#include "../Misc/Tools.h"

#define NETENGINE nsNetEngine::NetEngine

using namespace std;
using namespace nsTools;

NETENGINE::NetEngine(const std::string &p_ipAddress, const unsigned int &p_port) noexcept
{
    m_ipAddress = p_ipAddress;
    m_port = p_port;
    m_listenServer = true;
    m_isServer = false;
}

NETENGINE::~NetEngine() noexcept
{
    disconnect();
	if (m_isServer)
	    delete m_server;
	    
	
}

void NETENGINE::setNotifier(nsGameEngine::GameEngine *p_gameEngine)
{
    m_gameEngine = p_gameEngine;
}

void NETENGINE::launch(const std::string &p_playerName, const PLAYER_TYPE &p_player /*= NEUTRAL*/, const nsMapEngine::MapEngine *p_map /* = nullptr */) throw (NetException)
{  
    // The game instance is a player that hosts a game
    if (m_isServer)
    {
        m_map = p_map;
        m_server = new Server(m_ipAddress, m_port, this, m_map->getPlayers());

	    m_server->launch();
    }  
    
    m_playerName = p_playerName;    
    m_playerType = p_player;
    joinServer(); 
}

void NETENGINE::setIsServer(const bool &p_isServer)
{
    m_isServer = p_isServer;
}

void NETENGINE::joinServer() throw (NetException)
{
    sf::Time timeout = sf::seconds(10.0);

    if (m_socket.connect(m_ipAddress, m_port, timeout) != sf::Socket::Done)
    {
        cout << "Failed to connect to server" << endl;
        return;

    }
   // Waiting for the welcome message (200)

    char data[256];
    size_t received;
    m_socket.receive(data, 256, received);
    if (cleanMessage(string(data)) != "200")
    {
        manageError(cleanMessage(string(data, 3)));
    }

    // Sending player information to be accepted
    NetPackage package;
    char typeStr[2];
    sprintf(typeStr, "%d", m_playerType);
    
    package.message = m_playerName + "#" + typeStr;
    send(package, true);

    // Waiting for acceptance
    char data2[256];
    m_socket.receive(data2, 256, received);

    if (cleanMessage(string(data2)) != "200")
    {
        manageError(string(data, 3));
        return;
    }  
        
    // Start listener thread
    m_listenerThread = new thread(&NetEngine::listen, this);   
}

void NETENGINE::listen()
{
    char data[256];
    size_t received = 0;
    string message("");
    
    while(m_listenServer)
    {

        sf::Socket::Status status;
        if ((status = m_socket.receive(data, 256, received)) != sf::Socket::Done)
        {
            cout << "Error receiving message for server " << status << endl;         
            
            if (status == sf::Socket::Disconnected)
                return;  
        }
        string strData = cleanMessage(string(data));
        string strCode = strData.substr(strData.size() - 3);
        if (strCode == "|||")
        {
            message += strData.substr(0, strData.size() - 3);
            parseMessage(message);
            message = "";
        }
        else if (strData.size() == 3)
        {
            parseMessage(message);
        }
        else
        {
            message += strData;
        }
    }
}

void NETENGINE::disconnect()
{
    if (m_listenerThread != nullptr)
    {
        m_listenServer = false;
        m_socket.setBlocking(false);
        m_socket.disconnect();
        m_listenerThread->detach();
        delete m_listenerThread;
    }
}

void NETENGINE::send(const NetPackage &p_package, const bool &p_connect /* = false */)
{
    char* data;
    string toSend = p_package.message + "|||";
    NetPackage np;
    if (!p_connect)
    	np.message = to_string(m_playerType) + string("#") + toSend;
    else
	    np.message = toSend;
    vector<NetPackage> splitMessage = splitMessages(np);
    
    for (NetPackage NetP : splitMessage)
    { 
	    NetP.message = to_string(NetP.message.size()) + "/" + NetP.message;	
        data = (char*)NetP.message.c_str();
        m_socket.send(data, NetP.message.size());
    }
}

void NETENGINE::manageError(const std::string &p_error)
{
    if (p_error == "204")
    {
        throw new string("Too many players");
        disconnect();
    }
    if (p_error == "203")
    {
        throw new string("Player color already taken");
        disconnect();
    }
    if (p_error == "201")
    {
        throw new string("Connection closed by server");
        disconnect();
    }
}

void NETENGINE::parseMessage(const std::string &p_message)
{
    
    m_gameEngine->notify(p_message);
}
