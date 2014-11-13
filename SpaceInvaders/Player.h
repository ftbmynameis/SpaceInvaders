
#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include "Shot.h"

class Game;

class Player : public Object
{
public:
    using Object::Move;
    // Methoden (pub)
    Player(Game* game);
    ~Player();

	bool IsInvulnerable();
    bool Move(float frametime);
    void TriggerHit();
    bool IsDefeated();
    unsigned short GetLives();
private:
    // Methoden (priv)

    // Attribute
    unsigned short m_Points;
    unsigned short m_Lives;
    float m_LastShot;
    bool m_Dead;
    Game* m_Game;

	bool m_IsInvulnerable;
	float m_TimeStamp;
    

};


#endif