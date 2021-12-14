#include <stdio.h>
#include <stdlib.h>
#include "round.h"
#include "game.h"
#include "deck.h"
#include "ui.h"
#include "vector.h"
#include "ADTDefs.h"
#define MAGIC 567651
#define CARD_TO_START 39
#define HEART_POINTS 1
#define QUEEN_SPADE 13 


void dealCards(Round * _pRound , Deck * _pDeck);
Trick * createTrick(Round * pRound , int _trickNumber);
void destroyTrick (Trick * _trick);
ADTErr throwCards(Round * _pRound, Trick * _trick);
void takeLeadSet(int _card , Trick * _trick , Round * _pRound  );
ADTErr isValidThrow(Trick * _trick, Round * _pRound , int _player, int _card , int _turn , int _index );
int isCpuHaveSet(Round * _pRound , int _set , int _player);
int startWithoutHeart(Round * _pRound , int _player);
int checkTableHeart(Round * _pRound, Trick * _trick);
void whoLost(Round * _pRound , Trick * _trick);
void saveTrickScore(Round * _pRound , Trick * _trick);
void runTricks(Round * _pRound);
void swapCards(Round * _pRound, int _player1 , int _player2);
void switchCards(Round * _pRound);
void firstThrow(Round * _pRound, Trick * _trick , int _player);
int playerTurn(Round * _pRound, Trick * _trick , int _i , int _player);


struct Round
{
	struct Player ** m_Players;
	int m_roundNumber;
	int m_isHeartPlayed;
	int m_magicNumber;
	int m_numberOfPlayers;
	int m_cardsToSwap;
	int m_cardsInHand;
	int * m_roundScore;
	int m_whoStart;
	int m_numberOfTricks;
	int m_isFirstTrick;
};

struct Trick
{
	int m_leadSet;
	int m_whoLost;
	int m_magicNumber;
	struct Vector * m_table;
};


Round * createRound(int _rondNumber , Player ** _players , int _numberOfPlayers , int _cardsInHand , int _numberOfTricks , int _cardsToSwap)
{
	struct Round * pRound;
	if((pRound = (struct Round *) malloc (sizeof(struct Round))) == NULL)
	{
		return NULL;
	}
	pRound->m_roundNumber = _rondNumber;
	pRound->m_isHeartPlayed = 0;
	pRound->m_Players = _players;
	pRound->m_numberOfPlayers = _numberOfPlayers;
	pRound->m_cardsInHand = _cardsInHand;
	pRound->m_cardsToSwap = _cardsToSwap;
	pRound->m_numberOfTricks = _numberOfTricks;
	pRound->m_isFirstTrick = 1;
	pRound->m_roundScore = (int *) calloc (_numberOfPlayers , sizeof(int));
	if(pRound->m_roundScore ==NULL)
	{
		return NULL;
	}
	pRound->m_magicNumber = MAGIC;
	return pRound;
}

Trick * createTrick(Round * pRound , int _trickNumber)
{
	struct Trick * pTrick;
	pTrick = (struct Trick *) malloc (sizeof(struct Trick));
	pTrick->m_table = VectorCreate(pRound->m_numberOfPlayers , 0);
	pTrick->m_whoLost = pRound->m_whoStart;
	pTrick->m_magicNumber = MAGIC;
}

int *  startRound(int _roundNumber ,Round * _pRound )
{
	int i;
	struct Deck * pdeck;
	pdeck = createDeck(1);
	if(pdeck == NULL)
	{
		return NULL;
	}
	sheffleDeck(pdeck);
	dealCards(_pRound ,pdeck);
	printPlayerHand(_pRound->m_Players[0]);
	switchCards(_pRound);
	printPlayerHand(_pRound->m_Players[0]);
	runTricks(_pRound);
	destroyDeck(pdeck);
	return _pRound->m_roundScore;
}

void runTricks(Round * _pRound)
{
	int status , i , j , check;
	for(j = 1 ; j < _pRound->m_numberOfTricks + 1 ; j++)
	{
		struct Trick * pTrick;
		pTrick = createTrick(_pRound , 0);
		throwCards(_pRound , pTrick);
		if(_pRound->m_isHeartPlayed == 0)
		{
			check = checkTableHeart(_pRound, pTrick);
			if(check == 1)
			{
				_pRound->m_isHeartPlayed = 1;
			}
		}
		whoLost(_pRound , pTrick);
		saveTrickScore(_pRound , pTrick);
		roundScore(_pRound->m_roundScore ,_pRound->m_numberOfPlayers);
		destroyTrick(pTrick);
	}
}

int swapStrategy(int _first , int _second)
{
	if(RANK(_first) < RANK(_second))
	{
		return 1;
	}
	return 0;
}


ADTErr throwCards(Round * _pRound, Trick * _trick)
{
	int i ,status,indexStart , cpuIndex, cardDrop, turn =_pRound->m_whoStart, playerChoice , check , cardCheck ;
	PrintplayerStart(turn + 1);
	printPlayerHand(_pRound->m_Players[0]);

	for(i = 0 ; i<_pRound->m_numberOfPlayers ; i++)
	{
		if(_pRound->m_isFirstTrick == 1)/*first trick throw 2 club first*/
		{
			firstThrow(_pRound, _trick ,turn);
			turn = (turn+1) % _pRound->m_numberOfPlayers;
			continue;
		}
		if(isPlayerHuman(_pRound->m_Players[turn]) == 1)/*player turn*/
		{
			cardDrop = playerTurn(_pRound, _trick , i ,turn);
			turn = (turn+1) % _pRound->m_numberOfPlayers;
			if(i == 0)
			{
				takeLeadSet(cardDrop , _trick ,_pRound);
			}
			continue;
		}
		if(_pRound->m_isHeartPlayed == 0 && i == 0)/*first throw when no heart played*/
		{
			indexStart = startWithoutHeart(_pRound , turn);
			cardDrop = throwCard(_pRound->m_Players[turn], indexStart);
			VectorAdd(_trick->m_table, cardDrop);
			takeLeadSet(cardDrop , _trick ,_pRound);
			turn = (turn+1) % _pRound->m_numberOfPlayers;
			continue;
		}
		cpuIndex = isCpuHaveSet(_pRound ,_trick->m_leadSet , turn );/*cpu answer to throw*/
		if(cpuIndex != -1 && i != 0)
		{
			cardDrop = throwCard(_pRound->m_Players[turn], cpuIndex);
			VectorAdd(_trick->m_table, cardDrop);
			turn = (turn+1) % _pRound->m_numberOfPlayers;
			continue;
		}
		cardDrop = throwCard(_pRound->m_Players[turn], 0);/*throw first card when no limitation*/
		if(i == 0)
		{
			takeLeadSet(cardDrop , _trick ,_pRound);
		}
		VectorAdd(_trick->m_table, cardDrop);
		turn = (turn+1) % _pRound->m_numberOfPlayers;
	}
	printTable(_trick->m_table);
}

int playerTurn(Round * _pRound, Trick * _trick , int _i , int _player)
{
	int playerChoice, cardCheck , check , cardDrop;
	char * str = "Enter index of the card you want to throw :";
	printTable(_trick->m_table);
	printPlayerChoice( str, &playerChoice);
	cardCheck = getCard(_pRound->m_Players[_player] , playerChoice);
	check = isValidThrow(_trick, _pRound , _player, cardCheck , _i , playerChoice );
	while(check != ERR_OK)
	{
		printPlayerChoice( str, &playerChoice);
		cardCheck = getCard(_pRound->m_Players[_player] , playerChoice);
		check = isValidThrow(_trick, _pRound , _player, cardCheck , _i , playerChoice );
	}
	cardDrop = throwCard(_pRound->m_Players[_player],playerChoice );
	VectorAdd(_trick->m_table, cardDrop);
	return cardDrop;
}

void firstThrow(Round * _pRound, Trick * _trick , int _player)
{
	int indexStart, cardDrop;
	indexStart = haveSpecificCard(_pRound->m_Players[_player] ,CARD_TO_START );
	cardDrop = throwCard(_pRound->m_Players[_player],indexStart );
	takeLeadSet(cardDrop , _trick ,_pRound);
	VectorAdd(_trick->m_table, cardDrop);
	_pRound->m_isFirstTrick = 0;
}

int checkTableHeart(Round * _pRound, Trick * _trick)
{
	int i , item;
	for(i = 0 ; i<_pRound->m_numberOfPlayers ; i++)
	{
		VectorGet(_trick->m_table, i, &item);
		if(SUIT(item) == SUIT(HEART))
		{
			return 1;
		}
	}
	return 0;
}

int startWithoutHeart(Round * _pRound , int _player)
{
	int index;
	index = haveSpecificSet(_pRound->m_Players[_player] ,SPADE );

	if(index == -1)
	{
		index = haveSpecificSet(_pRound->m_Players[_player] ,DIAMOND );
	}
	if(index == -1)
	{
		index = haveSpecificSet(_pRound->m_Players[_player] ,CLUB );
	}
	return index;
}

void switchCards(Round * _pRound)
{
	int i;
	switch(_pRound->m_roundNumber % _pRound->m_numberOfPlayers)/*every player throw 3 cards to swap array*/
	{
		case 1:
			for(i = 0 ; i <_pRound->m_numberOfPlayers ; i++)
			{
				swapCards(_pRound , i , (i + 1) % _pRound->m_numberOfPlayers );
			}
			break;

		case 2:
			for(i = 0 ; i <_pRound->m_numberOfPlayers ; i++)
			{
				if(i == 0)
				{
					swapCards(_pRound , i ,_pRound->m_numberOfPlayers - 1 );
					continue;
				}
				swapCards(_pRound , i , (i - 1) % _pRound->m_numberOfPlayers );
			}
			break;
		case 3:
			for(i = 0 ; i <_pRound->m_numberOfPlayers ; i++)
			{
				swapCards(_pRound , i , (i + 2) % _pRound->m_numberOfPlayers );
			}
			break;
	}
	for(i = 0; i<_pRound->m_numberOfPlayers ; i++)/*add the swap array to players hand*/
	{
		addSwapCards(_pRound->m_Players[i]);
	}
}


void swapCards(Round * _pRound, int _player1 , int _player2)
{
	int card , i;
	char * invalid = "wrond index, pick again.\n";
	char * throw = "Enter index of the card you want to swap : ";
	if(isPlayerHuman(_pRound->m_Players[_player1]) == 1)
	{
		for(i = 0 ; i<_pRound->m_cardsToSwap ; i++)
		{
			printPlayerChoice(throw , &card);
			card = throwCard(_pRound->m_Players[_player1], card);
			while(card == -1)
			{
				printMesseage(invalid);
				printPlayerHand(_pRound->m_Players[_player1]);
				printPlayerChoice(throw , &card);
				card = throwCard(_pRound->m_Players[_player1], card);
			}
			printPlayerHand(_pRound->m_Players[_player1]);
			cardToSwap(_pRound->m_Players[_player2] , card);
			if(card == CARD_TO_START)
			{
				_pRound->m_whoStart = _player2;
			}
		}
		return;
	}
	card = throwCard(_pRound->m_Players[_player1], cpuSwap(_pRound->m_Players[_player1] , swapStrategy));
	cardToSwap(_pRound->m_Players[_player2] , card);
	card = throwCard(_pRound->m_Players[_player1], cpuSwap(_pRound->m_Players[_player1] , swapStrategy));
	cardToSwap(_pRound->m_Players[_player2] , card);
	card = throwCard(_pRound->m_Players[_player1], cpuSwap(_pRound->m_Players[_player1] , swapStrategy));
	cardToSwap(_pRound->m_Players[_player2] , card);
}


void whoLost(Round * _pRound , Trick * _trick)
{
	int lostCard ,playerLost, i = 1 , item , temp;
	size_t size;
	playerLost = _pRound->m_whoStart;
	temp = playerLost;
	VectorItemsNum(_trick->m_table, &size);
	VectorGet(_trick->m_table, 0, &lostCard);

	while(i<_pRound->m_numberOfPlayers)
	{
		playerLost = (playerLost + 1) % _pRound->m_numberOfPlayers;
		VectorGet(_trick->m_table, i, &item);
		if(SUIT(item) == _trick->m_leadSet && item > lostCard)
		{	
			_trick->m_whoLost = playerLost;
			_pRound->m_whoStart = playerLost;
			lostCard = item;
		}
		i++;
	}
	PrintplayerLost(_trick->m_whoLost + 1);
}

void saveTrickScore(Round * _pRound , Trick * _trick)
{
	int i , item , points = 0;
	for(i = 0 ;i<_pRound->m_numberOfPlayers ; i++)
	{
		VectorGet(_trick->m_table, i, &item);
		if(SUIT(item) == HEART)
		{
			points += HEART_POINTS;
		}
		if(item == SPADE_Q)
		{
			points += QUEEN_SPADE;
		}
	}
	_pRound->m_roundScore[_trick->m_whoLost] += points;
}


void takeLeadSet(int _card , Trick * _trick, Round * _pRound )
{
	_trick->m_leadSet = SUIT(_card);
}

ADTErr isValidThrow(Trick * _trick, Round * _pRound , int _player, int _card , int _turn , int _index )
{
	int index,checkHearts,status;
	char * invalid = "invalid index";
	char * heart = "canot play heart yet";
	index = haveSpecificSet(_pRound->m_Players[_player] ,_trick->m_leadSet);
	status = checkRange(_pRound->m_Players[_player] , _index);
	if(status != ERR_OK)/*check valid index*/
	{
		printMesseage(invalid);
		return ERR_INVALID_THROW;
	}
	if(_turn == 0)
	{
		if(SUIT(_card) == HEART)
		{
			checkHearts = checkOnlyHearts(_pRound->m_Players[_player]);
			if(_pRound->m_isHeartPlayed == 0 && checkHearts == 0)/*player have cards that are not heart and heart didnt played yet*/
			{
				printMesseage(heart);
				return ERR_INVALID_THROW;
			}
		}
		return ERR_OK;
	}
	if(index != -1 && SUIT(_card) != _trick->m_leadSet)/*player have leading set card and he throw card not from leading set*/
	{
		printInvalidSet(_trick->m_leadSet);
		return ERR_INVALID_THROW;
	}
	return ERR_OK;
}

int isCpuHaveSet(Round * _pRound , int _set , int _player)
{
	int index;
	index = haveSpecificSet(_pRound->m_Players[_player] ,_set);
	if(index != -1)
	{
		return index;
	}
	return -1;
}


void dealCards(Round * _pRound , Deck * _pDeck)
{
	int card,i,j;
	for(i = 0 ; i<_pRound->m_cardsInHand ; i++)
	{
		for(j = 0 ; j<_pRound->m_numberOfPlayers ; j++)
		{
			card = drawCard(_pDeck);
			givePlayerCard(_pRound->m_Players[j] , card);
			if(card == CARD_TO_START)
			{
				_pRound->m_whoStart = j;
			}
		}
	}
}


void destroyRound (Round * _round)
{
	if(_round != NULL && _round->m_magicNumber == MAGIC)
	{
		free(_round->m_roundScore);
		free(_round);
	}
	_round->m_magicNumber = 0;
}

void destroyTrick (Trick * _trick)
{
	if(_trick != NULL && _trick->m_magicNumber == MAGIC)
	{
		VectorDestroy(_trick->m_table);
		free(_trick);
	}
	_trick->m_magicNumber = 0;
}














