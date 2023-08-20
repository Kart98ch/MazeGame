#pragma once
#include "Actor.h"

class Player;
class Level;

class Weapon :
    public Actor
{
    static constexpr unsigned char kWeapon = 168;

public:
    Weapon(int x, int y) :Actor(x, y) {}
    void Draw() const override;

    bool OnCollide(Player* player, int newX, int newY, const Level& m_level);
};

