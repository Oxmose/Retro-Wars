#include <iostream>
#include "NetEngine/Server.h"

using namespace std;
using namespace nsNetEngine;

int main(int argc, char** argv)
{
	Server server("127.0.0.1", 5000);
	cout << "Attente" << endl;
	server.launch();
	cout << "Entering loop" << endl;
	int i = 0;	
	cin >> i;
	/*if (argv[1] == "-h")
	{
		NetEngine netEngine(127.0.0.1, 5000, true);
		netEngine.launch();
	}
	else
	{
		NetEngine netEngine(127.0.0.1, 5000, false);
		netEngine.launch();
	}
	*/
	return 0;
}
