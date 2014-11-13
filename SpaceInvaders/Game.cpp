
#include "Game.h"
#include "Definitions.h"
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

Game::Game()
: m_Targets(Definitions::DefShipCountX, std::vector<Ship*>(Definitions::DefShipCountY)), m_Player(this), m_Time(0), m_ShipDirection(true), m_DirCheck(0.0f), m_CenterAverage(0.0f),
m_LastShotBack(0.0f), m_MouseX(0), m_MouseY(0), m_Level(0), m_Points(0)
{
    // Init SDL
    SDL_Init(SDL_INIT_VIDEO);

    if(!TTF_WasInit())
		TTF_Init();
    
    // Create Window
    Uint32 Format = Definitions::DefFullScreen? SDL_DOUBLEBUF | SDL_FULLSCREEN : SDL_DOUBLEBUF;
    m_Screen = SDL_SetVideoMode(Definitions::DefScreenW, Definitions::DefScreenH, 32, Format);

    m_Font = TTF_OpenFont("cour.ttf", 20);

    srand(SDL_GetTicks());
    
}

Game::~Game()
{
    // Aliens weglöschen
    for(unsigned int x = 0; x < Definitions::DefShipCountX; ++x)
    {
        for(unsigned int y = 0; y < Definitions::DefShipCountY; ++y)
        {
            if(m_Targets[x][y])
                delete m_Targets[x][y];
        }
    }

    
    // verbleibende Schuesse weglöschen
    ClearShots();

    // close the font
    TTF_CloseFont(m_Font);
    // quit SDL Font:
    TTF_Quit();
    
    // SDL beenden
    SDL_Quit();
}

SDL_Surface* Game::GetVideoSurface()
{
    return m_Screen;
}


bool Game::Run()
{
    bool Run = true;
    float FPS = 0.0f;
    float F1  = 0.0f;
    
    // game instances:
    
    SpawnField();
    while(Run)
    {
        while(SDL_PollEvent(&m_Event))
        {
            switch(m_Event.type)
            {
            case SDL_QUIT:
            {
                Run = false;
                break;
            }
            case SDL_KEYDOWN:
            {
                // exit if ESCAPE is pressed
                if(m_Event.key.keysym.sym == SDLK_ESCAPE)
                {
                    Run = false;
                }
                break;
            } 
			case SDL_MOUSEMOTION:
			{
				m_MouseX = m_Event.motion.x;
				m_MouseY = m_Event.motion.y;
				break;
			}
            default: {break;}
            }
        }
        if(!Run)
        {
            break;
        }
        // Berechnen der Zeit seit dem vergangenen Frame zum sicherstellen, dass
        // das Spiel auf allen PCs gleich schnell läuft!
        F1 = static_cast<float>(SDL_GetTicks());
        
        // Hier Move und Render ausführen!
        if(!Move(FPS)) 
        {
            Run = false;
        }
        Render();

        F1 = static_cast<float>(SDL_GetTicks()) - F1;
        FPS = F1 / 1000.0f; // In Sekunden

    }
	return false;
}

bool Game::Move(float frametime)
{
    

    for(unsigned int x = 0; x < Definitions::DefShipCountX; ++x)
    {
        for(unsigned int y = 0; y < Definitions::DefShipCountY; ++y)
        {
            if(m_Targets[x][y])
            {
                m_Targets[x][y]->SetDirection(m_ShipDirection ? 1 : (-1));
                m_Targets[x][y]->Move(frametime);
            }
        }
    }
    
    if(m_ShipDirection)
    {
        m_DirCheck += Definitions::DefShipSpeedX * frametime;
    }
    else
    {
        m_DirCheck += Definitions::DefShipSpeedX * frametime * (-1);
    }

    if(m_DirCheck - m_CenterAverage < m_DirLeftBorder)
    {
        m_ShipDirection = true;
    }
    else if(m_DirCheck + m_CenterAverage > m_DirRightBorder)
    {
        m_ShipDirection = false;
    }
    
    // Shot movement
    std::list<Shot*>::iterator it = m_Shots.begin();
    bool hitplayer = false;
    for( ; it != m_Shots.end(); )
    {
        (*it)->Move(frametime);
        if((*it)->OutOfMap())
        {
            delete (*it);
            it = m_Shots.erase(it);
        }
        else
        {   
            bool hit = false;
            // Kollisions überprüfung:
            for(unsigned int x = 0; x < Definitions::DefShipCountX; ++x)
            {
                for(unsigned int y = 0; y < Definitions::DefShipCountY; ++y)
                {
                    if(m_Targets[x][y])
                    {
                        
                        if((*it)->GetPositionY() < m_Targets[x][y]->GetPositionY() + m_Targets[x][y]->GetHeight() && 
                           (*it)->GetPositionY() + (*it)->GetHeight() > m_Targets[x][y]->GetPositionY() &&
                           (*it)->GetPositionX() < m_Targets[x][y]->GetPositionX() + m_Targets[x][y]->GetWidth() && 
                           (*it)->GetPositionX() + (*it)->GetWidth() > m_Targets[x][y]->GetPositionX())
                        {
                            // Kollision!
                            delete m_Targets[x][y];
                            m_Targets[x][y] = 0;
                            --m_ShipCount;
							m_Points += 50;
                            hit = true;
                            break;
                        }
                        
                    }
                }
                if(hit)
                    break;
            }

			if(!m_Player.IsInvulnerable())
			{
            if((*it)->GetPositionY() < m_Player.GetPositionY() + m_Player.GetHeight() && 
               (*it)->GetPositionY() + (*it)->GetHeight() > m_Player.GetPositionY() &&
               (*it)->GetPositionX() < m_Player.GetPositionX() + m_Player.GetWidth() && 
               (*it)->GetPositionX() + (*it)->GetWidth() > m_Player.GetPositionX())
            {
                hit = true;
                hitplayer = true;
                m_Player.TriggerHit();
            }
			}

            if(hit)
            {
                delete (*it);
                it = m_Shots.erase(it);
            }
            
            // increment
            if(!hit)
                ++it;
        }
    }

    if(hitplayer)
        ClearShots();

    AlienShot();

    // Player movement
    m_Player.Move(frametime);

    if(!m_ShipCount)
        SpawnField();

    if(m_Player.IsDefeated())
        return false;

    return true;
}

void Game::Render()
{
    SDL_FillRect(m_Screen, NULL, SDL_MapRGB(SDL_GetVideoSurface()->format, 0, 0, 0));
    
    // Render Ships
    for(unsigned int x = 0; x < Definitions::DefShipCountX; ++x)
    {
        for(unsigned int y = 0; y < Definitions::DefShipCountY; ++y)
        {
            if(m_Targets[x][y])
                m_Targets[x][y]->Render(m_Screen);
        }
    }

    std::list<Shot*>::iterator it = m_Shots.begin();
    for( ; it != m_Shots.end(); ++it)
    {
        (*it)->Render(m_Screen);
    }

    
    m_Player.Render(m_Screen);
    
    // Umwandeln in string/c_str
    std::stringstream ss;
    // Lives
    SDL_Rect pos = {25, 25, 0, 0};
    SDL_Color col = {0,0,255,0};

	ss << "Level: " << m_Level << " | Leben: " << m_Player.GetLives() << " | Punkte: " << m_Points;
	SDL_Surface *text = TTF_RenderText_Solid(m_Font, ss.str().c_str(), col);
	SDL_BlitSurface(text, NULL, m_Screen, &pos);
	SDL_FreeSurface(text);

    Update();
}

void Game::SpawnField()
{
	m_Level++;
    // remove all shots!
    ClearShots();

    const int sidedistancelr = (Definitions::DefScreenW - (Definitions::DefShipW   *  Definitions::DefShipCountX 
                                                       + Definitions::DefShipDistanceX * (Definitions::DefShipCountX - 1))) / 2;
    const int sidedistancetb = (Definitions::DefScreenH - (Definitions::DefShipH  *  Definitions::DefShipCountY
                                                       + Definitions::DefShipDistanceY * (Definitions::DefShipCountY - 1))) / 2;
    
    for(unsigned int i = 0; i < Definitions::DefShipCountX; ++i)
    {
        for(unsigned int t = 0; t < Definitions::DefShipCountY; ++t)
        {
            const int x = sidedistancelr + (Definitions::DefShipW * i)
                                   + (i * Definitions::DefShipDistanceX);
            const int y = sidedistancetb + (Definitions::DefShipH * t)
                                   + (t * Definitions::DefShipDistanceY);
            m_Targets[i][t] = new Ship(x , y);
        }
    }

    m_ShipCount = Definitions::DefShipCountX * Definitions::DefShipCountY;

    //m_DirCheck = (sidedistancelr + (DefShipW * DefShipCountX) + ((DefShipCountX - 1 ) * DefShipDistanceX)) / 2;
    m_DirCheck = Definitions::DefScreenW / 2;
    m_CenterAverage = ((Definitions::DefShipW * Definitions::DefShipCountX) + ((Definitions::DefShipCountX - 1 ) * Definitions::DefShipDistanceX)) / 2;
    m_DirRightBorder = Definitions::DefScreenW - sidedistancelr;
    m_DirLeftBorder = sidedistancelr;
    m_DirLeftBorder = sidedistancelr * 0.3f;
    m_DirRightBorder = Definitions::DefScreenW - sidedistancelr * 0.3f;
    m_LastShotBack = 0.0f;

    


}

void Game::Update()
{
    SDL_Flip(m_Screen);
    SDL_UpdateRect(m_Screen, 0, 0, 0, 0);
}


void Game::CreateShot(float x, float y)
{
    m_Shots.push_back(new Shot(x, y - Definitions::DefShotH - Definitions::DefShotYOffset, 0));
}

void Game::ClearShots()
{
    std::list<Shot*>::iterator it = m_Shots.begin();
    for( ; it != m_Shots.end(); ++it)
        delete (*it);
    m_Shots.clear();
}


void Game::AlienShot()
{
    if(((SDL_GetTicks() - m_LastShotBack) / 1000) > Definitions::DefAlienShotReloadDelay - m_Level * 0.1f)
    {
        std::vector<Ship*> posshooter(Definitions::DefShipCountX);

        for(unsigned int x = 0; x < Definitions::DefShipCountX; ++x)
        {
            for(unsigned int y = 0; y < Definitions::DefShipCountY; ++y)
            {
                if(m_Targets[x][y])
                    posshooter[x] = m_Targets[x][y];
            }
        }
        int shooter = -1;
        while(shooter == -1 || posshooter[shooter] == 0)
            shooter = rand() % Definitions::DefShipCountX;

        m_Shots.push_back(new Shot(posshooter[shooter]->GetPositionX() + (Definitions::DefShipW - Definitions::DefShotW) / 2, 
                                   posshooter[shooter]->GetPositionY() + posshooter[shooter]->GetHeight() + Definitions::DefShotYOffset,
                                   1));
        
        
        m_LastShotBack = SDL_GetTicks();
    }

}



    

  