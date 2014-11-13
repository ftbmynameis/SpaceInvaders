
#include "Definitions.h"
#include <windows.h>
#include <iostream>
#include <sstream>
// Game
unsigned int Definitions::DefScreenW;
unsigned int Definitions::DefScreenH;
bool Definitions::DefFullScreen;

// GAme-Config
unsigned short Definitions::DefStartLives;
unsigned int Definitions::DefShipDistanceX;
unsigned int Definitions::DefShipDistanceY;
unsigned int Definitions::DefShipCountX;
unsigned int Definitions::DefShipCountY;
unsigned int Definitions::DefShipSpeedX;
unsigned int Definitions::DefShipSinMult;
unsigned int Definitions::DefShotYOffset;
float Definitions::DefShotReloadDelay;
float Definitions::DefAlienShotReloadDelay;

// Ship
unsigned int Definitions::DefShipW;  // pixel
unsigned int Definitions::DefShipH; // pixel
std::string Definitions::DefShipPath;

// Ship-Player
unsigned int Definitions::DefPlayerShipW;
unsigned int Definitions::DefPlayerShipH;
std::string Definitions::DefPlayerPath;
unsigned int Definitions::DefPlayerShotSpeed;
unsigned int Definitions::DefPlayerSpeed;

// Shot
unsigned int Definitions::DefShotW;
unsigned int Definitions::DefShotH;
std::string Definitions::DefShotPath;
unsigned int Definitions::DefShotSpeed;



void Definitions::ReadConfigurationFile(const std::string& file)
{
    // relativen pfad erstellen
    char buffer[128] = "";
    GetCurrentDirectory(128, buffer);
    std::string path(buffer);
    path = path + "\\" + file;

    // stirngstream
    std::stringstream convert;
    
    // Game
    DefScreenW    = ::GetPrivateProfileInt("Game", "ScreenWidth", 640, path.c_str());
    DefScreenH    = ::GetPrivateProfileInt("Game", "ScreenHeight", 480, path.c_str());
    DefFullScreen = ::GetPrivateProfileInt("Game", "Fullscreen", 0, path.c_str());

    // Game-Config
    DefStartLives    = ::GetPrivateProfileInt("Game-Config", "StartLives", 3, path.c_str());
    DefShipDistanceX = ::GetPrivateProfileInt("Game-Config", "ShipDistanceX", 40, path.c_str());
    DefShipDistanceY = ::GetPrivateProfileInt("Game-Config", "ShipDistanceY", 25, path.c_str());
    DefShipCountX    = ::GetPrivateProfileInt("Game-Config", "ShipCountX", 7, path.c_str());
    DefShipCountY    = ::GetPrivateProfileInt("Game-Config", "ShipCountY", 5, path.c_str());
    DefShipSpeedX    = ::GetPrivateProfileInt("Game-Config", "ShipSpeedX", 10, path.c_str());
    DefShipSinMult   = ::GetPrivateProfileInt("Game-Config", "ShipSinMult", 50, path.c_str());
    DefShotYOffset   = ::GetPrivateProfileInt("Game-Config", "ShotYOffset", 20, path.c_str());;
                    ::GetPrivateProfileString("Game-Config", "ShotReloadDelay", "0.7", buffer, 128, path.c_str());
    convert << buffer; convert >> DefShotReloadDelay; convert.clear();
                    ::GetPrivateProfileString("Game-Config", "AlienShotReloadDelay", "1.5", buffer, 128, path.c_str());
    convert << buffer; convert >> DefAlienShotReloadDelay; convert.clear();
    
    // Ship
    DefShipW =    ::GetPrivateProfileInt("Ship", "Width", 15, path.c_str());
    DefShipH =    ::GetPrivateProfileInt("Ship", "Height", 20, path.c_str());
               ::GetPrivateProfileString("Ship", "Path", "Test.jpg", buffer, 128, path.c_str());
    DefShipPath = buffer;
    
    // Player Ship
    DefPlayerShipW = ::GetPrivateProfileInt("Ship-Player", "Width", 15, path.c_str());
    DefPlayerShipH = ::GetPrivateProfileInt("Ship-Player", "Height", 20, path.c_str());
                  ::GetPrivateProfileString("Ship-Player", "Path", "Test.jpg", buffer, 128, path.c_str());
    DefPlayerPath = buffer;
    DefPlayerShotSpeed = ::GetPrivateProfileInt("Ship-Player", "ShotSpeed", 400, path.c_str());;
    DefPlayerSpeed =     ::GetPrivateProfileInt("Ship-Player", "Speed", 150, path.c_str());
    
    // Shot
    DefShotW = ::GetPrivateProfileInt("Shot", "Width", 15, path.c_str());
    DefShotH = ::GetPrivateProfileInt("Shot", "Height", 20, path.c_str());
            ::GetPrivateProfileString("Shot", "Path", "Test.jpg", buffer, 128, path.c_str());
    DefShotPath = buffer;
    DefShotSpeed = ::GetPrivateProfileInt("Shot", "Speed", 400, path.c_str());
    
};
