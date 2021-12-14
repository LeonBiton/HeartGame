#ifndef __ROUND_H__
#define __ROUND_H__
#include <stdio.h>
#include "ADTDefs.h"
#include "player.h"
#include "game.h"
#include "card.h"

typedef struct Round Round;

typedef struct Trick Trick;

/*
Description : create new round
Input: round number , array of players pointer , number of players , how many cards in hand , how many tricks in round, how many card to swap
Output: pointer to struct Round
Errors : return NULL
*/
Round * createRound(int _rondNumber , Player ** _players , int _numberOfPlayers , int _cardsInHand , int _numberOfTricks , int _cardsToSwap);


/*
Description : start new round
Input: round number , pointer to struct Round
Output: score of the round
Errors : return NULL
*/
int * startRound(int _roundNumber ,Round * _pRound );


/*
Description : destoy round, have protection from double free
Input: pointer to struct Round
Output: none
Errors : none
*/
void destroyRound (Round * _round);




#endif /* #ifndef __ROUND_H__ */
