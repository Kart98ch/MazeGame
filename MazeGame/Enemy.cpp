#include "Enemy.h"
#include "Level.h"
#include "Player.h"
#include <iostream>

void Enemy::Init()
{
	if (m_xDirection > 1)
	{
		m_xDirection = 1;
	}
	else if (m_xDirection < -1)
	{
		m_xDirection = -1;
	}

	if (m_yDirection > 1)
	{
		m_yDirection = 1;
	}
	else if (m_yDirection < -1)
	{
		m_xDirection = -1;
	}

}

void Enemy::Draw() const { std::cout << kEnemy; }

void Enemy::Update(const Level &level)
{
	if (m_xDirection != 0)
	{
		if (m_xDeviation*m_xDirection < m_moveLimit)
		{
			m_xDeviation += m_xDirection;

			if (level.IsSpace(m_pPosition.m_X + m_xDirection, m_pPosition.m_Y))
			{
				m_pPosition.m_X += m_xDirection;
			}
		}
		else
		{
			m_xDirection *= -1;
			m_xDeviation += m_xDirection;
			if (level.IsSpace(m_pPosition.m_X + m_xDirection, m_pPosition.m_Y))
			{
				m_pPosition.m_X += m_xDirection;
			}
		}
	}

	if (m_yDirection != 0)
	{
		if (m_yDeviation * m_yDirection < m_moveLimit)
		{
			m_yDeviation += m_yDirection;
			if (level.IsSpace(m_pPosition.m_X, m_pPosition.m_Y + m_yDirection))
			{
				m_pPosition.m_Y += m_yDirection;
			}
		}
		else
		{
			m_yDirection *= -1;
			m_yDeviation += m_yDirection;
			if (level.IsSpace(m_pPosition.m_X, m_pPosition.m_Y + m_yDirection))
			{
				m_pPosition.m_Y += m_yDirection;
			}
		}
	}
}

bool Enemy::OnCollide(Player* player, int newX, int newY, const Level& m_level)
{
	if (player->GetWeaponCount() > 0)
	{
		SetInactive();
		player->LoseWeapon();
		player->IncreaseScore();
		player->SetPosition(newX, newY);
		return false;
	}
	else
	{
		player->LoseLife();
		// Do not move.
		if (player->GetLives() < 1) 
		{ 
			return true;
		}
		player->SetPosition(m_level.GetStartX(), m_level.GetStartY());
		return false;
	}
}
