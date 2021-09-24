#pragma once
#include "Card.h"
#include <string>

// Forward declare Player class for PlayerVec to be used in Player
class Player;
using PlayerPtr = std::shared_ptr<Player>;
using PlayerVec = std::vector<PlayerPtr>;

class Player :
	public std::enable_shared_from_this <Player>
{
public:

	// Declare Constructor with Name and Age of player
	Player(const std::string&, const int&);
	
	// Delete Implicit Constructor
	Player() = delete;
	// Delete Implicit Copy Constructor
	Player(const Player&) = delete;
	// Delete copy-assignment operator
	Player& operator=(const Player&) = delete;

	// Declare Destructor
	~Player();

	// Receive cards from game at the beginning 
	void ReceiveCards(const CardVec&);

	// Getter function for Player Name
	inline std::string GetName() const { return mName; }
	inline int GetAge() const { return mAge; }
	inline CardVec GetCardsInHand() const { return mCardsInHand; }
	inline CardVec GetOpenCards() const { return mOpenCards; }

	// Adds card to open cards
	inline void AddToOpenCards(const CardPtr& inCard) { mOpenCards.push_back(inCard); }

	// Removes the card from hand
	void RemoveCardFromHand(const CardPtr&);

	// Checks whether a player has max open cards of one creature type
	bool HasMaxOpenCards(const int inOpenCardLimit) const;

	// Checks whether there are any cards in hand
	bool HasCardsInHand() const;

private:
	// Members to store the name and age of the player
	std::string mName;
	int mAge;

	// Vector of Cards in Hand for a player
	CardVec mCardsInHand;
	// Vector of Open cards for a player
	CardVec mOpenCards;
};

