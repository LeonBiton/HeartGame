#include <stdio.h>
#include "deck.h"
#include "sort.h"
#include "ADTDefs.h"
#define MAGIC 65467

struct Deck
{
	struct Vector * m_deck;
	int m_magicNumber;
	int m_nCards;
};


Deck * createDeck(int _numberOfDucks)
{
	int i;
	struct Vector * pVec;
	struct Deck * pdeck;
	pVec = VectorCreate(52,0);
	if((pdeck = (struct Deck *) malloc (sizeof(struct Deck))) == NULL)
	{
		return NULL;
	}
	pdeck->m_deck = pVec;
	pdeck->m_magicNumber = MAGIC;
	pdeck->m_nCards = 52;
	for(i = 0; i<52 ; i++)
	{
		VectorAdd(pVec , i);
	}
	return pdeck;
}

int drawCard(Deck * _deck)
{
	int card , status;
	status = VectorDelete(_deck->m_deck , &card);
	if(status != ERR_OK)
	{
		return status;
	}
	return card;
}


void sheffleDeck(Deck* _deck)
{
	int i , j , card1, card2;
	
	if (_deck->m_nCards <= 1)
	{
		return;
	}
	srand(time(0));
	for (i = 0; i < _deck->m_nCards - 1; i++) 
    {
    	j = i + rand() / (RAND_MAX / (_deck->m_nCards - i) );
    	
    	VectorGet(_deck->m_deck, i, &card1);
		VectorGet(_deck->m_deck, j, &card2);
    	swap( i, j, card1, card2 , _deck->m_deck);
    }
}

void destroyDeck(Deck * _deck)
{
	if(_deck != NULL && _deck->m_magicNumber == MAGIC)
	{
		free(_deck);
		VectorDestroy(_deck->m_deck);
	}
	_deck->m_magicNumber = 0;
}


