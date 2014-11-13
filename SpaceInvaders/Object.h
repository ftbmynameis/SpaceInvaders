
#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>

class Object
{
public:
    // Methoden (pub)
    Object(float x, float y, const std::string& path);
    virtual ~Object();

    unsigned int GetWidth();
    unsigned int GetHeight();

    float GetPositionX();
    float GetPositionY();
    
    void Move(float x, float y);

    virtual bool Move(float frametime) = 0;
    void Render(SDL_Surface* screen);
    
protected:
    // Struktur (prot)
    struct Position
    {
        Position(float x, float y);
        float x;
        float y;
    };

    // Methoden (prot)

    //Attribute (prot)
    Position     m_Position;
    SDL_Surface* m_Surface;

};


#endif