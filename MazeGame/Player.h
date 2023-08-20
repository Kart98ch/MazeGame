#pragma once
#include "Actor.h"

class Player :
    public Actor
{
    static constexpr unsigned char kCursor = 164;
    static constexpr int kLeftArrow = 75;
    static constexpr int kRightArrow = 77;
    static constexpr int kUpArrow = 72;
    static constexpr int kDownArrow = 80;

private:
    int m_lives = 3;
    int m_weaponCount = 0;
    int m_score = 0;
    
    int m_faceX = 0;
    int m_faceY = 0;

    int m_XDirection = 1;
    int m_YDirection = 0;

    
public:
    Player() = default;
    Player(int x, int y) :Actor(x, y) {}

    int GetLives() const { return m_lives; }
    void LoseLife() { m_lives--; }
    void Draw() const override;

    void GetWeapon() { m_weaponCount++; }
    void LoseWeapon() { m_weaponCount--; }
    int GetWeaponCount() const { return m_weaponCount; }

    void IncreaseScore() { m_score++; }
    int GetScore() const { return m_score; }

    int GetXDirection() const { return m_faceX; }
    int GetYDirection() const { return m_faceY; }
    void SetXDirection(int x) { m_faceX = x; }
    void SetYDirection(int y) {m_faceY = y; }
    void ResetXDirection() { m_faceX = 0; }
    void ResetYDirection() { m_faceY = 0; }
    void UpdateDirection(int arrowInput);
};

