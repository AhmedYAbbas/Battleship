#include "Battleship/Game.h"
#include "Battleship/Player.h"

int main()
{
	Game game("Player 1", "Player 2");
	game.Start();
	game.Run();
}