#include <iostream>
#include "GameView.h"

PlayerPtr GameView::PlayerSetup()
{
	// Get the player name and age
	std::string playerName;
	int playerAge;
	std::cout << "Player Name: ";
	std::cin >> playerName;
	while (std::cin.fail() || playerName.length() == 0)
	{
		std::cout << "Please enter a valid player name" << std::endl;
	}
	std::cout << "Player Age: ";
	std::cin >> playerAge;
	while (std::cin.fail() || playerAge < 8 || playerAge > 100)
	{
		std::cout << "Please enter a valid player age" << std::endl;
	}

	return mAddPlayerCallbackFnPtr(playerName, playerAge);
}

int GameView::GetNumberOfPlayers()
{
	std::cout << "Enter the number of players:" << std::endl;
	int playerCount;
	std::cin >> playerCount;

	// Validate user input
	while (std::cin.fail() || playerCount < 2 || playerCount > 6)
	{
		std::cout << "This game is meant to be played by 2-6 players only. Please enter a proper value:" << std::endl;
		std::cin >> playerCount;
	}

	return playerCount;
}

void GameView::EndGame(const PlayerPtr& inLoser)
{
	std::cout << "Oops... " << inLoser->GetName() << " has lost the game!! Everyone else has won!!" << std::endl;
}