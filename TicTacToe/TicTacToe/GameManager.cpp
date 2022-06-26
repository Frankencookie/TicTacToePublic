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

    //This could be made more efficient by only testing squares next to the most recently placed square
    //No point in testing every square
    //This method can find if there's a victory overall so may be useful anyway, might make a second method for testing victory by square

    //Row test
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0)
        {
            return true;
        }
    }

    //column test
    for (int j = 0; j < 3; j++)
    {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != 0)
        {
            return true;
        }
    }

    //Diagonal tests
    //00 01 02
    //10 11 12
    //20 21 22
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != 0)
    {
        return true;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != 0)
    {
        return true;
    }


    return false;
}

int GameManager::GetNumber()
{
    return number;
}
