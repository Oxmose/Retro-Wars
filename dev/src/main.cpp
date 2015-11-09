#include <exception>

#include "GameEngine/GameEngine.h"


using namespace std;
using namespace nsGameEngine;

int main(int argc, char** argv)
{
	try
	{
		GameEngine gameEngine(800, 600, "Test SFML");
		gameEngine.init();
	}
	catch(exception &e)
	{
	}
} // main()
