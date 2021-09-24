#include "GameController.h"

int main()
{
	// Create a controller and let it run. It will take care of the game
	GameController g;
	g.Setup();
	g.Run();
	return 0;
}