#pragma once
#include "Player.h"
#include "Level.h"

class string;

class Game
{

private:
	Player m_player;
	Level m_level;
	bool m_gameOver;

	static constexpr int kArrowInput = 224;
	static constexpr int kLeftArrow = 75;
	static constexpr int kRightArrow = 77;
	static constexpr int kUpArrow = 72;
	static constexpr int kDownArrow = 80;
	static constexpr int kEscape = 27;
	static constexpr int kSpace = 32;

public:
	Game() : m_gameOver(false), m_player(Player(0,0)) {}
	void Load();
	void Run();
	void MainMenu();
	

private:
	int GetPlayerLives();
	void Draw() const;
	bool Update();
	bool Move(const int& arrowInput, int& newCursorX, int& newCursorY);
	bool Collision(int& newX, int& newY);
	void Clamp(int& newX, int& newY);
	void DisplayStats() const;
	void EndScreen() const;

	void PlayerAttack();



};

