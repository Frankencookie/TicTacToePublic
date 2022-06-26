#include "GameManager.h"

GameManager GameManager::instance;
int GameManager::board[3][3];
int GameManager::number;

GameManager& GameManager::Get()
{
    return instance;
}

void GameManager::ClearBoard()
{
    number = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = 0;
        }
    }
}

void GameManager::SetBoardValue(Vector2D pos, int value)
{
    board[pos.X][pos.Y] = value;
    number++;
}

int GameManager::GetBoardValueAtPos(Vector2D pos)
{
    return board[pos.X][pos.Y];
}

int* GameManager::GetBoardData()
{
    return *board;
}

bool GameManager::IsMoveValid(Vector2D pos)
{
    return board[pos.X][pos.Y] == 0;
}

bool GameManager::CheckVictory()
{
    //Victory states:
    //If the top 3 items are x or o
    //If Middle 3 are x or o
    //If bottom 3 are x or o
    //if row 1 has 3 in a row
    //ditto for 2
    //ditto for 3
    //Diagonal 3 in a row

    //Row test
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j] != 0)
            {
                return true;
            }
        }
    }

    //column test
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 1; i++)
        {
            if (board[i][j] == board[i + 1][j] && board[i + 1][j] == board[i + 2][j] && board[i][j] != 0)
            {
                return true;
            }
        }
    }

    return false;
}

int GameManager::GetNumber()
{
    return number;
}
