#include "LevelEditorClass.h"
#include <iostream>
#include <conio.h>
#include <fstream>

void LevelEditorClass::GetDimensions()
{
	std::cout << "Set width for level: ";
	std::cin >> m_levelWidth;
	std::cout << "Set height for level: ";
	std::cin >> m_levelHeight;
}

void LevelEditorClass::CreateDefaultLevelArray()
{
	m_pLevel = new char[m_levelWidth * m_levelHeight];

	for (int i = 0; i < m_levelWidth * m_levelHeight; i++)
	{
		m_pLevel[i] = ' ';
	}
}

void LevelEditorClass::DisplayLevel() const
{
	DisplayTopBorder();

	for (int y = 0; y < m_levelHeight; y++)
	{

		DisplayLeftBorder();

		for (int x = 0; x < m_levelWidth; x++)
		{
			if (x == m_cursorX && y == m_cursorY)
			{
				std::cout << kCursor;
			}
			else
			{
				std::cout << m_pLevel[GetIndex(x, y)];
			}
			
		}

		DisplayRightBorder();

	}

	DisplayBottomBorder();
	Legend();
}

bool LevelEditorClass::EditLevel()
{
	int newCursorX = m_cursorX;
	int newCursorY = m_cursorY;

	int intInput = _getch();
	
	if (intInput == kArrowInput) // arrow inputs have two facets.
	{
		int arrowInput = _getch();
		Move(arrowInput, newCursorX, newCursorY);

	}
	else
	{
		if (intInput == kEscape)
		{
			return true;
		}
		else
		{
			m_pLevel[GetIndex(newCursorX, newCursorY)] = (char)intInput;
		}
	}
	
	return false;
	
}

void LevelEditorClass::Move(const int& arrowInput, int& newCursorX, int& newCursorY)
{
	switch (arrowInput)
	{
	case kLeftArrow:
		newCursorX--;
		break;
	case kRightArrow:
		newCursorX++;
		break;
	case kUpArrow:
		newCursorY--;
		break;
	case kDownArrow:
		newCursorY++;
		break;
	}

	Clamp(newCursorX, newCursorY);

	m_cursorX = newCursorX;
	m_cursorY = newCursorY;
}

void LevelEditorClass::Clamp(int& newCursorX, int& newCursorY)
{
	if (newCursorX < 0)
	{
		newCursorX = 0;
	}
	else if (newCursorX == m_levelWidth)
	{
		newCursorX = m_levelWidth - 1;
	}

	if (newCursorY < 0)
	{
		newCursorY = 0;
	}
	else if (newCursorY == m_levelHeight)
	{
		newCursorY = m_levelHeight - 1;
	}
}

void LevelEditorClass::DisplayTopBorder() const
{
	std::cout << kTopLeft;
	for (int i = 0; i < m_levelWidth; i++)
	{
		std::cout << kHorizontal;
	}
	std::cout << kTopRight << '\n';
}

void LevelEditorClass::DisplayLeftBorder() const
{
	std::cout << kVertical;
}

void LevelEditorClass::DisplayRightBorder() const
{
	std::cout << kVertical << '\n';
}

void LevelEditorClass::DisplayBottomBorder() const
{
	std::cout << kBottomLeft;
	for (int i = 0; i < m_levelWidth; i++)
	{
		std::cout << kHorizontal;
	}
	std::cout << kBottomRight << '\n';
}

void LevelEditorClass::SaveLevel()
{
	std::cout << "Name of level: ";
	std::string levelName;
	std::cin >> levelName;

	levelName.insert(0, "../");

	std::ofstream levelFile;
	levelFile.open(levelName);

	if (!levelFile)
	{
		std::cout << "Failed to open file...\n";
	}
	else
	{
		levelFile << m_levelWidth << '\n';
		levelFile << m_levelHeight << '\n';
		levelFile.write(m_pLevel, m_levelWidth * m_levelHeight);
		
		if (!levelFile)
		{
			std::cout << "Write failed...\n";
		}
		else 
		{
			std::cout << "Level saved!\n";
		}

		levelFile.close();
	}

}

void LevelEditorClass::LoadLevel(std::string& levelName)
{
	// load existing level

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
		m_levelWidth = atoi(temp);
		std::cout << m_levelWidth;

		levelFile.getline(temp, tempSize, '\n');
		m_levelHeight = atoi(temp);
		std::cout << m_levelHeight;

		m_pLevel = new char[m_levelHeight * m_levelWidth];
		levelFile.read(m_pLevel, m_levelHeight * m_levelWidth);

		std::cout << "Level loaded...\n";
	}
}

void LevelEditorClass::FindCursor()
{
	for (int i = 0; i < m_levelHeight * m_levelWidth; i++)
	{
		if (m_pLevel[i] == '-')
		{
			m_cursorX = i % m_levelWidth;
			m_cursorY = (i - m_cursorX) / m_levelWidth;
		}
	}
}

void LevelEditorClass::Legend() const
{
	std::cout << "w = Wall\n";
	std::cout << "e = Enemy\n";
	std::cout << "g = Goal\n";
	std::cout << "p = Weapon\n";
	std::cout << "x = Player Start\n";
}

int LevelEditorClass::GetIndex(int x, int y) const { return x + y * m_levelWidth; }



