#pragma once
#include "Helpers.h"
#include "Input.h"

class IGameState;
class Window;
class GameManager;
class SpriteBank;

//State machine for handling players
class GameStateMachine : public IInputObserver
{
public:
	GameStateMachine();
	~GameStateMachine();

private:
	//State currently updating
	IGameState* currentState = nullptr;
	bool running = true;

public:
	void ChangeState(IGameState* newState, bool useExit = true);
	void UpdateState();

	//Returns running bool, called to see if the program should stop looping
	bool GetRunning();

	//Input observer interface override for keyboard events, should respond to ESC and mark program for closure
	void OnKeyboardEvent(SDL_Keycode keycode) override;
};

class IGameState : public IInputObserver
{
public:
	//States to be overidden by each gamestate
	virtual void OnStateBegin();
	virtual void OnStateUpdate();
	virtual void OnStateExit();

protected:
	//State machine this state is attached to
	GameStateMachine* parentSM;

public:
	//Methods which are common across all states
	void InitState(GameStateMachine* parent);
	void ExitState();
	void DrawBoard();
};

//Initial state for state machine. Used to reset the game state.
//Originally made a welcome message appear but was removed
class PreparingGameState : public IGameState
{
public:
	void OnStateBegin() override;
};

//Base class for player turns, includes common turn functionality
class TurnStateBase : public IGameState
{
protected:
	int CalculateScreenXPos(int xPos);
	int CalculateScreenYPos(int yPos);

protected:
	Vector2D GetSquareClicked(Vector2D mousePos);
};

//Player 1 turn state
class XTurnState : public TurnStateBase
{
public:
	void OnStateBegin() override;
	void OnClickEvent(Vector2D position) override;
};

//Player 2 turn state
class OTurnState : public TurnStateBase
{
public:
	void OnStateBegin() override;
	void OnClickEvent(Vector2D position) override;
};