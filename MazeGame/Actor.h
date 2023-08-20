#pragma once
#include "Point.h"

class Player;
class Level;

class Actor
{
protected:
	Point m_pPosition;
	bool m_Active = true;


public:
	Actor(int x, int y):m_pPosition(x, y) {}
	virtual ~Actor() {}

	int GetXPosition() const { return m_pPosition.m_X; }
	int GetYPosition() const { return m_pPosition.m_Y; }
	void SetPosition(int x, int y) { m_pPosition.m_X = x; m_pPosition.m_Y = y; }
	bool IsActive() const { return m_Active; }
	void SetInactive() { m_Active = false; }

	virtual void Draw() const = 0;
	virtual void Update(const Level &level) {}
	virtual bool OnCollide(Player* player, int newX, int newY, const Level& m_level) { return false; }
	virtual void OnHit() {}

};

