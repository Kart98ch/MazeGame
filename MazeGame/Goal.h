#pragma once
#include "Actor.h"

class Player;
class Level;

class Goal :
    public Actor
{
    static constexpr unsigned char kGoal = 245;

public:
    Goal(int x, int y) :Actor(x,y) {}
    void Draw() const override;

    bool OnCollide(Player* player, int newX, int newY, const Level& m_level);
};

