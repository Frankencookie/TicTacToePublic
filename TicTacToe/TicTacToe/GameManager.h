#pragma once
#include "Helpers.h"
class GameManager
{
public:
	static GameManager& Get();

	static GameManager instance;

	static void ClearBoard();

	static void SetBoardValue(Vector2D pos, int value);
	static int GetBoardValueAtPos(Vector2D pos);
	static int* GetBoardData();
	static bool IsMoveValid(Vector2D pos);
	static bool CheckVictory();
	static int GetNumber();

private:
	//Game board
	static int board[3][3];
	static int number;
};

