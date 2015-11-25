#include <string>
#include <vector>
#include <thread>
#include <iostream>
#include <atomic>
#include <map>
#include <utility>

#include <SFML/Network.hpp>

#include "../Misc/Misc.h"

#include "Server.h"
#include "Structures.h"
#include "NetEngine.h"
#include "NetException.h"

#define NETSERVER nsNetEngine::Server

using namespace std;

NETSERVER::Server(const std::string &p_ipAddress, const unsigned int &p_port, NetEngine* p_netEngine, const vector<PLAYER_TYPE> &p_allowedPlayers) noexcept
{
    m_ipAddress = p_ipAddress;
    m_port      = p_port;
    m_netEngine = p_netEngine; 
    m_maxPlayer = p_allowedPlayers.size();
    m_lastId    = 0;
    
    for (unsigned int i = 0 ; i < 5; ++i)
    {
        m_availablePositions[i] = false;
    }

    for (PLAYER_TYPE type : p_allowedPlayers)
        m_availablePositions[type] = true;
}

NETSERVER::~Server() noexcept
{
    disconnectClients();  
           
    m_waitForClients = false;
    
    m_listener.close();
    m_connectThread->detach();  
    
    delete m_connectThread;
}

void NETSERVER::launch() throw (NetException)
{    
    if (m_listener.listen(m_port) != sf::Socket::Done)
    {
        throw NetException("Can't bind the socket", __LINE__);
    }

    m_waitForClients = true;
    m_listen = true;

    m_connectThread = new thread(&Server::connectClient, this);
}

void NETSERVER::send(const NetPackage &p_package, const unsigned int &p_clientId)
{
    char* data;
    data = (char*)p_package.message.c_str();
    m_clients[p_clientId].socket->send(data, p_package.message.size());
}

void NETSERVER::connectClient()
{
    NetPackage package;
    package.message = "200";
    
    while(m_waitForClients)
    {
        sf::TcpSocket* client = new sf::TcpSocket();
        
        if (m_listener.accept(*client) != sf::Socket::Done)
        {
            delete client;
        }
        else 
        {
            if (getClientsNumber() == m_maxPlayer)
            {
                char* data;
                data = (char*)"204";
                client->send(data, 3);
                delete client;
            }
            else
            {           
                Client clientStruct;
                clientStruct.status = false; 
                clientStruct.ipAddress = client->getRemoteAddress().toString();
                clientStruct.port = client->getRemotePort();
                clientStruct.id = m_lastId;
                clientStruct.socket = client;
                cout << " JUST CREATED " << client << endl;
                
                m_clients[m_lastId] = clientStruct;
                thread *m_listenClientsThread  = new thread(&Server::listenClients, this, m_lastId);
                m_listenClientsThreads[m_lastId] = m_listenClientsThread;
                send(package, m_lastId);
                
                m_lastId++;
            }
        }
    }
}

void NETSERVER::listenClients(unsigned int p_id) throw (NetException)
{
    sf::TcpSocket *client = m_clients[p_id].socket;
    
    char data[256];
    size_t received = 0;
    string message("");

    while(m_listen)
    {
        sf::Socket::Status status;
        cout << "LISTEN " << client << endl;
        if ((status = client->receive(data, 256, received)) != sf::Socket::Done)
        {
            if (m_clients.find(p_id) != m_clients.end())
            {
                if (sf::Socket::Disconnected == status)
                {
                    disconnectClient(p_id, false);               
                }
            } 
	        cerr << "Can't receive from client with IP " << m_clients[p_id].ipAddress << " ID : " << p_id << endl;
            return;
        }
        string strData = string(data);
	cout << strData << endl;
        if (strData.substr(strData.size() - 3) == "100")
        {
            message += strData.substr(0, strData.size() - 3);
            parseMessage(p_id, message);
        }
        else if (received == 3 && strData == "201")
        {
            disconnectClient(p_id, false);
            return;
        }
        else
            message += string(data);
    }
}

void NETSERVER::sendAll(const NetPackage &p_package)
{        
    for (pair<unsigned int, Client> client : m_clients)
    {
        send(p_package, client.first);
    }
}

void NETSERVER::disconnectClients()
{
    for (pair<unsigned int, Client>  client : m_clients)
    {
        disconnectClient(client.first, false);
    }
    m_clients.clear();
}

void NETSERVER::disconnectClient(const unsigned int &p_id, const bool &p_erase /* = true */)
{
    if (m_clients[p_id].socket != nullptr)
    {
	    if (m_clients[p_id].status) 
	    { 
		    NetPackage package;
		    package.message = "201";
		
		    send(package, p_id);
	    }
	    
	    m_clients[p_id].status = false;
	    m_clients[p_id].socket->disconnect();    
	    m_listenClientsThreads[p_id]->detach();
	    
	    delete m_listenClientsThreads[p_id];
	    delete m_clients[p_id].socket;
    }

    if (p_erase)
    {        
        m_listenClientsThreads.erase(p_id);
    }
}

unsigned int NETSERVER::getClientsNumber()
{
    unsigned int counter = 0;
    for (pair<unsigned int, Client> client : m_clients)
    {
        if (client.second.status)
            ++ counter;
    }
    return counter;
}

vector<nsNetEngine::Client> NETSERVER::getClients()
{   
    vector<Client> result;     
    for (pair<unsigned int, Client> client : m_clients)
    {
        if (client.second.status)
            result.push_back(client.second);
    }  
    return result;
}

void NETSERVER::parseMessage(const unsigned int &p_id, const std::string &p_message)
{
    // Accpet the client
    if (m_clients[p_id].status == false)
    {
        NetPackage np;
        // Message has to be like : name#type
        // Get the type
        string tmpMessage = p_message.substr(p_message.find("#") + 1);
        unsigned int playerType = stoi(tmpMessage);
        
        if (playerType > 5 || playerType < 0 || m_availablePositions[playerType] == false)
        {
            np.message = "203";
            send(np, p_id);
            disconnectClient(p_id);
         }
         else
         {
             m_availablePositions[playerType] = false;
             np.message = "200";
             send(np, p_id);
         }
    }
}
