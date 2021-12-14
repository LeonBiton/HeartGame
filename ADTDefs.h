#ifndef __ADTDefs_H__
#define __ADTDefs_H__
typedef enum
{
/* General ADT Errors */
ERR_OK =0,

ERR_GENERAL,

ERR_NULL_ERROR,

ERR_NOT_INITIALIZED,

ERR_ALLOCATION_FAILED,

ERR_REALLOCATION_FAILED,

ERR_UNDERFLOW,

ERR_OVERFLOW,

ERR_DUPLICATE_NUMBER,

ERR_WRONG_INDEX,

ERR_INVALID_THROW,

/* Vector Errors */

/* Stack Errors */

ERR_STACK_BBBBB = 30

/* LinkedList Errors */
}ADTErr;

#endif /* #ifndef __ADTDefs_H__ */
