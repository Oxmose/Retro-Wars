#include <string>
#include <vector>
#include <array>
#include <thread>
#include <mutex>
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

#define NETSERVER nsNetEngine::Server

using namespace std;
using namespace nsTools;

NETSERVER::Server(const std::string &p_ipAddress, const unsigned int &p_port, NetEngine* p_netEngine, const vector<PLAYER_TYPE> &p_allowedPlayers)
{
    // Init
    m_ipAddress = p_ipAddress;
    m_port      = p_port;
    m_netEngine = p_netEngine; 
    m_maxPlayer = p_allowedPlayers.size();
    m_lastId    = 0;
    
    // Init and load available player tokens for the current map
    for(unsigned int i = 0 ; i < 5; ++i)
        m_availablePositions[i] = false;

    for(PLAYER_TYPE type : p_allowedPlayers)
        m_availablePositions[type] = true;

	m_connectThread = nullptr;
} // Server()

NETSERVER::~Server()
{
	// Stop waiting for clients and listening to connected clients  
    m_waitForClients = false;
    m_listen         = false; 

	// Close the tcp listener
    m_listener.close();

    m_clientListMutex.unlock();
    // Disconnect all clients
    disconnectClients();   

    // Detach and delete the listener thread
    if(m_connectThread != nullptr)
	{
		m_connectThread->join();   
    	delete m_connectThread;
	}
} // ~Server()

bool NETSERVER::launch()
{    
    // Bind the socket to the port
    if(m_listener.listen(m_port) != sf::Socket::Done)
    {
        cerr << "[SERVER][ERROR] Can't bind to port " << m_port << ". Ending." << endl;
        return false;
    }
    else
    {
        // Enable listening
        m_waitForClients = true;
        m_listen = true;

        // Start listener thread
        m_connectThread = new thread(&Server::connectClient, this);
		return true;
    }
} // launch()

void NETSERVER::send(const NetPackage &p_package, const unsigned int &p_clientId, const bool &p_split)
{
    // If it is required to split the message
    if(p_split)
    {
        char* data;

        // Define EOL
        string toSend = p_package.message + "|||";

        // Create NetPackage and set message
        NetPackage np;
        np.message = toSend;
    
        // Split message
        vector<NetPackage> splitMessage = splitMessages(np);
        
        // Send each messages
        for(NetPackage NetP : splitMessage)
        {
            NetP.message = to_string(NetP.message.size()) + "/" + NetP.message;
            data = (char*)NetP.message.c_str();
            // send
            m_clientListMutex.lock();
            if(m_clients[p_clientId].socket->send(data, NetP.message.size()) != sf::Socket::Done)
            {
                cerr << "[SERVER][ERROR] Message not sent." << endl;
            }
            m_clientListMutex.unlock();
        }
    }
    else
    {
        char* data;
        string toSend = to_string(p_package.message.size()) + "/" + p_package.message;
        data = (char*)toSend.c_str();

        // Send message
        m_clientListMutex.lock();
        if(m_clients[p_clientId].socket->send(data, toSend.size()) != sf::Socket::Done)
        {
            cerr << "[SERVER][ERROR] Message not sent." << endl;
        }
        m_clientListMutex.unlock();
    }
} // send()

void NETSERVER::connectClient()
{
    // Set accepting package
    NetPackage package;
    package.message = "200";
    
    // While listening for new clients
    while(m_waitForClients)
    {
		cout << "WAIT : " << m_waitForClients << endl;
        sf::TcpSocket* client = new sf::TcpSocket();
       	sf::Socket::Status status; 
        // Accept new client
        if((status = acceptTime(m_listener, *client)) != sf::Socket::Done)
        {
			if(!m_waitForClients)
				break;

			if(status == sf::Socket::NotReady)
				continue;

            cerr << "[SERVER][ERROR] Can't accept new client." << endl;
            delete client;
        }
        else 
        {
			if(!m_waitForClients)
				break;

            // If too much player
            if(getClientsNumber() == m_maxPlayer)
            {
                char* data;
                data = (char*)"204";

                // Send rejecting message
                if(client->send(data, 3) != sf::Socket::Done)
                {
                      cerr << "[SERVER][ERROR] Message not sent." << endl;
                }
                delete client;
            }
            else
            {           
                // Create the client structure
                Client clientStruct;

                // Set client structure
                clientStruct.ipAddress = client->getRemoteAddress().toString();
                clientStruct.port = client->getRemotePort();
                clientStruct.socket = client;
                clientStruct.id = m_lastId;
                clientStruct.status = false; 

                // Add client
                m_clientListMutex.lock();
                m_clients[m_lastId] = clientStruct;
                m_clientListMutex.unlock();

                // Create a new client listener thread
                thread *m_listenClientsThread  = new thread(&Server::listenClients, this, m_lastId);
                m_clientSocketListMutex.lock();
                m_listenClientsThreads[m_lastId] = m_listenClientsThread;
                m_clientSocketListMutex.unlock();

                // Send accepting message
                send(package, m_lastId, false);
                
                // Add one to the clientID
                m_lastId++;
            }
        }
    }
	cout << " OUT OF CONENCT " << endl;
} // connectClient()

void NETSERVER::listenClients(unsigned int p_id)
{
    // Get the client to listen
    m_clientListMutex.lock();
    sf::TcpSocket *client = m_clients[p_id].socket;
    m_clientListMutex.unlock();
    
    char data[256];
	size_t received = 0;
    string message("");

    // While listening to client
    while(m_listen)
    {
        // Manage client disconnection
		sf::Socket::Status status;
        if((status = receiveTime(*client, data, 256, received)) != sf::Socket::Done)
		{

			if(!m_listen)
				break;
	
			if(status == sf::Socket::NotReady)
				continue;

			
			if(m_clients.find(p_id) != m_clients.end())
           	{
               	if(sf::Socket::Disconnected == status)
               	{
                   	if(m_clients[p_id].status != false)
                   	{
                       	m_clients[p_id].status = false;
                       	disconnectClient(p_id, false); 
                   	}                                  
               	}
               
               	return;
           	}            
        }

		if (!m_listen)
			break;


		string strData = cleanMessage(string(data));

	   	// Preparse message (if message ends with ||| it has to be parsed
       	if(strData.substr(strData.size() - 3) == "|||")
       	{
           	message += strData.substr(0, strData.size() - 3);
           	parseMessage(p_id, message);
           	message = "";
       	}
       	else if (received == 3 && strData == "201")
       	{
           	// Disconnet message received
           	disconnectClient(p_id, false);
           	return;
       	}
       	else
           	message += strData;

	}

} // listenClient()

sf::Socket::Status NETSERVER::receiveTime(sf::TcpSocket &p_socket, char* p_buffer, const unsigned int p_limit, size_t &p_received)
{
	sf::SocketSelector selector;
    selector.add(p_socket);

    if (selector.wait(sf::seconds(2)))
	{
		return p_socket.receive(p_buffer, p_limit, p_received);
    }
	else
	{
		return sf::Socket::NotReady;
	}
} // receiveTime()

sf::Socket::Status NETSERVER::acceptTime(sf::TcpListener &p_listener, sf::TcpSocket &p_client)
{
	sf::SocketSelector selector;
	selector.add(p_listener);
	
	if(selector.wait(sf::seconds(0.5)))
	{
		return p_listener.accept(p_client);
	}
	else
	{
		return sf::Socket::NotReady;
	}
} // acceptTime()

void NETSERVER::sendAll(const NetPackage &p_package, const int &p_except /* = -1 */)
{        
    m_clientListMutex.lock();
    // For all client, send the message
    for(pair<unsigned int, Client> client : m_clients)
    {
        // if a clients should not get a message he will be rejected
        if(client.first != p_except)
        {
            m_clientListMutex.unlock();
            send(p_package, client.first, true);
            m_clientListMutex.lock();
        }
    }
    m_clientListMutex.unlock();
} // sendAll()

void NETSERVER::disconnectClients()
{
    m_clientListMutex.lock();
    for(pair<unsigned int, Client>  client : m_clients)
    {
        m_clientListMutex.unlock();
        disconnectClient(client.first, false);
        m_clientListMutex.lock();
    }
    m_clients.clear();
    m_clientListMutex.unlock();
} // disconnectClients()

void NETSERVER::disconnectClient(const unsigned int &p_id, const bool &p_erase /* = true */)
{
    m_clientListMutex.lock();
    m_clientSocketListMutex.lock();
    
    // If client is not null
    if(m_clients[p_id].socket != nullptr)
    {
        // If client is supposed active
        if(m_clients[p_id].status) 
        { 
            NetPackage package;
            package.message = "201";

            m_clientListMutex.unlock();
            send(package, p_id, false);
            m_clientListMutex.lock();
        }
        
        // Disconnect client
        m_clients[p_id].status = false;
        m_clients[p_id].socket->disconnect();    
        m_listenClientsThreads[p_id]->join();
        // Delete listener and socket
        delete m_listenClientsThreads[p_id];
        delete m_clients[p_id].socket;
    }

    // Erase the client from the socket list
    if(p_erase)
    {        
        m_listenClientsThreads.erase(p_id);
    }

    m_clientSocketListMutex.unlock();
    m_clientListMutex.unlock();
} // disconnectClient()

unsigned int NETSERVER::getClientsNumber()
{
    unsigned int counter = 0;
    m_clientListMutex.lock();
    for(pair<unsigned int, Client> client : m_clients)
    {
        if(client.second.status)
            ++counter;
    }
    m_clientListMutex.unlock();
    return counter;
} // getClientNumber()

vector<nsNetEngine::Client> NETSERVER::getClients()
{   
    vector<Client> result;   
    m_clientListMutex.lock();  
    for(pair<unsigned int, Client> client : m_clients)
    {
        if(client.second.status)
            result.push_back(client.second);
    }  
    m_clientListMutex.unlock();
    return result;
} // getClients();

void NETSERVER::parseMessage(const unsigned int &p_id, const std::string &p_message)
{
	if(!m_listen)
		return;

    // Accect the client 
    m_clientListMutex.lock();
    if(m_clients[p_id].status == false)
    {
        NetPackage np;
        // Message has to be like : name#type
        // Get the type
        string tmpMessage = p_message.substr(p_message.find("#") + 1);
        unsigned int playerType = stoi(tmpMessage);
        
        if(playerType > 5 || m_availablePositions[playerType] == false)
        {
            np.message = "203";
            m_clientListMutex.unlock();
            send(np, p_id, false);
            disconnectClient(p_id);
         }
         else
         {
            // Parse the message
             m_availablePositions[playerType] = false;
             m_clients[p_id].playerType = static_cast<PLAYER_TYPE>(playerType);
             m_clients[p_id].playerName = p_message.substr(0, p_message.find("#"));
             m_clients[p_id].status = true;
             np.message = "200";
             m_clientListMutex.unlock();
             send(np, p_id, false);
	         np.message = "3::" + to_string(getClientsNumber());
             sendAll(np, p_id);
         }
    }
    else if(p_message.substr(p_message.size() - 3) == "205")
    {
        m_clientListMutex.unlock();
        NetPackage np;
	    np.message = "3::" + to_string(getClientsNumber());
        send(np, p_id, true);
    }
    else
    {
        m_clientListMutex.unlock();
        NetPackage np;
        np.message = to_string(m_clients[p_id].playerType) + string("#") + p_message;
        sendAll(np, p_id);
    }
} // parseMessage()
