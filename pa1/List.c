/*********************************************************************************
* Calvin Hong, cbhong
* 2019 Summer CMPS101 PA1
* List.c
* List ADT
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

typedef struct NodeObj{
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
	Node N = malloc(sizeof(NodeObj));
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
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return(L);
}

void freeList(List* pL){
	if(pL != NULL && *pL != NULL){
		while(length(*pL) > 0){
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

int length(List L){
	if( L == NULL){
		printf("List Error: calling length() on NULL List reference\n");
		exit(1);
	}
	return L->length;
}


int index(List L){
	if(L == NULL){
		printf("List Error: calling index() on NULL List reference\n");
		exit(1);
	}
	return L->index;
}
int front(List L){
	if(L == NULL){
		printf("List Error: calling front() on NULL List reference\n");
		exit(1);
	}
	if(L->length < 1){
		printf("List Error: calling front() on empty List reference\n");
		exit(1);
	}
	return L->front->data;
}
int back(List L){
	if(L == NULL){
		printf("List Error: calling back() on NULL List reference\n");
		exit(1);
	}
	if(L->length < 1){
		printf("List Error: calling back() on empty List reference\n");
		exit(1);
	}
	return L->back->data;
}
int get(List L){
	if(L == NULL){
		printf("List Error: calling get() on NULL List reference\n");
		exit(1);
	}
	if(L->index < 0){
		printf("List Error: calling get() with an undefined index on List\n");
		exit(1);
	}
	if(L->length < 1){
		printf("List Error: calling get() on empty List reference\n");
		exit(1);
	}
	return L->cursor->data;
}
int equals(List A, List B){
	if(A == NULL || B == NULL){
		printf("List Error: calling equals() on NULL List reference\n");
		exit(1);
	}
	if(A->length != B->length){
		return 0;
	}

	Node tempA = A->front;
	Node tempB = B->front;

	while(tempB != NULL && tempA != NULL){
		if(tempB->data != tempA->data){
			return 0;
		}
		tempA = tempA->next;
		tempB = tempB->next;
	}
	return 1;
}

void clear(List L){
	if( L == NULL){
		printf("List Error: calling clear() on NULL List reference\n");
		exit(1);
	}
	Node temp = L->front;
	while(temp != NULL){
		Node clear = temp;
		temp = temp->next;
		free(clear);
	}

	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->index = -1;
}
void moveFront(List L){
	if(L == NULL){
		printf("List Error: calling moveFront() on NULL List reference\n");
	 	exit(1);
	}
	if(L->length == 0){
		printf("List Error: calling moveFront() on empty List reference\n");
		exit(1);
	}
	if(L->length > 0){
		L->cursor = L->front;
		L->index = 0;
	}
}


void moveBack(List L){
	if(L == NULL){
		printf("List Error: calling moveBack() on NULL List reference\n");
	 	exit(1);
	}
	if(L->length == 0){
		printf("List Error: calling moveBack() on empty List reference\n");
		exit(1);
	}
	if(L->length > 0){
		L->cursor = L->back;
		L->index = L->length - 1;
	}
}


void movePrev(List L){
	if(L == NULL){
		printf("List Error: calling movePrev() on NULL List reference\n");
		exit(1);
	}
	if(L->cursor != NULL && L->index != 0){
		L->cursor = L->cursor->prev;
		--L->index;
	}
	else if(L->cursor != NULL && L->index == 0){
		L->cursor = NULL;
		L->index = -1;
	}	
}
void moveNext(List L){
	if(L == NULL){
		printf("List Error: calling moveNext() on NULL List reference\n");
		exit(1);
	}
	if(L->cursor != NULL && L->index != L->length - 1){
		L->cursor = L->cursor->next;	
		L->index++;
	}
	else if(L->cursor != NULL && L->index == L->length - 1){
		L->cursor = NULL;
		L->index = -1;
	}	
}

void prepend(List L, int data){
	if(L == NULL){
		printf("List Error: calling prepend() on NULL List reference\n");
		exit(1);
	}
	Node temp = newNode(data);
	if(L->front == NULL){
		L->front = L->back = temp; 	
	}else{
		L->front->prev = temp;
		temp->next = L->front;
		L->front = temp;
		L->index++;
	}
	L->length++;	
}
void append(List L, int data){
	if(L == NULL){
		printf("List Error: calling append() on NULL List reference\n");
		exit(1);
	}
	Node temp = newNode(data);
	if(L->front == NULL){
		L->front = L->back = temp;
	}
	else {
		L->back->next = temp;
		temp->prev = L->back;
		L->back = temp;
	}
	L->length++;
}

void insertBefore(List L, int data){
	if(L == NULL){
		printf("List Error: calling insertBefore() on NULL List reference\n");
		exit(1);
	}else{
		Node temp = newNode(data);

		temp->next = L->cursor;
		if(L->cursor->prev != NULL){
			temp->prev = L->cursor->prev;
			L->cursor->prev->next = temp;
		}
		L->cursor->prev = temp;
		if(temp->prev == NULL){
			L->front = temp;
		}
		L->index++;
		L->length++;
	}
}

void insertAfter(List L, int data){
	if(L == NULL){
		printf("List Error: calling insertAfter() on NULL List reference\n");
		exit(1);
	}
	else if (L->length <= 0){
		printf("List Error: insertAfter() called on empty List\n");
		exit (1);		
	}
	else if(L->cursor == L->back){
		append(L,data);
	}
	else{
		Node temp = newNode(data);
		temp->prev = L->cursor;
		temp->next = L->cursor->next;
		L->cursor->next->prev= temp;
		L->cursor->next = temp;
		L->length++;
	}
}


void deleteFront(List L){
	Node N = NULL;
	if(L == NULL){
		printf("List Error: calling deleteFront() on NULL List reference\n");
		exit(1);
	}
	N = L->front;
	if(L->cursor == N){
   		L->index = -1;
   		L->cursor = NULL;
	}
	if(length(L) > 1){
		L->front = L->front->next;
	}
	if(L->index != -1){
		L->index--;
	}
	L->length--;
	freeNode(&N);
}
void deleteBack(List L){
	Node N = NULL;
	if(L == NULL){
		printf("List Error: calling deleteBack() on NULL List reference\n");
		exit(1);
	}
	N = L->back;
	if(L->cursor == N){
		L->back = L->back->prev;
		L->index = -1;
		L->cursor = NULL;
	}
	else if(L->front == N){
		L->front = L->back = NULL;
	}else{
		L->back = L->back->prev;
	}
	L->length--;
	freeNode(&N);
}
void delete(List L){
	Node N = NULL;
	N = L->cursor;
	if(L == NULL){
		printf("List Error: calling delete() on NULL List reference\n");
		exit(1);
	}
	if(L->index < 0){
		printf("List Error: calling delete() on a null cursor\n");
		exit(1);
	}
	else if(N == L->front){
		deleteFront(L);
	}
	else if(N == L->back){
		deleteBack(L);
	}
	else if(index(L) >= 0){
		if(L->cursor->prev == NULL){
			L->front = L->cursor->next;
		}else if(L->cursor->next == NULL){
			L->back = L->cursor->prev;
		}else{
			L->cursor->prev->next = L->cursor->next;
			L->cursor->next->prev = L->cursor->prev;
		}
	L->cursor = NULL;
	L->index = -1;
	L->length--;

	freeNode(&N);
	}

}

void printList(FILE* out, List L){
	Node temp = L->front;
	while(temp != NULL){
		fprintf(out, "%d ", temp->data);
		temp = temp->next;
	}
}

List copyList(List L){
	List c = newList();
	Node temp = L->front;
	while(temp != NULL){
		append(c, temp->data);
		temp = temp->next;
	}
	return c;
}
	
