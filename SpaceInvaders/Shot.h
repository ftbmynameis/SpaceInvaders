
#ifndef SHOT_H
#define SHOT_H

#include "Object.h"
#include <list>
#include <SDL.h>

class Shot : public Object
{
public:
    // Methoden (pub)
    Shot(float x, float y, int dir);
    ~Shot();

    bool Move(float frametime);

    bool OutOfMap();
    


private:
    // strukturen (priv)
    
    // Methoden (priv)

    // Attribute
    int m_Direction;
    int m_Speed;
    

};


#endif