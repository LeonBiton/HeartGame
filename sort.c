#include <stdio.h>
#include "sort.h"
#include "vector.h"
#include "stack.h"
#include "ADTDefs.h"


void swap(size_t  _index1 , size_t  _index2 , int _item , int _item2 ,  struct Vector* _vec);
void QuickRec(struct Vector* _vec, size_t _begin, size_t _end);
size_t partition (struct Vector* _vec ,size_t _indexPivot , size_t _indexEnd );
void Insertion(struct Vector* _vec , size_t _size , size_t _gap);
void Selection(struct Vector* _vec , size_t _size);
void MergeRec (struct Vector* _vec, size_t _begin, size_t _end, int  _temp[]);
void Merge(struct Vector* _vec,size_t _begin,size_t _mid , size_t _end, int _temp[]);
void countAggFreq(struct Vector* _vec, int _CountArr[] , int _maxValue , size_t _size );
void toTempAndCopy(struct Vector* _vec, int _CountArr[] , int _maxValue , size_t _size , int _temp[]);
int getDigit(int _num , int _nDigits);
void countFreqRadix(struct Vector* _vec , int _CountArr[], size_t _size , int _nDigits);
void zeroArray(int _array[] , size_t _size);
void sortAndCopyToTempRadix(struct Vector* _vec ,  int _CountArr[], int _temp[] , size_t _size , int _nDigits);
void setArray(struct Vector* _vec , int* _temp , size_t _dataArraySize);
void aggCountFreq(struct Vector* _vec, int _CountArr[] , int _maxValue , size_t _size );



ADTErr BubbleSort (struct Vector* _vec)
{
	size_t size ;
	int i,j,flag , status , item , item2;
	status = VectorItemsNum(_vec , &size);
	if(status != ERR_OK)
	{
		return status;
	}
	for(i = 0 ; i < size; i++)
	{
		flag = 0;
		for(j = 0; j< size - i - 1; j++)
		{
			VectorGet(_vec ,j ,&item);
			VectorGet(_vec ,j + 1 ,&item2);
			if( item > item2 )
			{
				swap(j , j+1 ,item , item2, _vec);
				flag = 1;
			}
		}
	if(flag == 0)
	{
		break;
	}
	}
}



ADTErr ShakeSort(struct Vector* _vec)
{
	size_t size;
	int flag = 1;
	int begin = 0,i , item , item2 , status;
	status = VectorItemsNum(_vec , &size);
	if(status != ERR_OK)
	{
		return status;
	}
	while(flag)
	{
		flag = 0 ;
		for(i = begin ; i < size - 1 ; i++ )
		{
			VectorGet(_vec ,i ,&item);
			VectorGet(_vec ,i + 1 ,&item2);
			if( item > item2 )
			{
				swap(i , i+1 ,item , item2, _vec);
				flag = 1;
			}
		}
		size--;
		if(flag == 0)
		{
			break;
		}
		flag = 0;
		for(i = size - 2 ; i>= begin ; i--)
		{
			VectorGet(_vec ,i ,&item);
			VectorGet(_vec ,i + 1 ,&item2);
			if(item > item2)
			{
				swap(i , i+1 ,item , item2, _vec);
				flag = 1;
			}
		}
		begin++;
	}
}



void swap(size_t  _index1 , size_t  _index2 , int _item , int _item2 ,  struct Vector* _vec)
{
	VectorSet(_vec ,_index1, _item2 );
	VectorSet(_vec ,_index2, _item );
}

/*void swap(size_t  _index1 , size_t  _index2 , struct Vector* _vec)
{
	int item , item2;
	VectorGet(_vec ,_index1 ,&item);
	VectorGet(_vec ,_index2 ,&item2);
	VectorSet(_vec ,_index1, item2 );
	VectorSet(_vec ,_index2, item );
}*/


/*ADTErr IterQuickSort (struct Vector* _vec)
{
	int status;
	size_t size , begin = 0;
	struct Stack * _stack = NULL;
	if (_vec == NULL)
	{
		return ERR_NULL_ERROR;
	}
	VectorItemsNum(_vec , &size);
	_stack = StackCreate(size , 0);
	status = StackPush(_stack , (int) begin);
	status = StackPush(_stack , (int) size);
	if(status != ERR_OK)
	{
		return status;
	}
	while(StackIsEmpty(_stack) == 0)
	{
		size_t pivotIndex;
		StackPop(_stack , (int *) &size );
		StackPop(_stack , (int *) &begin );
		pivotIndex = partition(_vec ,begin , size );
		if(pivotIndex - 1 > begin)
		{
			StackPush(_stack ,begin);
			StackPush(_stack ,pivotIndex - 1);
		}
		if(pivotIndex + 1 < size)
		{
			StackPush(_stack ,pivotIndex + 1);
			StackPush(_stack ,size);
		}
	}	
}*/


ADTErr QuickSort (struct Vector* _vec)
{
	size_t size;
	if (_vec == NULL)
	{
		return ERR_NULL_ERROR;
	}
	VectorItemsNum(_vec , &size);
	QuickRec(_vec , 0 , size - 1);
}


void QuickRec(struct Vector* _vec, size_t _begin, size_t _end) 
{
	if (_begin < _end)
    {
		size_t pivotIndex = partition(_vec ,_begin , _end );
		if(pivotIndex !=0)
		{
			QuickRec(_vec ,_begin , pivotIndex - 1 );
		}
		QuickRec(_vec ,pivotIndex + 1 , _end );
	}
}



size_t partition (struct Vector* _vec ,size_t _indexPivot , size_t _indexEnd )
{
	int pivot,left, right , last = _indexEnd;
	size_t indexBegin = _indexPivot;
	VectorGet(_vec ,_indexPivot ,&pivot);
	VectorGet(_vec ,indexBegin ,&left);
	VectorGet(_vec ,_indexEnd ,&right);
	while(indexBegin < _indexEnd)
	{
		while(left <= pivot)
		{
			if(last == indexBegin)
			{
				break;
			}
			VectorGet(_vec ,++indexBegin ,&left);
		}
		while(right > pivot)
		{
			VectorGet(_vec ,--_indexEnd ,&right);
		}
		if(indexBegin < _indexEnd)
		{
			swap(indexBegin , _indexEnd , left, right ,_vec);
			VectorGet(_vec ,indexBegin ,&left);
			VectorGet(_vec ,_indexEnd ,&right);
		}
	}
	swap(_indexEnd , _indexPivot ,right , pivot, _vec);
	return _indexEnd;
}


ADTErr InsertionSort (struct Vector* _vec )
{
	size_t size;
	if (_vec == NULL)
	{
		return ERR_NULL_ERROR;
	}
	VectorItemsNum(_vec , &size);
	Insertion(_vec , size , 1);/*return Ok*/
}


void Insertion(struct Vector* _vec , size_t _size , size_t _gap)
{
	size_t i , j;
	int num , numBack;
	for(i = _gap ; i< _size ; i++)
	{
		for(j = i ; j >= _gap ; j = j - _gap)
		{
			VectorGet(_vec ,j ,&num);
			VectorGet(_vec ,j - _gap ,&numBack);
			if(num >= numBack)
			{
				break;
			}
			swap(j , j - _gap ,num , numBack, _vec);
		}
	}
}


ADTErr ShellInsertionSort(struct Vector* _vec)
{
	size_t size , gap;
	if (_vec == NULL)
	{
		return ERR_NULL_ERROR;
	}
	VectorItemsNum(_vec , &size);
	gap = size;
	while(gap > 1)
	{
		gap = gap/2;
		Insertion(_vec , size, gap);
	}
}

ADTErr SelectionSort(struct Vector* _vec)
{
	size_t size;
		if (_vec == NULL)
	{
		return ERR_NULL_ERROR;
	}
	if (size <= 0)
	{
		return ERR_NULL_ERROR;
	}
	VectorItemsNum(_vec , &size);
	Selection(_vec , size);
}

void Selection(struct Vector* _vec , size_t _size)
{
	size_t i , j , indexSmall;
	int num , smallest , orig;
	for(i = 0 ; i< _size - 1 ; i++)
	{
		indexSmall = i;
		VectorGet(_vec ,indexSmall ,&smallest);
		VectorGet(_vec ,i ,&orig);
		for(j = i + 1 ; j< _size ; j++)/* find smallest func*/
		{
			VectorGet(_vec ,j ,&num);
			if(num < smallest)
			{
				smallest = num;
				indexSmall = j;
			}
		}
	swap(i ,indexSmall , orig , smallest , _vec);
	}
}

ADTErr MergeSort (struct Vector* _vec)
{
	size_t size;
	int * temp;
		if (_vec == NULL)
	{
		return ERR_NULL_ERROR;
	}
	VectorItemsNum(_vec , &size);
	if (size < 2)
	{
		return ERR_OK;
	}
	temp = (int *) malloc(size * sizeof(int));
	if(temp == NULL)
	{
		return ERR_ALLOCATION_FAILED;
	}
	MergeRec(_vec , 0 , size - 1 , temp);
	free(temp);
}

void MergeRec (struct Vector* _vec, size_t _begin, size_t _end, int _temp[])
{
	size_t mid;
	if(_begin != _end)
	{
		mid = (_begin + _end) / 2;
		MergeRec(_vec , _begin , mid , _temp);
		MergeRec(_vec , mid + 1 , _end , _temp);
		Merge(_vec , _begin , mid , _end , _temp);
	}
}


void Merge(struct Vector* _vec,size_t _begin,size_t _mid , size_t _end, int  _temp[])
{
	size_t i = _begin, j = _mid + 1 , z = _begin;/*valuable names*/
	int num , num2;
	while(i <= _mid &&j<= _end)
	{
		VectorGet(_vec ,i ,&num);
		VectorGet(_vec ,j ,&num2);
		if(num < num2)
		{
			_temp[z++] = num;
			i++;
		}
		else
		{
			_temp[z++] = num2;
			j++;
		}
	}
	while(i<= _mid)
	{
		VectorGet(_vec ,i ,&num);
		_temp[z++] =num; 
		i++;
	}
	while(j<=_end)
	{
		VectorGet(_vec ,j ,&num2);
		_temp[z++] =num2; 
		j++;
	}
	for(i = _begin ; i <= _end ; i++)
	{
		VectorSet(_vec , i ,_temp[i]);
	}
}


ADTErr CountingSort (struct Vector* _vec, int _maxValue)
{
	int * CountArr = NULL;
	int * temp = NULL;
	int i;
	size_t size;
	if(_vec == NULL)
	{
		return ERR_NULL_ERROR;
	}
	if(_maxValue <= 0)
	{
		return ERR_OK;
	}
	VectorItemsNum(_vec , &size);
	temp = (int *) malloc(size * sizeof(int));
	CountArr = (int *) calloc(_maxValue , sizeof(int));
	if(temp == NULL || CountArr == NULL)
	{
		return ERR_ALLOCATION_FAILED;
	}
	countAggFreq(_vec , CountArr ,_maxValue , size );
	toTempAndCopy(_vec , CountArr ,_maxValue , size , temp);
	free(temp);
	free(CountArr);
	return ERR_OK;
}

void countAggFreq(struct Vector* _vec, int _CountArr[] , int _maxValue , size_t _size )
{
	size_t i;
	int num , numBack;
	for(i = 0 ; i< _size ; i++)
	{
		VectorGet(_vec ,i ,&num);
		_CountArr[num] += 1;
	}
	for(i =1 ; i<_maxValue ; i++)
	{
		_CountArr[i] = _CountArr[i] +  _CountArr[i-1];
	}
}

void toTempAndCopy(struct Vector* _vec, int _CountArr[] , int _maxValue , size_t _size , int _temp[])
{
	int num;
	size_t i;
	for (i = _size ; i > 0 ;i --)
	{
		VectorGet(_vec ,i - 1 ,&num);
		_temp[_CountArr[num] - 1] = num;
		_CountArr[num] -= 1;
	}
	for(i = 0 ; i<_size;i++)
	{
		VectorSet(_vec , i ,_temp[i]);
	}
}


ADTErr RadixSort (struct Vector* _vec, int _nDigits)
{
	size_t size ;
	int i , j;
	int * CountArr = NULL;
	int * temp = NULL;
	VectorItemsNum(_vec , &size);
	if(_vec == NULL)
	{
		return ERR_NULL_ERROR;
	}
	if(_nDigits <= 0)
	{
		return ERR_OK;
	}
	temp = (int *) malloc(size * sizeof(int));
	CountArr = (int *) calloc(10 , sizeof(int));
	if(temp == NULL || CountArr == NULL)
	{
		return ERR_ALLOCATION_FAILED;
	}
	for(i = 1 ; i<= _nDigits ; i++)
	{
		countFreqRadix(_vec , CountArr , size , i);
		aggCountFreq(_vec ,CountArr , 10 , size );
		sortAndCopyToTempRadix(_vec ,CountArr ,temp, size , i );
		zeroArray(CountArr , 10);
		setArray(_vec ,temp , size );
	}
}

void setArray(struct Vector* _vec , int* _temp , size_t _dataArraySize)
{
	int i, item;
	
	for (i = 0; i < _dataArraySize ; i++)
	{
		VectorSet(_vec , i ,_temp[i]);		
	}

}


void aggCountFreq(struct Vector* _vec, int _CountArr[] , int _maxValue , size_t _size )
{
	size_t i;
	for(i =1 ; i<_maxValue ; i++)
	{
		_CountArr[i] = _CountArr[i] +  _CountArr[i-1];
	}
}

void countFreqRadix(struct Vector* _vec , int _CountArr[], size_t _size , int _nDigits)
{
	int i, item;
	
	for (i = 0 ; i < _size ; i++)
	{
		VectorGet(_vec, i, &item);
		_CountArr[getDigit(item , _nDigits)] += 1;
	}
}

void sortAndCopyToTempRadix(struct Vector* _vec ,  int _CountArr[], int _temp[] , size_t _size , int _nDigits)
{
	int i , item;
	
	for (i = _size - 1 ; i >= 0 ; i--)
	{
		VectorGet(_vec, i, &item);
		_temp[_CountArr[getDigit(item, _nDigits)] -1] = item; 
		_CountArr[getDigit(item, _nDigits)]--;
	}
}

int getDigit(int _num , int _nDigits)
{
	int i, digit;
	
	for (i = 0 ; i < _nDigits ; i++)
    {
        digit = _num % 10;
        _num = _num / 10;

    }
    return digit;
}


 void zeroArray(int _array[] , size_t _size)
{
	int i;
	
	for (i = 0 ; i < _size ; i++)
	{
		_array[i] = 0;
	}
}





