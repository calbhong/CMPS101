/*********************************************************************************
* Calvin Hong, cbhong
* 2019 Summer CMPS101 PA1
* List.c
* List ADT
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "Lish.h"

typdef struct NodeObj{
	int data;
	struct NodeObj* prev;
	struct NodeObj* next;
} NodeObj;

typedef NodeObj* Node;


typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

Node newNode(int data){
	Node N = malloc(sizeof(Nodeobj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}

void freeNode(Node* pN){
	if(pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}

List newList(void){
	List L
	L = malloc(sizeof(ListObj));
	L->front = L->back = NULL;
	L->length = 0
	L->index = -1
	return(L);
}
void freeList(List* pL);
int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);
int equals(List A, List B);

void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int data);
void append(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

void printList(FILE* out, List L);
List copyList(List L);
