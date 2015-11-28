#include <string>
#include <vector>
#include <thread>
#include <iostream>
#include <atomic>
#include <map>
#include <utility>

#include <SFML/Network.hpp>

#include "../Misc/Misc.h"
#include "../Misc/Tools.h"

#include "Server.h"
#include "Structures.h"
#include "NetEngine.h"
#include "NetException.h"

#define NETSERVER nsNetEngine::Server

using namespace std;
using namespace nsTools;

NETSERVER::Server(const std::string &p_ipAddress, const unsigned int &p_port, NetEngine* p_netEngine, const vector<PLAYER_TYPE> &p_allowedPlayers) noexcept
{
    // Init
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
    m_listen         = false; 
   
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

void NETSERVER::send(const NetPackage &p_package, const unsigned int &p_clientId, const bool &p_split)
{
    if (p_split)
    {
        char* data;
        string toSend = p_package.message + "|||";
        NetPackage np;
        np.message = toSend;
        vector<NetPackage> splitMessage = splitMessages(np);
        
        for (NetPackage NetP : splitMessage)
        {
            NetP.message = to_string(NetP.message.size()) + "/" + NetP.message;
            data = (char*)NetP.message.c_str();
            m_clients[p_clientId].socket->send(data, NetP.message.size());
        }
    }
    else
    {
        char* data;
        string toSend = to_string(p_package.message.size()) + "/" + p_package.message;
        data = (char*)toSend.c_str();
        m_clients[p_clientId].socket->send(data, toSend.size());
    }
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

                clientStruct.ipAddress = client->getRemoteAddress().toString();
                clientStruct.port = client->getRemotePort();
                clientStruct.socket = client;

                clientStruct.id = m_lastId;
                clientStruct.status = false; 
                
                m_clients[m_lastId] = clientStruct;



                thread *m_listenClientsThread  = new thread(&Server::listenClients, this, m_lastId);
                m_listenClientsThreads[m_lastId] = m_listenClientsThread;

                send(package, m_lastId, false);
                
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
        cout << "WAITING" << endl;
        if ((status = client->receive(data, 256, received)) != sf::Socket::Done)
        {
            if (m_clients.find(p_id) != m_clients.end())
            {
                if (sf::Socket::Disconnected == status)
                {
                    if (m_clients[p_id].status != false)
                    {
                        m_clients[p_id].status = false;
                        disconnectClient(p_id, false); 
                    }
                                  
                }
                return;
            }            
        }
	
        string strData = cleanMessage(string(data));
	    cout << endl << "RECEIVED " << strData << endl;

        if (strData.substr(strData.size() - 3) == "|||")
        {
            message += strData.substr(0, strData.size() - 3);
	        cout << "SEND TO PARSE " << message << endl;
            parseMessage(p_id, message);
            message = "";
        }
        else if (received == 3 && strData == "201")
        {
            disconnectClient(p_id, false);
            return;
        }
        else
            message += strData;
    }
}

void NETSERVER::sendAll(const NetPackage &p_package, const int &p_except /* = -1 */)
{        
    for (pair<unsigned int, Client> client : m_clients)
    {
	if (client.first != p_except)
        	send(p_package, client.first, true);
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
		
		    send(package, p_id, false);
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
        
        if (playerType > 5 || m_availablePositions[playerType] == false)
        {
            np.message = "203";
            send(np, p_id, false);
            disconnectClient(p_id);
         }
         else
         {
             m_availablePositions[playerType] = false;
             m_clients[p_id].playerType = static_cast<PLAYER_TYPE>(playerType);
             m_clients[p_id].playerName = p_message.substr(0, p_message.find("#"));
             m_clients[p_id].status = true;
             np.message = "200";
             send(np, p_id, false);
             np.message = string("SERVER#202#") + to_string(playerType) + m_clients[p_id].playerName;
             sendAll(np, p_id);
         }
    }
    else
    {
	    cout << endl << "RECEIVED (parse) " << p_message << endl;
        NetPackage np;
        np.message = to_string(m_clients[p_id].playerType) + string("#") + p_message;
        sendAll(np, p_id);
    }
}
