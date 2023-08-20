#include "Editor.h"
#include <iostream>
#include <conio.h>

void Editor::MainMenu()
{
	system("cls");
	std::cout << "Please select actions:\n\n1) Create Level\n2) Load Level\n3) Exit\n\n";
	std::cout << "Input: ";
	int input;
	std::cin >> input;

	if (input == 1)
	{
		system("cls");
		CreateLevel();
	}
	else if (input == 2)
	{
		system("cls");
		LoadLevel();
	}
	else
	{
		Exit();
	}

}

void Editor::CreateLevel()
{
	p_level = new LevelEditorClass;
	p_level->GetDimensions();
	p_level->CreateDefaultLevelArray();

	bool doneEditing = false;
	while (!doneEditing)
	{
		system("cls");
		p_level->DisplayLevel();
		doneEditing = p_level->EditLevel();
	}

	SaveLevel();

	delete p_level;
	p_level = nullptr;

	Exit();
}

void Editor::LoadLevel()
{
	p_level = new LevelEditorClass;

	std::cout << "Name of level to load (include .txt): ";
	std::string levelName;
	std::cin >> levelName;

	p_level->LoadLevel(levelName);

	bool doneEditing = false;
	while (!doneEditing)
	{
		system("cls");
		p_level->DisplayLevel();
		p_level->FindCursor();
		doneEditing = p_level->EditLevel();
	}

	SaveLevel();

	delete p_level;
	p_level = nullptr;

	Exit();
}

void Editor::SaveLevel()
{
	std::cout << "Do you want to save level:\n1) Y\n2) N\n";
	int input;
	std::cin >> input;

	if (input == 1)
	{
		p_level->SaveLevel();
	}
	else
	{
		// Do nothing.
	}
}

void Editor::Exit()
{
	std::cout << "Do you want to exit or return to Main Menu?:\n\n";
	std::cout << "1) Main Menu\n2) Exit\n";
	int input;
	std::cin >> input;

	if (input == 1)
	{
		MainMenu();
	}
	else
	{
		exit(0);
	}
}