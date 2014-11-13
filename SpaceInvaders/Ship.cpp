
#include "Ship.h"
#include "Definitions.h"
#include <SDL_image.h>
#include <cmath>

Ship::Ship(float x, float y)
: Object(x, y, Definitions::DefShipPath), m_Direction(1) // base ctor
{
    // :D
}

Ship::~Ship()
{
    // done in Object::~Object()
}

void Ship::SetDirection(int bf)
{
    m_Direction = bf;
}

bool Ship::Move(float frametime)
{
    Object::Move(m_Direction * (Definitions::DefShipSpeedX * frametime), Definitions::DefShipSinMult * std::sinf(GetPositionX()) * frametime);
    return true;
}





