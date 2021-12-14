#ifndef __DECK_H__
#define __DECK_H__
#include <stdio.h>
#include "ADTDefs.h"
#include "vector.h"
#include "card.h"
#include "deck.h"


typedef struct Deck Deck;


/*
Description : create new deck
Input: number of decks
Output: pointer to struct Deck
Errors : return NULL
*/
Deck * createDeck(int _numberOfDucks);


/*
Description : draw card from deck
Input: pointer to struct Deck
Output: card we draw
Errors : ERR_NULL_ERROR , ERR_UNDERFLOW.
*/
int drawCard(Deck * _deck);

/*
Description : sheffle the deck
Input: pointer to struct Deck
Output: none
Errors : none.
*/
void sheffleDeck(Deck * _deck);

/*void returnCardToDeck(Deck * _deck);*/

void destroyDeck(Deck * _deck);












#endif /* #ifndef __DECK_H__ */
