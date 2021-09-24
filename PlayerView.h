#pragma once

#include "Card.h"
#include "Player.h"

class PlayerView
{
public:
	PlayerView() = default;

	// Declare Destructor
	~PlayerView() = default;

	// Gets user input on which card to play
	CardPtr GetCardToPlay(const PlayerPtr&);

	// Gets user input on which card to announce
	Creature GetCreatureToAnnounce();

	// Shows open cards for player
	void ShowOpenCards(const PlayerPtr& inPlayer);

	// Selects a player from the list
	PlayerPtr SelectOpponent(const PlayerVec&);

	// Ask the player whether they want to pass
	// If they want to pass, get the new creature they want to declare
	bool GetPassAndCreatureChoice(Creature& inOutCreature);

	// Print the player has lost a round
	void DeclareRoundLoss(const PlayerPtr&);

	// Decide whether tp accept a card or pass it on
	bool MakeDecision();

	// Print the name of the player who has to make the choice
	void DeclarePlayerChoice(const PlayerPtr&);
};

using PlayerViewPtr = std::shared_ptr<PlayerView>;