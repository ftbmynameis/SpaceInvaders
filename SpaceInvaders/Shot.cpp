
#include "Shot.h"
#include "Definitions.h"


Shot::Shot(float x, float y, int dir)
: Object(x, y + Definitions::DefShotYOffset, Definitions::DefShotPath), m_Direction(dir)
{
    if(dir == 0)
    {
        m_Speed = Definitions::DefPlayerShotSpeed;
    }
    else
        m_Speed = Definitions::DefShotSpeed;
}

Shot::~Shot()
{

}

bool Shot::Move(float frametime)
{
    if(m_Direction == 0)
        m_Position.y -= m_Speed * frametime;
    else
        m_Position.y += m_Speed * frametime;

    if(OutOfMap())
        return false;

    return true;
}


bool Shot::OutOfMap()
{
    return m_Position.y + Definitions::DefShotH <= 0;
}