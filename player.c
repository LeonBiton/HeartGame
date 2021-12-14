#include <stdio.h>
#include <stdlib.h> /*for size_t and malloc*/
#include "player.h"
#include "ADTDefs.h"
#include "sort.h"
#include "ui.h"
#include "vector.h"
#define MAGIC 65434

struct Player
{
	int m_isHumam;
	int m_id;
	char * m_name;
	int m_roundScore;
	struct Vector * m_hand;
	struct Vector * m_swapArray;
	int m_handSize;
	int m_cardsToSwap;
	int m_magicNumber;
};


Player * createPlayer(char * _name , int _isHuman , int _id, int _handSize , int _cardsToSwap)
{
	struct Vector * pVec;
	struct Vector * pSwap;
	struct Player * pPlayer;
	pVec = VectorCreate(_handSize,10);
	pSwap = VectorCreate(_cardsToSwap , 0);
	if((pPlayer = (struct Player *) malloc (sizeof(struct Player))) == NULL)
	{
		return NULL;
	}
	pPlayer->m_magicNumber = MAGIC;
	pPlayer->m_roundScore = 0;
	pPlayer->m_hand = pVec;
	pPlayer->m_handSize = _handSize;
	pPlayer->m_swapArray = pSwap;
	pPlayer->m_name = _name;
	pPlayer->m_cardsToSwap = _cardsToSwap;
	pPlayer->m_id = _id;
	pPlayer->m_isHumam = _isHuman;
	return pPlayer;
}

ADTErr givePlayerCard(Player * _player , int _card)
{
	int status;
	status = VectorAdd(_player->m_hand , _card);
	if(status != ERR_OK)
	{
		return status;
	}
	BubbleSort(_player->m_hand);
}

int throwCard(Player * _player, int _index)
{
	int item , item2,cardDrop,status;
	size_t size;
	VectorItemsNum(_player->m_hand , &size);
	status = VectorGet(_player->m_hand ,_index , &item);
	if(status != ERR_OK)
	{
		return -1;
	}
	VectorGet(_player->m_hand , size-1 , &item2);
	swap(_index , size-1 ,item ,item2 , _player->m_hand);
	VectorDelete(_player->m_hand , &cardDrop);
	BubbleSort(_player->m_hand);
	return cardDrop;
}

int isPlayerHuman(Player * _player)
{
	return _player->m_isHumam;
}

int cpuSwap(Player * _player , int(*funcPointer)(int _first , int _second))
{
	int i , swap , swapIndex = 0 , item;
	size_t size;
	VectorGet(_player->m_hand, 0, &swap);
	VectorItemsNum(_player->m_hand, &size);
	for(i = 1; i<size ; i++)
	{
		VectorGet(_player->m_hand, i, &item);
		if((*funcPointer)(swap , item))
		{
			swap = item;
			swapIndex = i;
		}
	}
	return swapIndex;
}


ADTErr cardToSwap(Player * _player , int _card)
{
	int status;
	status = VectorAdd(_player->m_swapArray , _card);
	if(status != ERR_OK)
	{
		return status;
	}
}

ADTErr addSwapCards(Player * _player)
{
	int i , item , status;
	for(i = 0 ; i<_player->m_cardsToSwap ; i++)
	{
		status = VectorDelete(_player->m_swapArray, &item);
		if(status != ERR_OK)
		{
			return status;
		}
		status = VectorAdd(_player->m_hand , item);
		if(status != ERR_OK)
		{
			return status;
		}
	}
	BubbleSort(_player->m_hand);
}

ADTErr checkRange(Player * _player , int _index)
{
	int item , status;
	status = VectorGet(_player->m_hand, _index, &item);
	return status;
}

int getCard(Player * _player , int _index)
{
	int item;
	VectorGet(_player->m_hand, _index, &item);
	return item;
}

int haveSpecificCard(Player * _player , int _card)
{
	int i , item;
	size_t size;
	VectorItemsNum(_player->m_hand , &size);
	for(i = 0; i<size;i++)
	{
		VectorGet(_player->m_hand, i, &item);
		if(item == _card)
		{
			return i;
		}
	}	
	return -1;
}

int haveSpecificSet(Player * _player , int _set)
{
	int i , item;
	size_t size;
	VectorItemsNum(_player->m_hand , &size);
	for(i = 0; i<size ;i++)
	{
		VectorGet(_player->m_hand, i, &item);
		if(SUIT(item) == _set)
		{
			return i;
		}
	}	
	return -1;
}



int checkOnlyHearts(Player * _player)
{
	int check , item;
	size_t size;
	VectorItemsNum(_player->m_hand , &size);
	VectorGet(_player->m_hand, size-1, &item);
	if(SUIT(item) == HEART)
	{
		return 1;
	}
	return 0;
}

void printPlayerHand (Player * _player)
{
	printHand(_player->m_hand);
}

void destroyPlayer(Player * _player)
{
	if(_player != NULL && _player->m_magicNumber == MAGIC)
	{
		VectorDestroy(_player->m_hand);
		free(_player);
	}
	_player->m_magicNumber = 0;
}





