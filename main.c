#include <stdio.h>
#include "round.h"
#include "player.h"
#include "vector.h"
#include "game.h"
#include "deck.h"


int main()
{
	Game * pGame;
	pGame = createGame(4 , 100 , 1, 13 , 3);
	run(pGame);

	

	return 0;
}
