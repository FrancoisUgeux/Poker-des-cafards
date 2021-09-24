#include <algorithm>
#include <iostream>
#include "PlayerController.h"
#include "PlayerView.h"

PlayerController::PlayerController(const PlayerViewPtr& inPlayerView)
	: mPlayerView(inPlayerView)
{}

PlayerPtr PlayerController::PlayCard(PlayerPtr& inDealer, const PlayerVec& inPlayerList)
{
	// Get the card to play from the view
	CardPtr cardToPlay = mPlayerView->GetCardToPlay(inDealer);
	// Remove it from hand
	inDealer->RemoveCardFromHand(cardToPlay);

	// Get the creature we want to announce
	Creature creature = mPlayerView->GetCreatureToAnnounce();
	return PlayCard(inDealer, inPlayerList, cardToPlay, creature);
}

PlayerPtr PlayerController::PlayCard(const PlayerPtr& inDealer, const PlayerVec& inPlayerList, const CardPtr& inCard, const Creature& inCreature)
{
	Creature creature = inCreature;

	// Select opponent
	PlayerPtr opponent = mPlayerView->SelectOpponent(inPlayerList);

	mPlayerView->DeclarePlayerChoice(opponent);
	if (inPlayerList.size() > 1)
	{
		// Give choice to pass if there are more players
		bool passToOtherPlayer = mPlayerView->GetPassAndCreatureChoice(creature);
		if (passToOtherPlayer)
		{
			// Get opponent list and forward card to the player we want to pass to
			PlayerVec opponentList = inPlayerList;
			opponentList.erase(std::remove(opponentList.begin(), opponentList.end(), opponent), opponentList.end());
			return PlayCard(opponent, opponentList, inCard, creature);
		}
	}

	// Card accepted, now we have to make a choice
	bool agreeWithDealer = mPlayerView->MakeDecision();

	PlayerPtr loser = opponent;
	if ((agreeWithDealer && creature == inCard->GetCreature())
		|| (!agreeWithDealer && creature != inCard->GetCreature()))
	{
		// Dealer loses, set them as loser
		loser = inDealer;
	}

	// Add the card to loser's open list
	loser->AddToOpenCards(inCard);

	// Declare the loser
	mPlayerView->DeclareRoundLoss(loser);
	return loser;
}
