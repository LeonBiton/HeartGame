#ifndef __STACK_H__
#define __STACK_H__
#include "ADTDefs.h"

typedef struct Stack Stack;


/*
	Description: create pointer to struct, in struct create  pointer to pointer to array, initialize size,blocksize and elements, return the pointer to the struct, size or inc_block_size can be 0 but size and inc_block_size cant be 0. 
	Input: size of array and inc_block size.
	Output: return pointer to struct.
	Errors: return NULL pointer if fail.
*/
struct Stack * StackCreate (size_t _size, size_t _blockSize);


/*
	Description: delete dynamic array and struct in memory, have protection against double free.
	Input: pointer to struct.
	Output: None.
	Errors: None.
*/
void StackDestroy(Stack* _stack);


/*
	Description: insert number to end of array, if array full the func do realloc, if we need to realloc and inc_block_size is 0 we will get overflow.
	Input: pointer to struct, number to add.
	Output: ERR_OK, ERR_OVERFLOW , ERR_NULL_ERROR.
	Errors: ERR_OVERFLOW , ERR_NULL_ERROR.
*/
ADTErr StackPush (Stack* _stack, int _item);

/*
	Description: Print the dynamic array.
	Input: pointer to struct.
	Output: None.
	Errors: None.
*/
void StackPrint (Stack *_stack);


/*
	Description: remove the last element of the array and store it in _item.
	Input:  pointer to struct, pointer to where we will keep the number we deleted.
	Output: ERR_OK.
	Errors: ERR_NULL_ERROR, ERR_UNDERFLOW.
*/
ADTErr StackPop (Stack* _stack, int* _item);


/*
	Description: store the value of the last number of array in _item..
	Input:  pointer to struct,pointer to where we will keep the number.
	Output: ERR_OK.
	Errors: ERR_WRONG_INDEX,ERR_NULL_ERROR.
*/
ADTErr StackTop (Stack* _stack, int* _item);

/*
	Description: Return 1 if the stuck is empty and 0 if not.
	Input: pointer to struct.
	Output: None.
	Errors: None.
*/
int StackIsEmpty(Stack* _stack);
ADTErr StackSize(struct Stack *_stack, size_t *_size);



#endif /* #ifndef __STACK_H__ */
