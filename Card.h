#pragma once
#include <map>
#include <memory>
#include <vector>

// Defining all colors
enum Color {
	kRed = 0,
	kGreen,
	kYellow,
	kBlue,
	kPink,
	kOrange,
	kViolet,
	kBrown,
	kColorCount
};

// Defining all creatures
enum Creature {
	kBear = 0,
	kBat,
	kToad,
	kScorpion,
	kLadyBug,
	kCockroach,
	kWorm,
	kFly,
	kCreatureCount
};

using ColorMap = std::map <Color, std::string>;
using CreatureMap = std::map <Creature, std::string>;

// Keeping a map of color enum to their names
static const 
ColorMap sColorMap = {
		{ Color::kRed, "Red" },
		{ Color::kGreen, "Green" },
		{ Color::kYellow, "Yellow" },
		{ Color::kBlue, "Blue" },
		{ Color::kPink, "Pink" },
		{ Color::kOrange, "Orange" },
		{ Color::kViolet, "Violet" },
		{ Color::kBrown, "Brown" }
};

// Keeping a map of creatures enum to their names
static const 
CreatureMap sCreatureMap = {
		{ Creature::kBear, "Bear" },
		{ Creature::kBat, "Bat" },
		{ Creature::kToad, "Toad" },
		{ Creature::kScorpion, "Scorpion" },
		{ Creature::kLadyBug, "LadyBug" },
		{ Creature::kCockroach, "Cockroach" },
		{ Creature::kWorm, "Worm" },
		{ Creature::kFly, "Fly" }
};

class Card
{
public: 
	// Declare Constructor
	Card(const Creature&, const Color&);

	// Delete Implicit Constructor
	Card() = delete;
	// Delete Implicit Copy Constructor
	Card(const Card&) = delete;
	// Delete copy-assignment operator
	Card& operator=(const Card&) = delete;

	// Declare Destructor
	~Card() = default;

	// Getter functions for Color and Creature
	inline Color GetColor() const { return mColor; }
	inline Creature GetCreature() const { return mCreature; }

	// Get the name of the card as string
	std::string GetName() const;

private:
	Color mColor;
	Creature mCreature;
};

using CardPtr = std::shared_ptr<Card>;
using CardVec = std::vector<CardPtr>;