#pragma once
#include <vector>
#include <string>

class Actor;
class Player;

class Level
{
private:
	char* m_pLevelData;
	int m_height;
	int m_width;
	std::vector<Actor*> m_pActors;
	bool m_winCondition = true;
	int CursorX = 0;
	int CursorY = 0;
	int m_XDirection = 1;
	int m_YDirection = 1;
	int m_limitMovement = 2;
	int m_StartX = 0;
	int m_StartY = 0;

	static constexpr int tempSize = 25;
	static constexpr unsigned char kSpace = 32;
	static constexpr unsigned char kCursor = 164;
	static constexpr unsigned char kWall = 219;
	static constexpr unsigned char kGoal = 245;
	static constexpr int kArrowInput = 224;
	static constexpr int kLeftArrow = 75;
	static constexpr int kRightArrow = 77;
	static constexpr int kUpArrow = 72;
	static constexpr int kDownArrow = 80;
	static constexpr int kEscape = 27;
	static constexpr unsigned char kTopLeft = 201;
	static constexpr unsigned char  kHorizontal = 205;
	static constexpr unsigned char  kTopRight = 187;
	static constexpr unsigned char  kVertical = 186;
	static constexpr unsigned char  kBottomLeft = 200;
	static constexpr unsigned char  kBottomRight = 188;

public:
	Level();
	~Level();

	void LoadLevel(std::string& levelName, Player* player);
	void Draw() const;

	int GetHeight() const { return m_height; }
	int GetWidth() const { return m_width; }
	bool GetWinCondition() const { return m_winCondition; }
	void ChangeWinCondition() { m_winCondition = true; }
	bool IsSpace(int x, int y) const { return m_pLevelData[GetIndex(x, y)] == kSpace; }
	bool IsGoal(int x, int y) const { return m_pLevelData[GetIndex(x, y)] == kGoal; }
	bool IsWall(int x, int y) const { return m_pLevelData[GetIndex(x, y)] == kWall; }
	int GetStartX() const { return m_StartX; }
	int GetStartY() const { return m_StartY; }

	Actor* UpdateActors(int x, int y, bool updateCondition);
	Actor* UpdateMove(int x, int y);
	Actor* UpdateAttack(int x, int y);

private:
	
	int GetIndex(int x, int y) const { return x + y * m_width; }
	void Convert(Player* player);
	void NewPosition(int& newCursorX, int& newCursorY);
	void DisplayTopBorder() const;
	void DisplayLeftBorder() const;
	void DisplayRightBorder() const;
	void DisplayBottomBorder() const;

};

