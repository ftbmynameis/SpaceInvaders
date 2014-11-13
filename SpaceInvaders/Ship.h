
#ifndef SHIP_H
#define SHIP_H


#include "Shot.h"
#include "Object.h"

#include <list>
#include <SDL.h>

class Ship : public Object
{
public:
    using Object::Move;
    // Methoden (pub)
    Ship(float x, float y);
    ~Ship();

    bool Move(float frametime); // real move method
    void SetDirection(int bf);

private:
    // Methoden (priv)

    // Attribute
    std::list<Shot> m_Shots;
    int m_Direction; // 1 / -1

};


#endif