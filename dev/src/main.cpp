#include <exception>

#include "GameEngine/GameEngine.h"
#include "NetEngine/NetEngine.h"
#include "MapEngine/MapEngine.h"

using namespace std;
using namespace nsGameEngine;
using namespace nsMapEngine;
using namespace nsNetEngine;

int main(int argc, char** argv)
{
	try
	{
        if (argc == 2)
        {
		    MapEngine mapEngine("test.tmx");
            cout << "Loaded map : " << mapEngine.getPlayers().size() << " players." <<endl;
            NetEngine netEngine("127.0.0.1", 5000);
            netEngine.launch("Alexy", RED, &mapEngine);
            cout << "Loaded server on 127.0.0.1:5000.\nLoaded client : " << "Alexy" << " is " << RED << endl;
        }

		GameEngine gameEngine(30*16, 20*16, "Retro Wars", "first-map.tmx", RED);
		gameEngine.frame();
        cout << "Loaded game engine" << endl;
	}
	catch(exception &e)
	{
	}
} // main()

