#include "Game.h"
#include <conio.h>
#include "Goal.h"
#include "Enemy.h"
#include "Weapon.h"
#include <windows.h>
#include <iostream>

std::string levelName = "Text2.txt";

void Game::Load()
{
	m_level.LoadLevel(levelName, &m_player);
}

void Game::Run()
{
	while (!m_gameOver)
	{
		Draw();
		m_gameOver = Update();
	}

	EndScreen();
}

void Game::MainMenu()
{
	system("cls");
	std::cout << "1) Play Game\n2) Exit\n";
	int input;
	std::cin >> input;

	if (input == 1)
	{
		Run();
	}
	
	std::cout << "\n\nExiting Program\n";

}

int Game::GetPlayerLives() 
{ 
	return m_player.GetLives(); 
}

void Game::Draw() const
{
	system("cls");
	m_level.Draw();

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD actorCursorPosition{ (short)(m_player.GetXPosition() + 1), (short)(m_player.GetYPosition() + 1) };
	SetConsoleCursorPosition(console, actorCursorPosition);
	m_player.Draw();

	COORD currentCursorPosition{ (short)0, (short)m_level.GetHeight() + 2 };
	SetConsoleCursorPosition(console, currentCursorPosition);

	DisplayStats();
}

bool Game::Update()
{
	int newX = m_player.GetXPosition();
	int newY = m_player.GetYPosition();

	int intInput = _getch();

	if (intInput == kArrowInput) // arrow inputs have two facets.
	{
		int arrowInput = _getch();
		return Move(arrowInput, newX, newY);

	}
	else if (intInput == kSpace)
	{
		PlayerAttack();
		return false;
	}
	else
	{
		if (intInput == kEscape)
		{
			return true;
		}
	}

	return false;
}

bool Game::Move(const int& arrowInput, int& newX, int& newY)
{
	switch (arrowInput)
	{
	case kLeftArrow:
		newX--;
		m_player.UpdateDirection(arrowInput);
		break;
	case kRightArrow:
		newX++;
		m_player.UpdateDirection(arrowInput);
		break;
	case kUpArrow:
		newY--;
		m_player.UpdateDirection(arrowInput);
		break;
	case kDownArrow:
		newY++;
		m_player.UpdateDirection(arrowInput);
		break;
	}

	if (newX == m_player.GetXPosition() && newY == m_player.GetYPosition())
	{
		return false;
	}
	else
	{
		return Collision(newX, newY);
	}
}

bool Game::Collision(int& newX, int& newY)
{
	Clamp(newX, newY);

	if (m_level.IsSpace(newX, newY)) { m_player.SetPosition(newX, newY); }
	else if (m_level.IsWall(newX, newY)) { /*do nothing*/ }

	Actor* collidedActor = m_level.UpdateActors(newX, newY, true);
	if (collidedActor != nullptr && collidedActor->IsActive())
	{
		return collidedActor->OnCollide(&m_player, newX, newY, m_level);
	}

	return false;
}

void Game::Clamp(int& newX, int& newY)
{
	if (newX < 0)
	{
		newX = 0;
		m_player.SetPosition(newX, newY);
	}
	else if (newX == m_level.GetWidth())
	{
		newX = m_level.GetWidth() - 1;
		m_player.SetPosition(newX, newY);
	}
	else if (newY < 0)
	{
		newY = 0;
		m_player.SetPosition(newX, newY);
	}
	else if (newY == m_level.GetHeight())
	{
		newY = m_level.GetHeight() - 1;
		m_player.SetPosition(newX, newY);
	}
}

void Game::DisplayStats() const
{
	std::cout << "Lives: " << m_player.GetLives() << '\n';
	std::cout << "Score: " << m_player.GetScore();
}

void Game::EndScreen() const
{
	
	if (m_player.GetLives()<1)
	{
		std::cout << "      ------- Game Over - No More Lives Left -------\n";
	}
	else if (m_level.GetWinCondition())
	{
		std::cout << "      ------- Success - Goal Reached -------\n";
	}

}

void Game::PlayerAttack()
{
	int x = m_player.GetXPosition() + m_player.GetXDirection();
	int y = m_player.GetYPosition() + m_player.GetYDirection();

	Actor* collidedActor = m_level.UpdateActors(x, y, false);

	if (collidedActor != nullptr && collidedActor->IsActive())
	{
		collidedActor->OnHit();
	}
}