#pragma once
#include "Helpers.h"
#include "Input.h"

class IGameState;
class Window;
class GameManager;
class SpriteBank;

class GameStateMachine
{
public:
	~GameStateMachine();

private:
	IGameState* currentState;

public:
	void ChangeState(IGameState* newState, bool useExit = true);
	void UpdateState();

};

class IGameState : public IInputObserver
{
public:
	virtual void OnStateBegin();
	virtual void OnStateUpdate();
	virtual void OnStateExit();

protected:
	GameStateMachine* parentSM;

public:
	void InitState(GameStateMachine* parent);
	void ExitState();
	void DrawBoard();
};

class PreparingGameState : public IGameState
{
public:
	void OnStateBegin() override;
};

class TurnStateBase : public IGameState
{
protected:
	int CalculateScreenXPos(int xPos);
	int CalculateScreenYPos(int yPos);

protected:
	Vector2D GetSquareClicked(Vector2D mousePos);
};

class XTurnState : public TurnStateBase
{
public:
	void OnStateBegin() override;
	void OnClickEvent(Vector2D position) override;
};

class OTurnState : public TurnStateBase
{
public:
	void OnStateBegin() override;
	void OnClickEvent(Vector2D position) override;
};