#include "Card.h"

Card::Card(const Creature& inCreature, const Color& inColor)
	: mCreature(inCreature)
	, mColor(inColor)
{}

// Create the full name using the maps
std::string Card::GetName() const
{
	return sColorMap.at(mColor) + " " + sCreatureMap.at(mCreature);
}