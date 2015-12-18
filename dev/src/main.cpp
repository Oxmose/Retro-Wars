#include <exception>

#include "GameEngine/GameEngine.h"
#include "NetEngine/NetEngine.h"
#include "MapEngine/MapEngine.h"

using namespace std;
using namespace nsGameEngine;
using namespace nsMapEngine;
using namespace nsNetEngine;

int Unit::m_lastId = 0;

int main(int argc, char** argv)
{
    try
    {  
	  
        MapEngine mapEngine("first-map.tmx");
        cout << "Loaded map : " << mapEngine.getPlayers().size() << " players." <<endl;
        NetEngine netEngine("127.0.0.1", 5003);
	PLAYER_TYPE type = RED;
	if (argc > 1)
	{           
		netEngine.setIsServer(true);
		type = BLUE;
	}
	
        if (netEngine.launch("okok", type, &mapEngine))
        {
            cout << "Loaded server on 127.0.0.1:5000.\nLoaded client : " << "Alexy" << " is " << RED << endl;
            GameEngine gameEngine(30*16, 20*16 + 75, "Retro Wars", &mapEngine, RED, &netEngine);
            netEngine.setNotifier(&gameEngine);
            cout << "Loaded game engine" << endl;
            gameEngine.frame();
        }       
    }
    catch(exception &e)
    {
        cerr << "[EXC] " << e.what() << endl;
    }
} // main()

