
#include "Object.h"
#include "Definitions.h"

Object::Position::Position(float x, float y)
: x(x), y(y)
{

};

Object::~Object()
{
    SDL_FreeSurface(m_Surface);
}

Object::Object(float x, float y, const std::string& path)
    : m_Position(x, y)
{
    m_Surface = IMG_Load(path.c_str());
}

unsigned int Object::GetWidth()
{
    if(!m_Surface)
        return 0;
    return m_Surface->w;
}

unsigned int Object::GetHeight()
{
    if(!m_Surface)
        return 0;
    return m_Surface->h;
}

float Object::GetPositionX()
{
    return m_Position.x;
}

float Object::GetPositionY()
{
    return m_Position.y;
}

void Object::Move(float x, float y)
{
    m_Position.x += x;
    m_Position.y += y;
}

void Object::Render(SDL_Surface* screen)
{
    SDL_Rect pos = {m_Position.x, m_Position.y, 0, 0};
    SDL_BlitSurface(m_Surface, NULL, screen, &pos);
}