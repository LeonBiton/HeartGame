#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <stdio.h>
#include "vector.h"
#include "ADTDefs.h"
#include "card.h"

typedef struct Player Player;


/*
Description : create new player
Input: name , player is human? , id , hand size , how many card to swap
Output: pointer to struct Player
Errors : return NULL
*/
Player * createPlayer(char * _name , int _isHuman , int _id, int _handSize , int _cardsToSwap);


/*
Description : throw card from player hand
Input: pointer to struct player , index
Output: card the player droped or -1 if error.
Errors : -1 for errors
*/
int throwCard(Player * _player, int _index);

/*
Description : check if player have specific card in hand
Input: pointer to struct player , card we are searching
Output: index of the card if found , -1 if not
Errors : -1 if not found
*/
int haveSpecificCard(Player * _player , int _card);


/*
Description : check if player have specific set in hand
Input: pointer to struct player , set we are searching
Output: index of the first card in set if found , -1 if not
Errors : -1 if not found
*/
int haveSpecificSet(Player * _player , int _set);


/*
Description : add to player hand card
Input: pointer to struct player , card to add
Output: none
Errors : ERR_NULL_ERROR , ERR_OVERFLOW , ERR_REALLOCATION_FAILED
*/
ADTErr givePlayerCard(Player * _player , int _card);


/*
Description : destoy player, have protection from double free
Input: pointer to struct PLayer
Output: none
Errors : none
*/
void destroyPlayer(Player * _player);






#endif /* #ifndef __PLAYER_H__ */
