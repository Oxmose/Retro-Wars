#include <exception>

#include "GameEngine/GameEngine.h"
#include "NetEngine/NetEngine.h"
#include "MapEngine/MapEngine.h"

using namespace std;
using namespace nsGameEngine;
using namespace nsMapEngine;
using namespace nsNetEngine;

int Unit::m_lastId = 0;

unsigned int rand_interval(unsigned int min, unsigned int max)
{
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

int main(int argc, char** argv)
{
    try
    {  
	string address = "127.0.0.1"; 
        MapEngine mapEngine("first-map.tmx");
        cout << "Loaded map : " << mapEngine.getPlayers().size() << " players." <<endl;
        NetEngine netEngine("127.0.0.1", 6010);
	PLAYER_TYPE type = RED;
	netEngine.setIsServer(true);
	if (argc > 1)
	{
		type = BLUE;
		netEngine.setIsServer(false);
	}
	
        if (netEngine.launch("okok", type, &mapEngine))
        {
            cout << "Loaded server on 127.0.0.1:5000.\nLoaded client : " << "Alexy" << " is " << type << endl;
            GameEngine gameEngine(30*16, 20*16 + 90, "Retro Wars", &mapEngine, type, &netEngine);
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

