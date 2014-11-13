
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// Compile Optionen, wie Screen Size ect.
#include <string>

struct Definitions
{
    
// Game
static unsigned int DefScreenW;
static unsigned int DefScreenH;
static bool DefFullScreen;

// Game-Config
static unsigned short DefStartLives;
static unsigned int DefShipDistanceX;
static unsigned int DefShipDistanceY;
static unsigned int DefShipCountX;
static unsigned int DefShipCountY;
static unsigned int DefShipSpeedX;
static unsigned int DefShipSinMult;
static unsigned int DefShotYOffset;
static float DefShotReloadDelay;
static float DefAlienShotReloadDelay;

// Ship
static unsigned int DefShipW;  // pixel
static unsigned int DefShipH; // pixel
static std::string DefShipPath;

// Ship-Player
static unsigned int DefPlayerShipW;
static unsigned int DefPlayerShipH;
static std::string DefPlayerPath;
static unsigned int DefPlayerShotSpeed;
static unsigned int DefPlayerSpeed;

// Shot
static unsigned int DefShotW;
static unsigned int DefShotH;
static std::string DefShotPath;
static unsigned int DefShotSpeed;

static void ReadConfigurationFile(const std::string& file);

};

#endif