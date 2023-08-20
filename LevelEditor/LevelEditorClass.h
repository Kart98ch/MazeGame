#pragma once
#include <string>

class LevelEditorClass
{
public:
	
	char* m_pLevel;
	int m_levelWidth;
	int m_levelHeight;

	LevelEditorClass(): m_pLevel(nullptr), m_levelWidth(0), m_levelHeight(0) {}
	~LevelEditorClass() { delete m_pLevel; m_pLevel = nullptr; }

	void GetDimensions();

	void CreateDefaultLevelArray();

	void DisplayLevel() const;

	bool EditLevel();
	void Move(const int& arrowInput, int& newCursorX, int& newCursorY);
	void Clamp(int& newCursorX, int& newCursorY);

	void DisplayTopBorder() const;
	void DisplayLeftBorder() const;
	void DisplayRightBorder() const;
	void DisplayBottomBorder() const;

	void SaveLevel();

	void LoadLevel(std::string& levelName);

	void FindCursor();

	void Legend() const;

protected:
	int GetIndex(int x, int y) const;

	int m_cursorX = 0;
	int m_cursorY = 0;

	static constexpr int tempSize = 25;

	static constexpr unsigned char kCursor = '_';
	
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
};

