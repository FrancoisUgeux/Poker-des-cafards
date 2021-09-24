#pragma once
#include "Player.h"
#include "PlayerView.h"

class PlayerController
{
public:
	PlayerController(const PlayerViewPtr&);

	// Play the card and return who lost the round
	PlayerPtr PlayCard(PlayerPtr&, const PlayerVec&);

	// Use this API if the creature and card are already known
	PlayerPtr PlayCard(const PlayerPtr&, const PlayerVec&, const CardPtr&, const Creature&);

private:
	PlayerViewPtr			mPlayerView;
};

using PlayerControllerPtr = std::shared_ptr<PlayerController>;