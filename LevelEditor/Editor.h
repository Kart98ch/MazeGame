#pragma once
#include "LevelEditorClass.h"

class Editor
{
	LevelEditorClass* p_level;

public:
	Editor() { Init(); }
	~Editor() { if (!(p_level == nullptr)) { delete p_level; p_level = nullptr; } }
	void Init() { MainMenu(); }

	void MainMenu();
	void CreateLevel();
	void LoadLevel();
	void SaveLevel();
	void Exit();
	void ReturnToMenu();



};

