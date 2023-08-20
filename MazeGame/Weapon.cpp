#include "Weapon.h"
#include "Player.h"
#include "Level.h"
#include <iostream>


void Weapon::Draw() const { std::cout << kWeapon; }

bool Weapon::OnCollide(Player* player, int newX, int newY, const Level& m_level)
{
	player->GetWeapon();
	SetInactive();
	player->SetPosition(newX, newY);
	return false;
}
