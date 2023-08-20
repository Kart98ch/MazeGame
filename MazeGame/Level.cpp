#include "Level.h"
#include <fstream>
#include <iostream>
#include <string>
#include <conio.h>
#include "Goal.h"
#include "Enemy.h"
#include"Weapon.h"
#include "Player.h"
#include <windows.h>

Level::Level() :m_pLevelData(nullptr), m_height(0), m_width(0) {}

Level::~Level()
{
	if (m_pLevelData != nullptr)
	{
		delete m_pLevelData;
		m_pLevelData = nullptr;
	}

	while (!m_pActors.empty())
	{
		delete m_pActors.back();
		m_pActors.pop_back();
	}

}

void Level::LoadLevel(std::string& levelName, Player* player)
{
	std::ifstream levelFile;
	levelName.insert(0, "../");
	levelFile.open(levelName);
	if (!levelFile)
	{
		std::cout << "Failed to load level...";
		exit(0);
	}
	else
	{
		char temp[tempSize];

		levelFile.getline(temp, tempSize, '\n');
		m_width = atoi(temp);
		std::cout << m_width;

		levelFile.getline(temp, tempSize, '\n');
		m_height = atoi(temp);
		std::cout << m_height;

		m_pLevelData = new char[m_height * m_width];
		levelFile.read(m_pLevelData, m_height * m_width);

		Convert(player);

		std::cout << "Level loaded...\n";
	}


}

void Level::Draw() const 
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	DisplayTopBorder();

	for (int y = 0; y < m_height; y++)
	{

		DisplayLeftBorder();

		for (int x = 0; x < m_width; x++)
		{
			std::cout << m_pLevelData[GetIndex(x, y)];
		}

		DisplayRightBorder();

	}

	DisplayBottomBorder();

	COORD actorCursorPosition;

	for (auto actor = m_pActors.begin(); actor != m_pActors.end(); actor++)
	{
		if ((*actor)->IsActive())
		{
			actorCursorPosition.X = (*actor)->GetXPosition() + 1;
			actorCursorPosition.Y = (*actor)->GetYPosition() + 1;
			SetConsoleCursorPosition(console, actorCursorPosition);
			(*actor)->Draw();
		}
	}


}

void Level::DisplayTopBorder() const
{
	std::cout << kTopLeft;
	for (int i = 0; i < m_width; i++)
	{
		std::cout << kHorizontal;
	}
	std::cout << kTopRight << '\n';
}

void Level::DisplayLeftBorder() const
{
	std::cout << kVertical;
}

void Level::DisplayRightBorder() const
{
	std::cout << kVertical << '\n';
}

void Level::DisplayBottomBorder() const
{
	std::cout << kBottomLeft;
	for (int i = 0; i < m_width; i++)
	{
		std::cout << kHorizontal;
	}
	std::cout << kBottomRight << '\n';
}

void Level::NewPosition(int& newCursorX, int& newCursorY)
{
	CursorX = std::move(newCursorX);
	CursorY = std::move(newCursorY);
}

Actor* Level::UpdateActors(int x, int y, bool updateCondition)
{
	if(updateCondition)
	{
		return UpdateMove(x, y);
	}
	else
	{
		return UpdateAttack(x, y);
	}
}

Actor* Level::UpdateMove(int x, int y)
{
	for (Actor* actor : m_pActors)
	{
		actor->Update(*this);

		if (x == actor->GetXPosition() && y == actor->GetYPosition())
		{
			return actor;
		}
	}
	return nullptr;
}

Actor* Level::UpdateAttack(int x, int y)
{
	Actor* collidedActor = nullptr;

	for (Actor* actor : m_pActors)
	{
		if (x == actor->GetXPosition() && y == actor->GetYPosition())
		{
			collidedActor = actor;
		}

		actor->Update(*this);

	}
	return collidedActor;
}

void Level::Convert(Player* player)
{
	for (int i = 0; i < m_height * m_width; i++)
	{
		switch (m_pLevelData[i])
		{
		case 'X':
		case 'x':
			player->SetPosition(i % m_width, (i - CursorX) / m_width);

			m_StartX = player->GetXPosition();
			m_StartY = player->GetYPosition();

			m_pLevelData[i] = kSpace;
			break;

		case 'W':
		case 'w':
			m_pLevelData[i] = kWall;
			break;

		case 'G':
		case 'g':
			m_pActors.push_back(new Goal(i % m_width, (i - CursorX) / m_width));
			m_pLevelData[i] = kSpace;
			break;

		case 'V':
		case 'v':
			m_pActors.push_back(new Enemy(i % m_width, (i - CursorX) / m_width, 0, m_YDirection, m_limitMovement));
			m_pLevelData[i] = kSpace;
			m_YDirection *= -1;
			break;

		case 'H':
		case 'h':
			m_pActors.push_back(new Enemy(i % m_width, (i - CursorX) / m_width, m_XDirection, 0, m_limitMovement));
			m_pLevelData[i] = kSpace;
			m_XDirection *= -1;
			break;

		case 'P':
		case 'p':
			m_pActors.push_back(new Weapon(i % m_width, (i - CursorX) / m_width));
			m_pLevelData[i] = kSpace;
			break;

		default:
			break;
		}

	}

}
