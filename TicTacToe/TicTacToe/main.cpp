#include "TicTacToeApp.h"
#include <memory>

//Entry point
int main(int argc, char* args[])
{
	//Create and run app, unique ptr clears memory when done
	{
		std::unique_ptr<TicTacToeApp> app(new TicTacToeApp());
		app->RunApp();
	}

	return 0;
}