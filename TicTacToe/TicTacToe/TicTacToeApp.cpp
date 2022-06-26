#include "TicTacToeApp.h"
#include "Window.h"
#include "GameStateMachine.h"

TicTacToeApp::TicTacToeApp()
{
    appWindow_ptr = new Window();
    printf("Created App Window \n");
    gameSM_ptr = new GameStateMachine();
    gameSM_ptr->ChangeState(new PreparingGameState());

    inputHandler_ptr = new Input();
}

TicTacToeApp::~TicTacToeApp()
{
    delete appWindow_ptr;
    appWindow_ptr = nullptr;

    delete gameSM_ptr;
    gameSM_ptr = nullptr;

    delete inputHandler_ptr;
    inputHandler_ptr = nullptr;

    printf("Destroyed App");
}

bool TicTacToeApp::RunApp()
{
    while (true)
    {
        appWindow_ptr->ClearScreen();
        appWindow_ptr->DrawBackground();
        inputHandler_ptr->UpdateInput();
        gameSM_ptr->UpdateState();

        appWindow_ptr->PresentRender();
    }
    return false;
}
