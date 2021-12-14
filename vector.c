#include <stdio.h> 
#include <stdlib.h>/* for malloc*/
#include "ADTDefs.h"
#include "vector.h"
#define MAGIC 654687
#define BLOCK_CHUNK 2

struct Vector
{
	int* m_items;
	size_t m_originalSize; 
	size_t m_size;
	size_t m_nItems; /* elements*/
	size_t m_blockSize;
	size_t m_magicNumber;
};

ADTErr IncreaseBlockSize(struct Vector *_vector);
ADTErr DecBlockSize(struct Vector *_vecto);

struct Vector * VectorCreate(size_t _initialSize, size_t _extensionBblockSize)
{
	struct  Vector *pVector;
	if(_initialSize == 0 && _extensionBblockSize == 0)
	{
		return NULL;
	}
	if((pVector = (struct Vector *)malloc (sizeof(struct Vector))) == NULL)
	{
		return NULL;
	}

	if((pVector->m_items =(int*) malloc (_initialSize * sizeof(int))) == NULL)
	{
		free(pVector);
		return NULL;
	}
	pVector->m_blockSize = _extensionBblockSize;
	pVector->m_nItems = 0;
	pVector->m_size = _initialSize;
	pVector->m_magicNumber = MAGIC;
	pVector->m_originalSize = _initialSize;
	return pVector;
}

ADTErr VectorAdd(struct Vector *_vector, int _item)
{
	int res;
	if(_vector == NULL)
	{
		return ERR_NULL_ERROR;
	}
	if(_vector->m_size == _vector->m_nItems)
	{
		if(_vector->m_blockSize == 0)
		{
			return ERR_OVERFLOW;
		}
		res = IncreaseBlockSize(_vector);
		if (res != ERR_OK)
		{
			return ERR_REALLOCATION_FAILED;
		}
	}
	_vector->m_items[_vector->m_nItems] = _item;
	_vector->m_nItems = _vector->m_nItems + 1;
	return ERR_OK;
}

ADTErr IncreaseBlockSize(struct Vector *_vector)
{
	int *temp = NULL;
	temp = (int*) realloc(_vector->m_items, (_vector->m_size + _vector->m_blockSize)* sizeof(int));
	if(temp == NULL)
	{
		return ERR_REALLOCATION_FAILED;
	}
	_vector->m_items = temp;
	_vector->m_size = _vector->m_size + _vector->m_blockSize;
	return ERR_OK;
}

void VectorPrint(struct Vector *_vector)
{
	int i;
	if(_vector == NULL)
	{
		return;
	}
	for(i=0 ; i<_vector->m_nItems ; i++)
	{
		printf("%d " , _vector->m_items[i]);
	}
	printf("\n");
}

void VectorDestroy (struct Vector *_vector)
{
	if(_vector != NULL && _vector->m_magicNumber == MAGIC)
	{
		if(_vector->m_items != NULL)
		{
			free(_vector->m_items);
		}
		_vector->m_magicNumber = 0;
		free(_vector);
	}
}

ADTErr VectorDelete(struct Vector *_vector, int* _item) 
{
	if(_vector == NULL || _item == NULL)
	{
		return ERR_NULL_ERROR;
	}
	if(_vector->m_nItems <= 0)
	{
		return ERR_UNDERFLOW;
	}
	*_item = _vector->m_items[_vector->m_nItems - 1];
	_vector->m_nItems = _vector->m_nItems - 1;
	if(_vector->m_size > _vector->m_originalSize && _vector->m_size >= _vector->m_nItems + (BLOCK_CHUNK * _vector->m_blockSize))
	{
		DecBlockSize(_vector);
	}
	return ERR_OK;
}

ADTErr DecBlockSize(struct Vector *_vector)
{
	int *temp = NULL;
	temp = (int*) realloc(_vector->m_items, (_vector->m_size - _vector->m_blockSize)* sizeof(int));
	if(temp == NULL)
	{
		return ERR_REALLOCATION_FAILED;
	}
	else
	{
	_vector->m_items = temp;
	_vector->m_size = _vector->m_size - _vector->m_blockSize;
	return ERR_OK;
	}
}


ADTErr VectorGet(struct Vector *_vector, size_t _index, int *_item)
{
	if(_vector == NULL)
	{
		return ERR_NULL_ERROR;
	}
	if( _index >= _vector->m_nItems)
	{
		return ERR_WRONG_INDEX;
	}
	*_item = _vector->m_items[_index];
	return ERR_OK;
}

ADTErr VectorSet(struct Vector *_vector, size_t _index, int _item)
{
	if(_vector == NULL)
	{
		return ERR_NULL_ERROR;
	}
	if( _index >= _vector->m_nItems)
	{
		return ERR_WRONG_INDEX;
	}
	_vector->m_items[_index] = _item;
	return ERR_OK;
}
ADTErr VectorItemsNum(struct Vector *_vector, size_t* _numOfItems)
{
	if(_vector == NULL || _numOfItems == NULL)
	{
		return ERR_NULL_ERROR;
	}
	* _numOfItems = _vector->m_nItems;
	return ERR_OK;
}

ADTErr VectorSizesNum(struct Vector *_vector, size_t* _numOfItems)
{
	if(_vector == NULL || _numOfItems == NULL)
	{
		return ERR_NULL_ERROR;
	}
	* _numOfItems = _vector->m_size;
	return ERR_OK;
}

int * GetArrPtr(struct Vector *_vector)
{
	return _vector->m_items;
}











