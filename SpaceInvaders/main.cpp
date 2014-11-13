
/*
#ifdef _WIN32
    #undef main
#endif
*/

#include "Game.h"
#include "Definitions.h"
#include <iostream>
#include <windows.h>

int main(int argc, char *argv[])
{
    Definitions::ReadConfigurationFile("SpaceInvaders.ini");
    Game MyGame;
    MyGame.Run();
    return 0;
	
}