#pragma once
#include "Card.h"
#include "Player.h"

class Game
{
public:
	// Initializes the game model
	void Initialize();

	// Adds a player to the game
	void AddPlayer(const PlayerPtr& inPlayer);

	// Distributes the cards among the players
	void DistributeCards();

	// Getter/Setter for who is dealing cards
	PlayerPtr GetDealer() const { return mDealer; }
	void SetDealer(const PlayerPtr& inDealer) { mDealer = inDealer;  }

	// Get a list of possible opponents
	PlayerVec GetPossibleOpponents() const;

	// Check if the game has ended because someone lost
	bool HasEnded();

private:
	CardVec				mCards;
	PlayerVec			mPlayers;
	int					mOpenCardLimit;
	PlayerPtr			mDealer;
};