#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "player.h"
#include "ui.h"
#include "ADTDefs.h"
#define MAGIC 37378


void addGlobalScore(Game * _pGame, int * _arr);

struct Game
{
	int * m_globalScore;
	struct Player ** m_Players;
	int m_scoreToEnd;
	int m_numberOfPlayers;
	int m_cardsInHand;
	int m_magicNumber;
};

Game * createGame(int _numberOfPlayers , int _scoreToEnd , int _humanPlayers , int _handSize , int _cardsToSwap)
{
	int i;
	struct Game * pgame;
	if(_numberOfPlayers <= 1)
	{
		return NULL;
	}
	pgame = (struct Game *) malloc (sizeof(struct Game));
	pgame->m_scoreToEnd = _scoreToEnd;
	pgame->m_numberOfPlayers = _numberOfPlayers;
	pgame->m_cardsInHand = _handSize;
	pgame->m_magicNumber = MAGIC;
	pgame->m_globalScore = ( int *) calloc(_numberOfPlayers , sizeof(int));
	pgame->m_Players = (struct Player **) malloc(_numberOfPlayers * sizeof(struct Player *));
	if(pgame->m_Players == NULL|| pgame->m_globalScore == NULL|| pgame == NULL)
	{
		return 	NULL;
	}
	for(i = 0 ; i<_humanPlayers ; i++)
	{
		pgame->m_Players[i] = createPlayer("Player" , 1 , i + 1, _handSize , _cardsToSwap);
		if(pgame->m_Players[i] == NULL)
		{
			return NULL;
		}
	}
	for( ; i< _numberOfPlayers ;i++ )
	{
		pgame->m_Players[i] = createPlayer("CPU" , 0 , i + 1, _handSize, _cardsToSwap);
		if(pgame->m_Players[i] == NULL)
		{
			return NULL;
		}
	}
	return pgame;
}

int run (Game * _pGame)
{
	int * roundScore ,check , winner , i = 1;
	while(i)
	{
		Round * pRound;
		pRound = createRound(i,_pGame->m_Players ,_pGame->m_numberOfPlayers ,_pGame->m_cardsInHand , 13 , 3);
		roundScore = startRound(0 , pRound);
		addGlobalScore(_pGame , roundScore);
		check = checkForWinner(_pGame);
		if(check == 1)
		{
			winner = whoWin(_pGame);
			printWinner(winner);
			return winner;
		}
		destroyRound(pRound);
		i++;
	}
}

void addGlobalScore(Game * _pGame, int * _arr)
{
	int i;
	for(i = 0 ; i<_pGame->m_numberOfPlayers; i++)
	{
		_pGame->m_globalScore[i] += _arr[i];
		_arr[i] = 0;
	}
	printGlobalScore(_pGame->m_globalScore , _pGame->m_numberOfPlayers);
}

int whoWin(Game * _pGame)
{
	int i , smallest , smallestScore;
	smallestScore = _pGame->m_globalScore[0];
	smallest = 0;
	for(i = 1 ; i<_pGame->m_numberOfPlayers; i++)
	{
		if(_pGame->m_globalScore[i] < smallestScore)
		{
			smallest = i;
			smallestScore = _pGame->m_globalScore[i];
		}
	}
	return smallest;
}

int checkForWinner(Game * _pGame)
{
	int i;
	for(i = 0 ; i<_pGame->m_numberOfPlayers; i++)
	{
		if(_pGame->m_globalScore[i] >= 100)
		{
			return 1;
		}
	}
	return 0;
}

void destroyGame(Game * _game)
{
	int i;
	if(_game != NULL && _game->m_magicNumber == MAGIC)
	{
		free(_game->m_globalScore);
		for(i = 0; i<_game->m_numberOfPlayers ; i++)
		{
			free(_game->m_Players[i]);
		}
		free(_game);
	}
	_game->m_magicNumber = 0;
}





