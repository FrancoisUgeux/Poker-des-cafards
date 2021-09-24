#include <iostream>
#include <memory.h>
#include "Card.h"
#include "Player.h"
#include "GameController.h"

GameController::GameController()
{
	// Set callback function to create player
	mGameView.SetAddPlayerCallbackFnPtr(&GameController::OnPlayerInformationEntered);

	// Crate the player view and player controller
	mPlayerView = std::make_shared<PlayerView>();
	mPlayerController = std::make_shared<PlayerController>(mPlayerView);
}

PlayerPtr GameController::OnPlayerInformationEntered(const std::string& inName, const int inAge)
{
	// Create player object ans return
	return std::make_shared<Player>(inName, inAge);
}

void GameController::Setup()
{
	// Initialize the game object
	mGame.Initialize();

	// Get the number of players
	int playerCount = mGameView.GetNumberOfPlayers();
	for (int i = 0; i < playerCount; ++i)
	{
		// Get information on each player from view and add them to the game
		std::cout << "Enter some information about player#" << i + 1 << ":" << std::endl;
		mGame.AddPlayer(mGameView.PlayerSetup());
	}

	// Districute the cards amongst the players
	mGame.DistributeCards();
}

void GameController::Run()
{
	while (true)
	{
		PlayerPtr dealer = mGame.GetDealer();

		// Play the card and get who lost. Set them as the next dealer
		PlayerPtr loser = mPlayerController->PlayCard(dealer, mGame.GetPossibleOpponents());
		mGame.SetDealer(loser);
		if (mGame.HasEnded())
		{
			// Announce game loss for the loser and break
			mGameView.EndGame(loser);
			break;
		}
	}
}