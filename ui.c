#include <stdio.h>
#include "ui.h"
#include "vector.h"

char getRank(int _card);


void printInvalidSet(int _set)
{
	printf("leading series is ");
	switch(_set)
		{
			case HEART:
				printf(RED);
				printf(HEART_PRINT);
				printf(NORMAL);
				printf("  ");
				break;

			case SPADE:
				printf(BLACK);
				printf(SPADE_PRINT);
				printf(NORMAL);
				printf("  ");
				break;

			case DIAMOND:
				printf(RED);
				printf(BOLD_ON);
				printf(DIAMOND_PRINT);
				printf(NORMAL);
				printf("  ");
				break;
			
			case CLUB:
				printf(BLACK);
				printf(BOLD_ON);
				printf(CLUB_PRINT);
				printf(NORMAL);
				printf("  ");
				break;
		}
	printf("throw card from the leading series\n");
}

void printPlayerChoice(char * _str , int * _choice )
{
	printf("%s\n" , _str);
	scanf("%d" , _choice);
}

void printMesseage(char * _str)
{
	printf("%s\n" , _str);
}

void PrintplayerStart(int _player)
{
	printf("\n");
	printf("Player %d start \n" , _player);
}

void PrintplayerLost(int _player)
{
	printf("\n");
	printf("Player %d lost \n" , _player);
}

void roundScore(int _arr[] , int _size)
{
	int i = 0;
	printf(GREEN);
	printf(BOLD_ON);
	printf("\n               Round Score \n");
	printf(" ___________________________________________");
	printf("\n|Player %d  | Player %d | Player %d | Player %d |\n" , i+ 1, i+ 2, i + 3, i + 4);
	printf("|__________|__________|__________|__________|\n");
	for(; i<_size ; i++)
	{
		printf("|   %2d     " , _arr[i]);
	}
	printf(GREEN);
	printf(BOLD_ON);
	printf("|");
	printf("\n|__________|__________|__________|__________|\n");
	printf(NORMAL);
	printf("\n");
}

void printGlobalScore(int _arr[] , int _size)
{
	int i;
	printf("\n    Global Score \n");
	printf(" _________________");
	for(i = 0; i<_size ; i++)
	{
		printf(WHITE);
		printf(BOLD_ON);
		printf("\n|Player %d  | %3d  |\n" ,i + 1 , _arr[i]);
		printf("|__________|______|");
	}
	printf(NORMAL);
	printf("\n");
}

void printWinner(int _winner)
{
	printf(YELLOW);
	printf(BOLD_ON);
	printf("The winner is player %d !\n" , _winner + 1);
	printf(NORMAL);
}

void printTable(struct Vector * _vec)
{
	printf("--------Table-------\n");
	printHand(_vec);
	printf("--------------------");
	printf("\n");
}

void printHand(struct Vector * _vec)
{
	int i , card;
	char item2;
	size_t size;
	VectorItemsNum(_vec, &size);
	if(_vec == NULL || size == 0)
	{
		return;
	}
	for(i = 0 ; i<size ; i++)
	{
		VectorGet(_vec, i, &card);
		if(RANK(card) <= 8)
		{
			printf("%2d" , RANK(card) + 2 );
		}
		else
		{
			item2 = getRank(RANK(card));
			printf("%2c" , item2);
		}
		switch(SUIT(card))
		{
			case HEART:
				printf(RED);
				printf(HEART_PRINT);
				printf(NORMAL);
				printf("  ");
				break;

			case SPADE:
				printf(BLACK);
				printf(SPADE_PRINT);
				printf(NORMAL);
				printf("  ");
				break;

			case DIAMOND:
				printf(RED);
				printf(BOLD_ON);
				printf(DIAMOND_PRINT);
				printf(NORMAL);
				printf("  ");
				break;
			
			case CLUB:
				printf(BLACK);
				printf(BOLD_ON);
				printf(CLUB_PRINT);
				printf(NORMAL);
				printf("  ");
				break;
		}
	}
	printf("\n");
}

char getRank(int _card)
{
	if(_card == 9)
	{
		return 'J';
	}
	if(_card == 10)
	{
		return 'Q';
	}
	if(_card == 11)
	{
		return 'K';
	}
	if(_card == 12)
	{
		return 'A';
	}
}


