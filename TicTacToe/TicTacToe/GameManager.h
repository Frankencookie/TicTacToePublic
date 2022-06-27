#pragma once
#include "Helpers.h"

//Handles the board state
class GameManager
{
public:
	//Singleton getter and instance
	static GameManager& Get();
	static GameManager instance;

	void ClearBoard();

	//Methods for checking and setting board state
	void SetBoardValue(Vector2D pos, int value);
	int GetBoardValueAtPos(Vector2D pos);
	int* GetBoardData();
	int GetNumber();

	bool IsMoveValid(Vector2D pos);
	bool CheckVictory();

private:
	//Game board
	int board[3][3];

	//Number of turns, if this reaches 9 then the game is a draw
	int number;
};

