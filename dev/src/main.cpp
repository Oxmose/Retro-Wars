// STD LIBS
#include <exception>

// INCLUDES FROM PROJECT
#include "GameEngine/GameEngine.h"
#include "NetEngine/NetEngine.h"
#include "MapEngine/MapEngine.h"
#include "Misc/Tools.h"

// NAMESPACE STD
using namespace std;

// PROJECT NAMESPACES
using namespace nsGameEngine;
using namespace nsMapEngine;
using namespace nsNetEngine;
using namespace nsTools;

// Static UniqID init
int Unit::m_lastId = 0;

int main(int argc, char** argv)
{
    try
    {  
        // IP / PORT OF SERVER
        string serverAddress = "127.0.0.1";
        unsigned int serverPort = 5000;

        // IS HOST SETTING
        bool isServer = true;

        // TYPE OF PLAYER
        PLAYER_TYPE playerType = RED;

        // Parameters were added
        if(argc == 1)
        {
            cerr << "\x1b[32;1mWrong command, use \"" << argv[0] << " -help\" to get help.\x1b[0m" << endl;
            return 1;
        }
        else if(argc == 2)
        {
            //if debug run
            if(string(argv[1]).compare("-debug") == 0)
            {
                playerType = BLUE;
                isServer = false;
            }
            //if normal lauch
            else if(string(argv[1]).compare("-help") == 0)
            {
                cout << "Usage : " << endl;
                cout << "\tRun as host : \"" << argv[0] << " <port_of_server>\"" << endl;
                cout << "\tRun as client : \"" << argv[0] << " <ipv4_of_server> <port_of_server>\"" << endl << endl;
                return 0;    
            }
            else if(stoi(argv[1]) > 1024 && stoi(argv[1]) < 65000)
            {
                serverPort = stoi(argv[1]);
            }
            else
            {
                cerr << "\x1b[32;1mWrong command, use \"" << argv[0] << " -help\" to get help.\x1b[0m" << endl;
                return 1;
            }
        }
        else if(argc == 3)
        {
            
        // In this case not server
            isServer = false;
            playerType = BLUE;

            if(validateIP(argv[1]))
                serverAddress = argv[1];
            else
            {
                cerr << "\x1b[31;1mWrong ip address, use \"" << argv[0] << " -help\" to get help.\x1b[0m" << endl;
                return 1;
            }
            if(isNumber(argv[2]) && stoi(argv[2]) > 1024 && stoi(argv[2]) < 65000)
                serverPort = stoi(argv[2]);
            else
            {
                cerr << "\x1b[31;1mWrong port, use \"" << argv[0] << " -help\" to get help.\x1b[0m" << endl;
                return 1;
            }
        }
        else
        {
            cerr << "\x1b[32;1mWrong command, use \"" << argv[0] << " -help\" to get help.\x1b[0m" << endl;
            return 1;
        }    

        // Load NETENGINE
        NetEngine netEngine(serverAddress, serverPort);            
        netEngine.setIsServer(isServer);

        // If is server, load map first
        if(isServer)
        {
            // Load MAP
            MapEngine mapEngine("first-map.tmx");
            cout << "Loaded map : " << mapEngine.getPlayers().size() << " players." <<endl;

            // Launch NETENGINE
            if (netEngine.launch("PLAYER" + to_string(playerType), playerType, &mapEngine))
            {
                cout << "Loaded server on 127.0.0.1:" << serverPort << endl;
          
                // Load GAMEENGINE
                GameEngine gameEngine(30*16, 20*16 + 90, "Retro Wars", &mapEngine, playerType, &netEngine);
                netEngine.setNotifier(&gameEngine);
                gameEngine.frame();
                // ON ERROR
            }
            else
            {
                cout << "\x1b[32;1mPlease make sure that : " << endl << "\t -The server is launched." <<
                                                  endl << "\t -If hosting, your router/NAT is correctly configured." <<
                                                  endl << "\t -If hosting, your system is not blocking used port." <<
                                                  endl << "\t -You have access to the network." <<
                                                  endl << "Then restart the game." << endl << "\x1b[0m";    
            }
        }
        else
        {
            // Launch NETENGINE
            if (netEngine.launch("PLAYER" + to_string(playerType), playerType))
            {
                // Load MAP
                MapEngine mapEngine(netEngine.getMapName());
            
                if(mapEngine.getHash() != netEngine.getMapHash())
                {
                    cout << "Map file is corrupted or not corresponding." << endl;
                    return 0;
                }                

                cout << "Loaded map : " << mapEngine.getPlayers().size() << " players." <<endl;
          
                // Load GAMEENGINE
                GameEngine gameEngine(30*16, 20*16 + 90, "Retro Wars", &mapEngine, playerType, &netEngine);
                netEngine.setNotifier(&gameEngine);
                gameEngine.frame();
            }
            else
            {
                // ON ERROR
                cout << "\x1b[32;1mPlease make sure that : " << endl << "\t -The server is launched." <<
                                                  endl << "\t -If hosting, your router/NAT is correctly configured." <<
                                                  endl << "\t -If hosting, your system is not blocking used port." <<
                                                  endl << "\t -You have access to the network." <<
                                                  endl << "Then restart the game." << endl << "\x1b[0m";    
            }

        }       
    }
    catch(exception &e)
    {
        cerr << "[EXC] " << e.what() << endl;
    }
    catch(...)
    {
        cerr << "UNKNOW ERROR, please contact developers (and do not expect replay from them)." << endl;
    }

    return 0;    
} // main()

