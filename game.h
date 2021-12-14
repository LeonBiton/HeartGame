#ifndef __GAME_H__
#define __GAME_H__
#include <stdio.h>
#include "ADTDefs.h"
#include "round.h"
#include "player.h"
#include "game.h"


typedef struct Game Game;

/*
Description : create new game
Input: number of players , score to end the game , how many humans play , size of hand and how many card to swapCards
Output: pointer to struct Game
Errors : return NULL
*/
Game * createGame(int _numberOfPlayers , int _scoreToEnd , int _humanPlayers , int _handSize , int _cardsToSwap);


/*
Description : run game
Input: pointer to struct Game
Output: return the winner of the game
Errors : return NULL
*/
int run (Game * _pGame);

/*
Description : destoy game, have protection from double free
Input: pointer to struct Game
Output: none
Errors : none
*/
void destroyGame(Game * _game);




#endif /* #ifndef __GAME_H__ */
