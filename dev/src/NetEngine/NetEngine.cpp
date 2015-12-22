#include <iostream>
#include <string>
#include <atomic>
#include <thread>

#include <SFML/Network.hpp>

#include "NetEngine.h"
#include "Server.h"
#include "Structures.h"

#include "../MapEngine/MapEngine.h"
#include "../GameEngine/GameEngine.h"
#include "../Misc/Misc.h"
#include "../Misc/Tools.h"

#define NETENGINE nsNetEngine::NetEngine

using namespace std;
using namespace nsTools;

NETENGINE::NetEngine(const std::string &p_ipAddress, const unsigned int &p_port)
{
    // Setting basic configuration
    m_ipAddress = p_ipAddress;
    m_port = p_port;
    m_listenServer = true;
    m_isServer = false;
} // NetEngine()

NETENGINE::~NetEngine()
{
    // Disconnecting from server
    disconnect();

    // If is host, disconnect server
    if(m_isServer)
        delete m_server;   
} // ~NetEngine()

void NETENGINE::setNotifier(nsGameEngine::GameEngine *p_gameEngine)
{
    // Set the game engine to notify
    m_gameEngine = p_gameEngine;
} // setNotifier()

bool NETENGINE::launch(const std::string &p_playerName, const PLAYER_TYPE &p_player /*= NEUTRAL*/, const nsMapEngine::MapEngine *p_map /* = nullptr */) 
{  
    bool launched = true;
    // The game instance is a player that hosts a game
    if(m_isServer)
    {
        m_map = p_map;
        m_server = new Server(m_ipAddress, m_port, this, m_map->getPlayers());
        launched = m_server->launch();
    }  
    
    // Basic settings
    m_playerName = p_playerName;    
    m_playerType = p_player;

    // Join the server
    joinServer(); 

    return launched;
} // launch()

void NETENGINE::setIsServer(const bool &p_isServer)
{
    // Set if the game instance is the host
    m_isServer = p_isServer;
} // setIsServer()

bool NETENGINE::isServer()
{
    return m_isServer;
} // isServer()

void NETENGINE::joinServer()
{
    sf::Time timeout = sf::seconds(10.0);

    if(m_socket.connect(m_ipAddress, m_port, timeout) != sf::Socket::Done)
    {
        cout << "[ERROR]Failed to connect to server" << endl;
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

    if(cleanMessage(string(data2)) != "200")
    {
        manageError(string(data, 3));
        return;
    }  
        
    // Start listener thread
    m_listenerThread = new thread(&NetEngine::listen, this);   
} // joinServer()

void NETENGINE::listen()
{
    char data[256];
    size_t received = 0;
    string message("");
    
    // While we have tolisten the server
    while(m_listenServer)
    {
        sf::Socket::Status status;
        if((status = m_socket.receive(data, 256, received)) != sf::Socket::Done)
        {
            cout << "Error receiving message for server " << status << endl;         
            
            if(status == sf::Socket::Disconnected)
                return;  
        }

        // Clean the message and get code if exists
        string strData = cleanMessage(string(data));
        string strCode = strData.substr(strData.size() - 3);
        // If end of message
        if(strCode == "|||")
        {
            message += strData.substr(0, strData.size() - 3);
            parseMessage(message);
            message = "";
        }
        else if(strData.size() == 3)
        {
            parseMessage(message);
        }
        else
        {
            message += strData;
        }
    }
} // listen();

void NETENGINE::disconnect()
{
    if(m_listenerThread != nullptr)
    {
        m_listenServer = false;
        m_socket.setBlocking(false);
        m_socket.disconnect();
        m_listenerThread->detach();
        delete m_listenerThread;
    }
} // disconnect();

void NETENGINE::send(const NetPackage &p_package, const bool &p_connect /* = false */)
{
    char* data;
    string toSend = p_package.message + "|||";
    NetPackage np;
    if(!p_connect)
        np.message = to_string(m_playerType) + string("#") + toSend;
    else
        np.message = toSend;
    vector<NetPackage> splitMessage = splitMessages(np);
    
    for(NetPackage NetP : splitMessage)
    { 
        NetP.message = to_string(NetP.message.size()) + "/" + NetP.message;    
        data = (char*)NetP.message.c_str();
        m_socket.send(data, NetP.message.size());
    }
} // send();

void NETENGINE::manageError(const std::string &p_error)
{
    if(p_error == "204")
    {
        cerr << "Too many players" << endl;
        disconnect();
    }
    if(p_error == "203")
    {
        cerr << "Player color already taken" << endl;
        disconnect();
    }
    if(p_error == "201")
    {
        cerr << "Connection closed by server" << endl;
        disconnect();
    }
} // manageError()

std::pair<int,int> NETENGINE::stringToCooord(const std::string &p_s)
{
    int i = p_s.find(",");
    return make_pair(std::stoi(p_s.substr(1,i-1)),std::stoi(p_s.substr(i+1, p_s.size()-i-2)));
}

void NETENGINE::parseMessage(const std::string &p_message)
{   
    cout << "recu : " << p_message << endl;
    auto split = splitString(p_message, "::");
    for(auto a : splitString(p_message, "::"))
        cout << "parse : " << a << endl;
    Action action;
    switch(split[0][split[0].size()-1])
    {
        case '0':
            
            action.type = MOVE;
            stringToCooord(split[1]);
            stringToCooord(split[2]);
            action.coord.push_back(stringToCooord(split[1]));
            action.coord.push_back(stringToCooord(split[2]));
            m_gameEngine->notify(action);
            break;
        case '1':
            action.type = ATTACK;
            stringToCooord(split[1]);
            stringToCooord(split[2]);
            action.coord.push_back(stringToCooord(split[1]));
            action.coord.push_back(stringToCooord(split[2]));
            action.data.push_back(stoi(split[3]));
            action.data.push_back(stoi(split[4]));
            m_gameEngine->notify(action);
            break;
	case '2':
            action.type = CH_TURN;
            action.data.push_back(stoi(split[1]));
            m_gameEngine->notify(action);
            break;
    }
    	
} // parseMessage()
