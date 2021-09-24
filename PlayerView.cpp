#include <iostream>

#include "Card.h"
#include "PlayerView.h"

PlayerPtr PlayerView::SelectOpponent(const PlayerVec& inPlayerList)
{
	PlayerVec playerList = inPlayerList;

	// Set the default target as the first player in the list
	int selectedPlayer = 0;
	if (playerList.size() > 1)
	{
		// If there are more than one opponent players
		// Display player list and decide who to target
		std::cout << "Potential opponents:" << std::endl;
		int playerIdx = 0;
		for (PlayerVec::const_iterator player = playerList.begin(); player != playerList.end(); ++player)
		{
			std::cout << playerIdx++ << ". " << (*player)->GetName() << std::endl;
		}

		// Select an opponent 
		std::cout << "Select the player number you would like to challenge" << std::endl;
		std::cin >> selectedPlayer;

		// Validate user input
		while (std::cin.fail() || selectedPlayer < 0 || selectedPlayer >= playerList.size())
		{
			std::cout << "Your last selection was invalid. Please enter a valid player number." << std::endl;
			std::cin >> selectedPlayer;
		}
	}

	PlayerPtr opponent = playerList.at(selectedPlayer);
	std::cout << "You have chosen " << opponent->GetName() << " as opponent" << std::endl;
	return opponent;
}

Creature PlayerView::GetCreatureToAnnounce()
{
	// Ask which creature should be announced
	std::cout << "Creatures available:" << std::endl;
	for (CreatureMap::const_iterator creature = sCreatureMap.begin(); creature != sCreatureMap.end(); ++creature)
	{
		std::cout << creature->first << ". " << creature->second << std::endl;
	}

	// Select a creature
	int selectedCreature;
	std::cout << "Select what creature you would like to declare the card as:" << std::endl;
	std::cin >> selectedCreature;

	// Validate user input
	while (std::cin.fail() || selectedCreature < 0 || selectedCreature >= sCreatureMap.size())
	{
		std::cout << "Your last selection was invalid. Please enter a valid creature number." << std::endl;
		std::cin >> selectedCreature;
	}

	return static_cast<Creature>(selectedCreature);
}

CardPtr PlayerView::GetCardToPlay(const PlayerPtr& inPlayer)
{
	// It is a new turn. Print out the player name and tell them it is their turn to platy
	std::cout << "\n\n" << inPlayer->GetName() << ", it is your turn to play a card." << std::endl;

	CardVec cards = inPlayer->GetCardsInHand();
	std::cout << "Cards in your hand:" << std::endl;
	int cardIdx = 0;
	for (CardVec::const_iterator card = cards.begin(); card != cards.end(); ++card)
	{
		std::cout << cardIdx++ << ". " << (*card)->GetName() << std::endl;
	}

	// Select the card to deal 
	int cardToDeal;
	std::cout << "Enter the card number you would like to deal" << std::endl;
	std::cin >> cardToDeal;

	// Validate user input
	while (std::cin.fail() || cardToDeal < 0 || cardToDeal >= cards.size())
	{
		std::cout << "Your last selection was invalid. Please enter a valid card number." << std::endl;
		std::cin >> cardToDeal;
	}

	return cards.at(cardToDeal);
}

void PlayerView::ShowOpenCards(const PlayerPtr& inPlayer)
{
	std::cout << "\n\n" << inPlayer->GetName() << ", the cards open in your hand are -" << std::endl;

	CardVec cards = inPlayer->GetOpenCards();
	int cardIdx = 0;
	for (CardVec::const_iterator card = cards.begin(); card != cards.end(); ++card)
	{
		std::cout << cardIdx++ << ". " << (*card)->GetName() << std::endl;
	}
}

void PlayerView::DeclarePlayerChoice(const PlayerPtr& inPlayer)
{
	std::cout << "\n" << inPlayer->GetName() << ", It is your choice" << std::endl;
}

void PlayerView::DeclareRoundLoss(const PlayerPtr& inPlayer)
{
	std::cout << "\n" << inPlayer->GetName() << " has lost this round" << std::endl;
	ShowOpenCards(inPlayer);
}

bool PlayerView::MakeDecision()
{
	int selectedOption;
	// We have to make a choice to either agree with the dealer or disagree
	std::cout << "You have two options:'" << std::endl;
	std::cout << "1. True, that means you agree with dealer " << std::endl;
	std::cout << "2. False, that means you disagree with dealer" << std::endl;
	std::cin >> selectedOption;

	// Validate user input
	while (std::cin.fail() || selectedOption <= 0 || selectedOption > 2)
	{
		std::cout << "Your last selection was invalid. Please enter a valid option." << std::endl;
		std::cin >> selectedOption;
	}

	return (selectedOption == 1);
}

bool PlayerView::GetPassAndCreatureChoice(Creature& inOutCreature)
{
	int selectedOption;
	std::cout << "You have two options:" << std::endl;
	std::cout << "1. Accept the card" << std::endl;
	std::cout << "2. Pass the card to another player" << std::endl;
	std::cin >> selectedOption;

	// Validate user input
	while (std::cin.fail() || selectedOption <= 0 || selectedOption > 2)
	{
		std::cout << "Your last selection was invalid. Please enter a valid option." << std::endl;
		std::cin >> selectedOption;
	}

	if (selectedOption == 2)
	{
		// As we are passing, take a peek at the actual card
		std::cout << "Card dealt was a " << sCreatureMap.at(inOutCreature) << std::endl;

		// Ask if he wants to keep the creature called earlier or change
		// if we want to change, show creature list and select
		std::cout << "Do you want to change the creature selection? Choose one of the options:" << std::endl;
		std::cout << "1. Yes" << std::endl;
		std::cout << "2. No" << std::endl;
		std::cin >> selectedOption;

		// Validate user input
		while (std::cin.fail() || selectedOption <= 0 || selectedOption > 2)
		{
			std::cout << "Your last selection was invalid. Please enter a valid option." << std::endl;
			std::cin >> selectedOption;
		}

		if (selectedOption == 1)
		{
			inOutCreature = GetCreatureToAnnounce();
		}
		return true;
	}
	return false;
}