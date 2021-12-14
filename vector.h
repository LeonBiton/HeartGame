#ifndef __VECTOR_H__
#define __VECTOR_H__
#include <stdlib.h> /* Size_t*/
#include "ADTDefs.h"

typedef struct Vector Vector;


/*
	Description: create pointer to struct, in struct create pointer to array, initialize size,blocksize and elements, return the pointer to the struct, size or inc_block_size can be 0 but size and inc_block_size cant be 0. 
	Input: size of array and inc_block size.
	Output: return pointer to struct.
	Errors: return NULL pointer if fail.
*/
struct Vector * VectorCreate(size_t _initialSize, size_t _extensionBblockSize);


/*
	Description: insert number to end of array, if array full the func do realloc, if we need to realloc and inc_block_size is 0 we will get overflow.
	Input: pointer to struct, number to add.
	Output: ERR_OK, ERR_OVERFLOW , ERR_NULL_ERROR.
	Errors: ERR_OVERFLOW , ERR_NULL_ERROR.
*/
ADTErr VectorAdd(struct Vector *_vector, int _item);


/*
	Description: delete dynamic array and struct in memory, have protection against double free.
	Input: pointer to struct.
	Output: None.
	Errors: None.
*/
void VectorDestroy (struct Vector *_vector);

/*
	Description: remove the last element of the array and store it in _item.
	Input:  pointer to struct, ponter to where we will keep the number we delete.
	Output: ERR_OK, ERR_NULL_ERROR, ERR_UNDERFLOW.
	Errors: ERR_NULL_ERROR, ERR_UNDERFLOW.
*/
ADTErr VectorDelete(struct Vector *_vector, int* _item);


/*
	Description: store the value of number in array with given index in _item.
	Input:  pointer to struct, index, ponter to where we will keep the number.
	Output: ERR_OK, ERR_WRONG_INDEX,ERR_NULL_ERROR.
	Errors: ERR_WRONG_INDEX.
*/
ADTErr VectorGet(Vector *_vector, size_t _index, int *_item);


/*
	Description: replace the value of number in array with given index to  _item.
	Input:  pointer to struct, index, number to replace.
	Output: ERR_OK, ERRORS.
	Errors: ERR_WRONG_INDEX,ERR_NULL_ERROR.
*/
ADTErr VectorSet(Vector *_vector, size_t _index, int _item);


/*
	Description: store the number of elements in array in _numOfItems.
	Input:  pointer to struct, _numOfItems to store.
	Output: ERR_OK,ERR_NULL_ERROR.
	Errors: ERR_NULL_ERROR.
*/
ADTErr VectorItemsNum(Vector *_vector, size_t* _numOfItems);
void VectorPrint(struct Vector *_vector);
ADTErr VectorSizesNum(struct Vector *_vector, size_t* _numOfItems);
int * GetArrPtr(struct Vector *_vector);


#endif /* #ifndef __VECTOR_H__ */
