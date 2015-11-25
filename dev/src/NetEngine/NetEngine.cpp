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
	if (m_isServer)
	    delete m_server;
	    
	disconnect();
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
    printf("oo");
    sf::Time timeout = sf::seconds(10.0);
    cout << m_socket.getRemoteAddress() << "ADDR" << endl;
    if (m_socket.connect(m_ipAddress, m_port, timeout) != sf::Socket::Done)
    {
        cout << "Failed to connect to server" << endl;
        return;

    }
    cout << "CONECT" << endl;
   // Waiting for the welcome message (200)
    char data[256];
    size_t received;
    m_socket.receive(data, 256, received);
    if (string(data, 3) != "200")
    {
        manageError(string(data, 3));
    }
    cout << "RECEIVED" << endl;
    // Sending player information to be accepted
    NetPackage package;
    char typeStr[2];
    sprintf(typeStr, "%d", m_playerType);
    
    package.message = m_playerName + "#" + typeStr;
    send(package);

    // Waiting for acceptance
    cout << "WAIT RECEIVE from : " << package.message << endl;
    char data2[256];
    m_socket.receive(data2, 256, received);
    cout << "Received " << string(data2) << endl;
    if (string(data2, 3) != "200")
    {
        manageError(string(data, 3));
        return;
    }  
        
    // Start listener thread
    cout << "Connected" << endl;
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
            cerr << "Error receiving message for server " << status << endl;
            disconnect();             
            return;  
        }
        string strData = string(data);
        string strCode = strData.substr(strData.size() - 3);
        if (strCode == "100")
        {
            message += strData.substr(0, strData.size() - 3);
            parseMessage(message);
        }
        else if (strData.size() == 3)
        {
            parseMessage(message);
        }
        else
            message += string(data);
    }
}

void NETENGINE::disconnect()
{
    m_socket.disconnect();
    m_listenerThread->detach();
    delete m_listenerThread;
}

void NETENGINE::send(const NetPackage &p_package)
{
    char* data;
    string toSend = p_package.message + "100";
    NetPackage np;
    np.message = toSend;
    vector<NetPackage> splitMessage = splitMessages(np);
    
    for (NetPackage NetP : splitMessage)
    {
        cout << " TO SEND " << NetP.message.size() << ": " << NetP.message << endl;
        data = (char*)NetP.message.c_str();
        cout << " REALLY : " << string(data) << " - size : " << string(data).size() << endl;
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
    cout << p_message << endl;
}
