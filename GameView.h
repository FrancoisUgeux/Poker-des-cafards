#pragma once
#include "Player.h"

using AddPlayerCallbackFnPtr = PlayerPtr(*)(const std::string&, const int);
class GameView
{
public:
	int GetNumberOfPlayers();
	PlayerPtr PlayerSetup();

	void EndGame(const PlayerPtr&);

	void SetAddPlayerCallbackFnPtr(
		const AddPlayerCallbackFnPtr& inCallback)
	{ mAddPlayerCallbackFnPtr = inCallback; }

private:
	AddPlayerCallbackFnPtr		mAddPlayerCallbackFnPtr;
};