#include <algorithm>
#include <iostream>
#include <random>
#include "GameModel.h"

void Game::Initialize()
{
	// Create all cards for playing the game
	for (int color = 0; color < Color::kColorCount; ++color)
	{
		for (int creature = 0; creature < Creature::kCreatureCount; ++creature)
		{
			CardPtr card = std::make_shared<Card>((Creature)creature, (Color)color);
			mCards.push_back(card);
		}
	}

	// Set open card limit to 4, change if it is 2 player game
	mOpenCardLimit = 4;
	mPlayers.clear();
}

void Game::AddPlayer(const PlayerPtr& inPlayer)
{
	// Add every player to our vector
	mPlayers.push_back(inPlayer);

	// The youngest player is the dealer
	if (!mDealer || mDealer->GetAge() > inPlayer->GetAge())
	{
		mDealer = inPlayer;
	}
}

void Game::DistributeCards()
{
	// Shuffle cards
	std::shuffle(std::begin(mCards), std::end(mCards), std::default_random_engine());

	if (mPlayers.size() == 2)
	{
		// Burn 10 cards and set open card limit to 5 if there are 2 players
		mCards.resize(mCards.size() - 10);
		mOpenCardLimit = 5;
	}

	// Distribute the cards evenly among all players
	int cardsToDeal = mCards.size();
	int playersLeft = mPlayers.size();
	for (const PlayerPtr& player : mPlayers)
	{
		int cardsForPlayer = cardsToDeal / playersLeft;
		CardVec tempVec(mCards.begin() + (mCards.size() - cardsToDeal), mCards.begin() + (mCards.size() - cardsToDeal) + cardsForPlayer);
		player->ReceiveCards(tempVec);
		cardsToDeal -= cardsForPlayer;
		--playersLeft;
	}
}

bool Game::HasEnded()
{
	// If the dealer does not have any cards in hand or has more open cards than required,
	// end the game and declare the loser
	if (!mDealer->HasCardsInHand() || mDealer->HasMaxOpenCards(mOpenCardLimit))
	{
		return true;;
	}

	return false;
}

PlayerVec Game::GetPossibleOpponents() const
{
	// return all players except the dealer
	PlayerVec players = mPlayers;
	players.erase(std::remove(players.begin(), players.end(), mDealer), players.end());
	return players;
}