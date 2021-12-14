#ifndef __SORT_H__
#define __SORT_H__
#include "vector.h"
#include "stack.h"
#include "ADTDefs.h"
/*
description : bubble sort array
input : pointer to struct vector
otput : none
Errors : ERR_NULL_ERROR
Performance : O(n**2) for average and wors case , best case O(n)
*/
ADTErr BubbleSort (struct Vector* _vec);

/*
description : shake sort array
input : pointer to struct vector
otput : none
Errors : ERR_NULL_ERROR
Performance : O(n**2) for average and wors case , best case O(n)
*/
ADTErr ShakeSort(struct Vector* _vec);


/*
description : quick sort array
input : pointer to struct vector
otput : none
Errors : ERR_NULL_ERROR
Performance : O(n log n) for average and BEST case , WORST case O(n**2)
*/
ADTErr QuickSort (struct Vector* _vec);

/*
description : iterative quick sort array by
input : pointer to struct vector
otput : none
Errors : ERR_NULL_ERROR
Performance : O(n log n) for average and BEST case , WORST case O(n**2)
*/
/*ADTErr IterQuickSort (struct Vector* _vec);*/

/*
description : The array is virtually split into a sorted and an unsorted part, Values from the unsorted part are picked and placed at the correct position in the sorted part.
input : pointer to struct vector
otput : none
Errors : ERR_NULL_ERROR
Performance : O(n ** 2) for average O(n)BEST case , WORST case O(n**2)
*/
ADTErr InsertionSort (struct Vector* _vec );


/*
description : variation of Insertion Sort with gap jumps.
input : pointer to struct vector
otput : none
Errors : ERR_NULL_ERROR
*/
ADTErr ShellInsertionSort(struct Vector* _vec);


/*
description : sort array by finding the minimum from the unsorted part..
input : pointer to struct vector
otput : none
Errors : ERR_NULL_ERROR
*/
ADTErr SelectionSort(struct Vector* _vec);

ADTErr MergeSort (struct Vector* _vec);

ADTErr CountingSort (struct Vector* _vec, int _maxValue);

ADTErr RadixSort (struct Vector* _vec, int _nDigits);


#endif /* #ifndef __SORT_H__ */
