#ifndef __UI_H__
#define __UI_H__
#include <stdio.h>
#include "card.h"
#include "vector.h"
/* bold/not bold */
#define BOLD_ON "\x1b[1m"
#define BOLD_OFF "\x1b[21m"

/* colors */
#define NORMAL "\x1B[0m"
#define BLACK "\x1b[30m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"
#define GRAY "\x1b[90m"

/* cards suites symbols */
#define HEART_PRINT "\xE2\x99\xA5"
#define SPADE_PRINT "\xE2\x99\xA0"
#define DIAMOND_PRINT "\xE2\x99\xA6"
#define CLUB_PRINT "\xE2\x99\xA3"

void printHand(struct Vector * _vec);

void printTable(struct Vector * _vec);

void printGlobalScore(int _arr[] , int _size);

void PrintplayerStart(int _player);

void PrintplayerLost(int _player);

void printPlayerChoice(char * _str , int * _choice );

void printInvalidSet(int _set);

void printMesseage(char * _str);

#endif /* #ifndef __UI_H__ */
