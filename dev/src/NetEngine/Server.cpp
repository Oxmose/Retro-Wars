#include <string>
#include <vector>
#include <thread>
#include <iostream>

#include <SFML/Network.hpp>

#include "../Misc/Misc.h"
#include "Server.h"
#include "Structures.h"

#define NETSERVER nsNetEngine::Server

using namespace std;

NETSERVER::Server(const std::string &p_ipAddress, const unsigned int &p_port) noexcept
{
    m_ipAddress = p_ipAddress;
    m_port      = p_port; 
    m_waitForClients = true;
    m_listen = true;
}

NETSERVER::~Server() noexcept
{
    disconnectClients();  
    
    m_waitForClients = false;
    m_listen = false;

    m_connectThread->detach();
    m_listenClientsThread->detach();
    
    delete m_connectThread;
    delete m_listenClientsThread;
    
    for (unsigned int i = 0; i < m_clients.size(); ++i)
    {
        delete m_clients[i];
    }
}

void NETSERVER::launch()
{
    // lie l'écouteur à un port
    if (m_listener.listen(m_port) != sf::Socket::Done)
    {
        throw (string("Error binding the socket to the port"));
    }

    m_connectThread = new thread(&Server::connectClient, this);
    m_listenClientsThread  = new thread(&Server::listenClients, this);
}

void NETSERVER::listenClients()
{
    size_t received = 0;
    while(m_listen)
    {
        for (unsigned int i = 0; i < m_clients.size(); ++i)
        {
            char data[100];
            

            // socket TCP:
            if (m_clients[i]->receive(data, 100, received) != sf::Socket::Done)
            {
                // erreur...
            }
            if (received != 0)
            {
                cout << "Received " << received << " bytes : " << data << endl;
                received = 0;
            }
        }
    }
}

void NETSERVER::send(const NetPackage &p_package, const unsigned int &p_clientId)
{
    char* data;
    data = (char*)p_package.message.c_str();
    m_clients[p_clientId]->send(data, p_package.message.size());
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
            // erreur...
        }
                
        for (unsigned int i = 0; i < m_clients.size(); ++i)
        {
            send(package, i);
        }
        
        client->setBlocking(false);
        m_clients.push_back(client);
    }
}

void NETSERVER::disconnectClients()
{
    NetPackage package;
    package.message = "201";
        
    for (unsigned int i = 0; i < m_clients.size(); ++i)
    {
        send(package, i);
        m_clients[i]->disconnect();
    }
}

