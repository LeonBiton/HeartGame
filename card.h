#ifndef __CARD_H__
#define __CARD_H__
#include <stdio.h>
#define SUIT(x) (x / 13) 
#define RANK(x) (x % 13)


typedef enum
{
	HEART,
	SPADE,
	DIAMOND,
	CLUB,
	NUMBER_OF_SUITS
}Suit ;

typedef enum
{
	HEART_2 = 0,
	HEART_3,
	HEART_4,
	HEART_5,
	HEART_6,
	HEART_7,
	HEART_8,
	HEART_9,
	HEART_10,
	HEART_J,
	HEART_Q,
	HEART_K,
	HEART_A, 
	SPADE_2 = 13,
	SPADE_3,
	SPADE_4,
	SPADE_5,
	SPADE_6,
	SPADE_7,
	SPADE_8,
	SPADE_9,
	SPADE_10,
	SPADE_J,
	SPADE_Q,
	SPADE_K,
	SPADE_A,
	DIAMOND_2 = 26,
	DIAMOND_3,
	DIAMOND_4,
	DIAMOND_5,
	DIAMOND_6,
	DIAMOND_7,
	DIAMOND_8,
	DIAMOND_9,
	DIAMOND_10,
	DIAMOND_J,
	DIAMOND_Q,
	DIAMOND_K,
	DIAMOND_A,
	CLUB_2 = 39,
	CLUB_3,
	CLUB_4,
	CLUB_5,
	CLUB_6,
	CLUB_7,
	CLUB_8,
	CLUB_9,
	CLUB_10,
	CLUB_J,
	CLUB_Q,
	CLUB_K,
	CLUB_A = 51,
	NUMBER_OF_CARDS
	
}Card;









#endif /* #ifndef __CARD_H__ */
