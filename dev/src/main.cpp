#include <iostream>
#include "NetEngine/NetEngine.h"

using namespace std;
using namespace nsNetEngine;

int main(int argc, char** argv)
{
    try
    {
        NetEngine netEngine("127.0.0.1", 5000);
	    if (argc == 2 && string(argv[1]) == "-h")
	    {
	        netEngine.setIsServer(true);
		    netEngine.launch("Oxmose", "mousa", NEUTRAL);
	    }
	    else
	    {
		    netEngine.setIsServer(false);
		    netEngine.launch("Oxmose", "NONE", NEUTRAL);
	    }
	    while(true);
	    return 0;
	}
	catch(const NetException &Exc)
	{
	    cerr << Exc.what() << endl;
	}
	catch(...)
	{
	    cerr << "Unknown exception" << endl;
	}
}
