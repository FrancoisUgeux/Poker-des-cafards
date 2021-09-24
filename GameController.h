#pragma once

#include "GameModel.h"
#include "GameView.h"
#include "PlayerController.h"

class GameController
{
public:
	GameController();

	// Setup the controller. Initializes the game
	void Setup();

	// Has the application loop which runs till someone loses
	void Run();

	// Callback to create player
	static PlayerPtr OnPlayerInformationEntered(const std::string& inName, const int inAge);

private:
	Game					mGame;
	GameView				mGameView;

	PlayerViewPtr			mPlayerView;
	PlayerControllerPtr		mPlayerController;
};