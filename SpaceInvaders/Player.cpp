
#include "Player.h"
#include "Game.h"
#include "Definitions.h"
#include <windows.h>

Player::Player(Game* game)
: Object((Definitions::DefScreenW - Definitions::DefPlayerShipW) / 2, Definitions::DefScreenH - Definitions::DefPlayerShipH, Definitions::DefPlayerPath),
m_Dead(false), m_Game(game), m_LastShot(0.0f), m_Lives(Definitions::DefStartLives), m_IsInvulnerable(false), m_TimeStamp(3.0f)
{

}

Player::~Player()
{
    // blub! A non-senseless msg here!!!!!!!
}

bool Player::Move(float frametime)
{
    if(GetAsyncKeyState(VK_LEFT))
    {
        m_Position.x -= Definitions::DefPlayerSpeed * frametime;
    }
    
    if(GetAsyncKeyState(VK_RIGHT))
    {
        m_Position.x += Definitions::DefPlayerSpeed * frametime;
    }

    if(GetAsyncKeyState(VK_SPACE))
    {
        if(((SDL_GetTicks() - m_LastShot) / 1000) > Definitions::DefShotReloadDelay)
        {
            float x = m_Position.x + (Definitions::DefPlayerShipW - Definitions::DefShotW) / 2;
            m_Game->CreateShot(x, m_Position.y);
            m_LastShot = SDL_GetTicks();
        }
    }

    if(m_Position.x <= 0)
        m_Position.x = 0;
    else if((m_Position.x + Definitions::DefPlayerShipW) > Definitions::DefScreenW)
        m_Position.x = Definitions::DefScreenW - Definitions::DefPlayerShipW;

	if(m_IsInvulnerable)
	{
		m_TimeStamp -= frametime;
		if(m_TimeStamp <= 0)
		{
			m_IsInvulnerable = false;
		}
	}
    
    return true;
}

void Player::TriggerHit()
{
    if(m_Lives <= 0)
    {
        m_Dead = true;
        return;
    }
	 m_IsInvulnerable = true;
	 m_TimeStamp = 3.0f;
    // Leben - 1
    m_Lives--;
}

bool Player::IsDefeated()
{
    return m_Dead;
}

unsigned short Player::GetLives()
{
    return m_Lives;
}

bool Player::IsInvulnerable()
{
	return m_IsInvulnerable;
}