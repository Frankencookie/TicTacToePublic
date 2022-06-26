#pragma once
#include <stdio.h>

class Window;
class GameStateMachine;
class Input;

class TicTacToeApp
{
public:
	TicTacToeApp();
	~TicTacToeApp();

	bool RunApp();

protected:
	Window* appWindow_ptr = nullptr;
	GameStateMachine* gameSM_ptr = nullptr;
	Input* inputHandler_ptr = nullptr;
};

