#include "Goal.h"
#include "Player.h"
#include "Level.h"
#include <iostream>

void Goal::Draw() const
{
	std::cout << kGoal;
}

bool Goal::OnCollide(Player* player, int newX, int newY, const Level& m_level)
{
	player->SetPosition(newX, newY);
	m_level.GetWinCondition();
	return true;
}
