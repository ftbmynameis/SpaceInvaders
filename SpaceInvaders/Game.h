
#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Ship.h"
#include "Shot.h"

#include <list>
#include <vector>
#include <SDL.h>
#include <SDL_TTF.h>

class Game
{
public:
    // Methoden (pub)
    Game();
    ~Game();
    
    SDL_Surface* GetVideoSurface();

    bool Run();
    void CreateShot(float x, float y);

private:
    // Methoden (priv)
    void SpawnField();
    bool Move(float frametime);
    void Render();
    void Update();
    int GetShipCount();
    void ClearShots();
    void AlienShot();
    // Attribute
    std::vector<std::vector<Ship*> > m_Targets;
    SDL_Surface*    m_Screen;
    Player          m_Player;
    SDL_Event       m_Event;
    float   m_Time;
    bool    m_ShipDirection;
    float m_DirCheck;
    float m_DirLeftBorder;
    float m_DirRightBorder;
    float m_CenterAverage;
    std::list<Shot*> m_Shots;
    unsigned int m_ShipCount;
    float m_LastShotBack;
    TTF_Font* m_Font;
	int m_MouseX;
	int m_MouseY;
	int m_Level;
	int m_Points;

};


#endif