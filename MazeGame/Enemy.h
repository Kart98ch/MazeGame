#pragma once
#include "Actor.h"

class Player;

class Enemy :
    public Actor
{
    int m_xDirection;
    int m_yDirection;
    int m_moveLimit;
    int m_xDeviation = 0;
    int m_yDeviation = 0;

    static constexpr unsigned char kEnemy = 184;

public:
    Enemy(int x, int y, int xDirection, int yDirection, int moveLimit) 
        :Actor(x, y), m_xDirection(xDirection), m_yDirection(yDirection), m_moveLimit(moveLimit) 
    {
        Init();
    }

    void Init();
    void Draw() const override;
    void Update(const Level &level) override;

    bool OnCollide(Player* player, int newX, int newY, const Level& m_level);
    void OnHit() { SetInactive(); }

};

