#include "GameStateMachine.h"
#include "Window.h"
#include "GameManager.h"
#include "SpriteBank.h"

GameStateMachine::GameStateMachine()
{
	Input::AttachKeyboardObserver(this);
}

GameStateMachine::~GameStateMachine()
{
	Input::DetachKeyboardObserver(this);

	if (currentState != nullptr)
	{
		delete currentState;
		currentState = nullptr;
	}
}

void GameStateMachine::ChangeState(IGameState* newState, bool useExit)
{
	if (currentState != nullptr && useExit)
	{
		currentState->ExitState();
		currentState->OnStateExit();
		delete currentState;
	}

	currentState = newState;
	currentState->InitState(this);
	currentState->OnStateBegin();
}

void GameStateMachine::UpdateState()
{
	if (currentState != nullptr)
	{
		currentState->OnStateUpdate();
		currentState->DrawBoard();
	}
}

bool GameStateMachine::GetRunning()
{
	return running;
}

void GameStateMachine::OnKeyboardEvent(SDL_Keycode keycode)
{
	if (keycode == SDLK_ESCAPE)
	{
		running = false;
	}
}

#pragma region State Base Methods
void IGameState::OnStateBegin()
{
}

void IGameState::OnStateUpdate()
{

}

void IGameState::OnStateExit()
{
}

void IGameState::InitState(GameStateMachine* parent)
{
	parentSM = parent;
	Input::AttachClickObserver(this);
}

void IGameState::ExitState()
{
	Input::DetachClickObserver(this);
}

void IGameState::DrawBoard()
{
	int third = Window::instance->GetScreenThird();
	third += 15;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int value = GameManager::GetBoardValueAtPos(Vector2D(i, j));
			switch (value)
			{
				case 0:
					break;
				case 1:
					Window::instance->DrawSprite(SpriteBank::GetInstance().LoadSprite("Assets/x.png", "x"), Vector2D(i * third, j * third));
					break;
				case 2:
					Window::instance->DrawSprite(SpriteBank::GetInstance().LoadSprite("Assets/o.png", "o"), Vector2D(i * third, j * third));
					break;
			}
		}
	}
}

int TurnStateBase::CalculateScreenXPos(int xPos)
{
	int third = Window::instance->GetWindowWidth() / 3;
	int square = xPos / third;
	return square;
}

int TurnStateBase::CalculateScreenYPos(int yPos)
{
	int third = Window::instance->GetWindowHeight() / 3;
	int square = yPos / third;
	return square;
}

Vector2D TurnStateBase::GetSquareClicked(Vector2D mousePos)
{
	int squareNoX = CalculateScreenXPos(mousePos.X);
	int squareNoY = CalculateScreenYPos(mousePos.Y);

	printf(std::to_string(squareNoX).c_str());
	printf(std::to_string(squareNoY).c_str());
	printf("\n");
	return Vector2D(squareNoX, squareNoY);
}


#pragma endregion

#pragma region Preparing State

void PreparingGameState::OnStateBegin()
{
	GameManager::Get().ClearBoard();
	//int result = SDL_ShowSimpleMessageBox(0, "Welcome", "Welcome To Noughts and Crosses", Window::instance->GetWindow());

	parentSM->ChangeState(new XTurnState());

}

#pragma endregion

#pragma region XTurn

void XTurnState::OnStateBegin()
{
	printf("X's Turn \n");
}

void XTurnState::OnClickEvent(Vector2D position)
{
	printf("Click Recieved \n");
	Vector2D square = GetSquareClicked(position);

	bool valid = GameManager::Get().IsMoveValid(square);

	if (valid)
	{
		GameManager::Get().SetBoardValue(square, 1);
		bool result = GameManager::Get().CheckVictory();
		if (result)
		{
			DrawBoard();
			Window::instance->PresentRender();
			SDL_ShowSimpleMessageBox(0, "Victory!", "X is the winner!", Window::instance->GetWindow());
			parentSM->ChangeState(new PreparingGameState());
			return;
		}
		if (GameManager::Get().GetNumber() == 9)
		{
			DrawBoard();
			Window::instance->PresentRender();
			SDL_ShowSimpleMessageBox(0, "Draw!", "It is a draw!", Window::instance->GetWindow());
			parentSM->ChangeState(new PreparingGameState());
			return;
		}
		parentSM->ChangeState(new OTurnState());
	}
}

#pragma endregion

#pragma region OTurn

void OTurnState::OnStateBegin()
{
	printf("O's Turn \n");
}

void OTurnState::OnClickEvent(Vector2D position)
{
	Vector2D square = GetSquareClicked(position);

	bool valid = GameManager::Get().IsMoveValid(square);

	if (valid)
	{
		GameManager::Get().SetBoardValue(square, 2);
		bool result = GameManager::Get().CheckVictory();
		if (result)
		{
			DrawBoard();
			Window::instance->PresentRender();
			SDL_ShowSimpleMessageBox(0, "Victory!", "O is the winner!", Window::instance->GetWindow());
			parentSM->ChangeState(new PreparingGameState());
			return;
		}
		if (GameManager::Get().GetNumber() == 9)
		{
			DrawBoard();
			Window::instance->PresentRender();
			SDL_ShowSimpleMessageBox(0, "Draw!", "It is a draw!", Window::instance->GetWindow());
			parentSM->ChangeState(new PreparingGameState());
			return;
		}
		parentSM->ChangeState(new XTurnState());
	}
}

#pragma endregion
