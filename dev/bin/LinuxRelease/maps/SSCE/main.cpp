#include <string>
#include <vector>
#include <thread>
#include <iostream>
#include <atomic>
#include <map>
#include <array>
#include <utility>
#include <SFML/Network.hpp>


typedef struct NetPackage NetPackage; 
struct NetPackage
{
	std::string message;
};

typedef struct Client Client;
struct Client
{
    bool		    status;
    std::string     ipAddress;
    unsigned int    port;
    unsigned int	id;
    sf::TcpSocket	*socket;
};

class Server
{
    public:
       
        Server(const std::string &p_ipAddress, const unsigned int &p_port);
        ~Server();

        void launch();
        
        void disconnectClient(const unsigned int &p_id, const bool &p_notErase = true);

        void send(const NetPackage &p_package, const unsigned int &p_clientId);
        void sendAll(const NetPackage &p_package);
		
	private:
        void connectClient();
        void disconnectClients();
        void listenClients(unsigned int p_id);
        void parseMessage(const unsigned int &p_id, const std::string &p_message);

		std::string 	                        m_ipAddress;
		unsigned int 	                        m_port;

        std::map<unsigned int, Client>          m_clients;
        sf::TcpListener                         m_listener; 

        std::thread*                            m_connectThread; 
        std::map<unsigned int, std::thread*>    m_listenClientsThreads; 

        std::atomic<bool>                       m_waitForClients;
        std::atomic<bool>                       m_listen;     
        
        unsigned int                            m_lastId;
        
};


Server::Server(const std::string &p_ipAddress, const unsigned int &p_port)
{
    m_ipAddress = p_ipAddress;
    m_port      = p_port;
    m_lastId    = 0;
}

void Server::launch() 
{    
    if (m_listener.listen(m_port) != sf::Socket::Done)
    {
        std::cout << "Can't bind the socket" << std::endl;
    }
    m_waitForClients = true;
    m_listen = true;
    m_connectThread = new std::thread(&Server::connectClient, this);
    
}

void Server::send(const NetPackage &p_package, const unsigned int &p_clientId)
{
    char* data;
    data = (char*)p_package.message.c_str();
    m_clients[p_clientId].socket->send(data, p_package.message.size());
}

void Server::sendAll(const NetPackage &p_package)
{        
    for (auto it = m_clients.begin() ; it != m_clients.end() ; ++it)
    {
    	printf("AA");
        send(p_package, it->first);
    }
}

void Server::parseMessage(const unsigned int &p_id, const std::string &p_message)
{
    // Accpet the client
    if (m_clients[p_id].status == false)
    {
        NetPackage np;
        // Message has to be like : name#type
        // Get the type
        std::string tmpMessage = p_message.substr(p_message.find("#") + 1);
        unsigned int playerType = stoi(tmpMessage);
        
        np.message = "200";
        send(np, p_id);    
    }
}

void Server::listenClients(unsigned int p_id)
{
    sf::TcpSocket *client = m_clients[p_id].socket;
    printf("HHIHI");
    
    char data[256];
    size_t received = 0;
    std::string message("");
    while(m_listen)
    {
    	printf("HOHO");
        sf::Socket::Status status;
        if ((status = client->receive(data, 256, received)) != sf::Socket::Done)
        {
            if (m_clients.find(p_id) != m_clients.end())
            {
                if (sf::Socket::Disconnected == status)
                {
                    m_clients[p_id].status = false;
                    disconnectClient(p_id);               
                }
            } 
            std::cout << "Can't receive from client with IP " + m_clients[p_id].ipAddress << std::endl;  
        }
        std::string strData = std::string(data);
        if (strData.substr(strData.size() - 3) == "100")
        {
            message += strData.substr(0, strData.size() - 3);
            parseMessage(p_id, message);
        }
        else if (received == 3 && strData == "201")
        {
            m_clients[p_id].status = false;
            disconnectClient(p_id);
            return;
        }
        else
            message += std::string(data);
    }
}

void Server::connectClient()
{
    NetPackage package;
    package.message = "202";

   while(m_waitForClients)
    {
    	sf::TcpSocket client;
        if (m_listener.accept(client) != sf::Socket::Done)
        {
            printf(")");
        }
        else 
        {
            
            printf("Quelqu'un se connecte lol!!!!\n");
            sendAll(package);
            
            std::thread *m_listenClientsThread  = new std::thread(&Server::listenClients, this, m_lastId);
            /*printf("o\n");
            m_listenClientsThreads[m_lastId] = m_listenClientsThread;

            Client clientStruct;
            clientStruct.status = false; 
            clientStruct.ipAddress = client->getRemoteAddress().toString();
            clientStruct.port = client->getRemotePort();
            clientStruct.id = m_lastId;
            clientStruct.socket = client;
            
            m_clients[m_lastId] = clientStruct;
            printf("%s %d \n", m_clients[m_lastId].ipAddress.c_str(), m_clients[m_lastId].id);
            package.message = "200";
            send(package, m_lastId);
            package.message = "202";
            */
            m_lastId++;
            
        }
    }
    printf("b");
}

void Server::disconnectClient(const unsigned int &p_id, const bool &p_erase /* = true */)
{
    if (m_clients[p_id].status) 
    { 
        NetPackage package;
        package.message = "201";
        
        send(package, p_id);
    }
    
    m_clients[p_id].socket->disconnect();    
    m_listenClientsThreads[p_id]->detach();
    
    delete m_listenClientsThreads[p_id];
    delete m_clients[p_id].socket;
    
    m_listenClientsThreads.erase(p_id);

    if (p_erase)
    	m_clients.erase(p_id);
}


void Server::disconnectClients()
{
    for (std::pair<unsigned int, Client>  client : m_clients)
    {
        disconnectClient(client.first, false);
    }
    m_clients.clear();
}

Server::~Server()
{
    disconnectClients();  
    
    m_listen = false;        
    m_waitForClients = false;
    
    m_listener.close();
    m_connectThread->detach();  
    
    delete m_connectThread;
}


int main()
{
	std::string ip = "127.0.0.1";
	int port = 5002;

	Server *server;
	server = new Server(ip, port);
	server->launch();


	sf::TcpSocket   socket;
	socket.connect(ip, port);

	int a;
	std::cin >> a;
	//char data[256];
	//size_t received;

	//socket.receive(data, 256, received);

	delete server;
}