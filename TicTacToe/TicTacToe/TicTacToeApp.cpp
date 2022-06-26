#include "TicTacToeApp.h"
#include "Window.h"
#include "GameStateMachine.h"
#include "Input.h"

TicTacToeApp::TicTacToeApp()
{
    //Create modules
    //Window
    appWindow_ptr = new Window();
    printf("Created App Window \n");

    //Input system
    inputHandler_ptr = new Input();

    //Game state machine, and assign start state
    gameSM_ptr = new GameStateMachine();
    gameSM_ptr->ChangeState(new PreparingGameState());
}

TicTacToeApp::~TicTacToeApp()
{
    //Delete modules
    //Window
    delete appWindow_ptr;
    appWindow_ptr = nullptr;

    //Game State machine
    delete gameSM_ptr;
    gameSM_ptr = nullptr;

    //Input system
    delete inputHandler_ptr;
    inputHandler_ptr = nullptr;

    printf("Destroyed App \n");
}

bool TicTacToeApp::RunApp()
{
    //Core Loop
    while (gameSM_ptr->GetRunning())
    {
        //Clear window and re-draw background
        appWindow_ptr->ClearScreen();
        appWindow_ptr->DrawBackground();

        //Check input then update the game state machine
        inputHandler_ptr->UpdateInput();
        gameSM_ptr->UpdateState();

        //Present render to the screen
        appWindow_ptr->PresentRender();
    }
    return true;
}
