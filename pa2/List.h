/*********************************************************************************
* Calvin Hong, cbhong
* 2019 Summer CMPS101 PA2
* List.h
* Header file for List ADT
*********************************************************************************/
#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------
List newList(void);
void freeList(List* pL);

// Access functions -----------------------------------------------------------
int length(List L);
int index(List L);
void *front(List L);
void *back(List L);
void *get(List L);
//int equals(List A, List B);

// change the return values to void ptrs somehow

// Manipulation procedures ----------------------------------------------------
void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, void* data);
void append(List L, void* data);
void insertBefore(List L, void* data);
void insertAfter(List L, void* data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L);
//List copyList(List L);

#endif