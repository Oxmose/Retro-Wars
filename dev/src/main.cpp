#include <exception>

#include "GameEngine/GameEngine.h"


using namespace std;
using namespace nsGameEngine;

int main(int argc, char** argv)
{
	try
	{
		GameEngine gameEngine(30*16, 20*16, "Retro Wars", "first-map.tmx", RED);
		gameEngine.frame();
	}
	catch(exception &e)
	{
	}
} // main()
