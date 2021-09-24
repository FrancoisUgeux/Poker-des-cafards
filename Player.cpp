#include "Player.h"

#include <algorithm>
#include <iostream>
#include <string>

Player::Player(const std::string& inName, const int& inAge)
	: mName(inName)
	, mAge(inAge)
{}

Player::~Player()
{
	mCardsInHand.clear();
	mOpenCards.clear();
}

void Player::ReceiveCards(const CardVec& inReceivedCards)
{
	// Iterate over vector ReceivedCards to push values to vector CardsInHand
	for (CardVec::const_iterator card = inReceivedCards.begin(); card != inReceivedCards.end(); ++card)
	{
		mCardsInHand.push_back(*card);
	}
}

void Player::RemoveCardFromHand(const CardPtr& inCard)
{
	// Remove the card from your hand. Called when a card is played
	mCardsInHand.erase(std::remove(mCardsInHand.begin(), mCardsInHand.end(), inCard), mCardsInHand.end());
}

bool Player::HasMaxOpenCards(const int inOpenCardLimit) const
{
	// Check if we have lost
	std::vector<int> openCardCount;
	openCardCount.resize(sCreatureMap.size());

	// Iterate over open cards and add the number of cards we have open for each creature
	for (CardVec::const_iterator card = mOpenCards.begin(); card != mOpenCards.end(); ++card)
	{
		openCardCount[(*card)->GetCreature()]++;
	}

	for (int val : openCardCount)
	{
		// If we have enough cards open for any creature type, return true
		if (val >= inOpenCardLimit)
		{
			return true;
		}
	}
	return false;
}

bool Player::HasCardsInHand() const
{
	// Check if the player has no cards in hand
	return !mCardsInHand.empty();
}