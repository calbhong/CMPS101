/*********************************************************************************
* Calvin Hong, cbhong
* 2019 Summer CMPS101 PA2
* Matrix.c
* C source file for Matrix ADT
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "Matrix.h"
#include "List.h"

typedef struct EntryObj{
	int colNum;
	double value;
} EntryObj;

typedef EntryObj* Entry;

typedef struct MatrixObj{
	int numRows;
	int nnz;
	List *row;
} MatrixObj;

Entry newEntry(int col, double data){
	Entry N = malloc(sizeof(EntryObj));
	N->colNum = col;
	N->value = data;
	return(N);
}

void freeEntry(Entry* pE){
	if(pE != NULL && *pE != NULL){
		free(*pE);
		*pE = NULL;
	}
}

Matrix newMatrix(int n){
	if(n < 1){
		printf("Matrix Error: Matrix() called with negative number of columns\n");
		exit(1);		
	}
	Matrix M = malloc(sizeof(MatrixObj));
	M->numRows = n;
	M->nnz = 0;
	//M->row = malloc(n*sizeof(ListObj));
	for(int i = 0; i < n; i++){
		M->row[i] = newList();
	}
	return M;
}

void freeMatrix(Matrix* pM){
	if(pM != NULL && *pM != NULL){
		for(int i = 0; i < size(*pM); i++){
			Matrix A = *pM;
			List temp = A->row[i];
			freeList(&temp);
		}
	}
	free(*pM);
	*pM = NULL;
}

int size(Matrix M){
	return M->numRows;
}

int NNZ(Matrix M){
	return M->nnz;
}

int equals(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("Matrix Error: calling equals() on NULL Matrix reference\n");
		exit(1);
	}
	if(A->numRows != B->numRows){
		return 0;
	}
	return 0;
}

void makeZero(Matrix M){
	for(int i = 0; i < size(M); i++){
		freeList(&M->row[i]);
		M->row[i] = newList();
	}
	M->nnz = 0;
}

void changeEntry(Matrix M, int i, int j, double x){

	if(i < 1 || i > size(M)){
		printf("Matrix Error: called Matrix on wrong ith position\n");
		exit(1);
	}
	if(j < 1 || j > size(M)){
		printf("Matrix Error: called Matrix on wrong jth position\n");
		exit(1);
	}
	
	int found = 0;
	moveFront(M->row[i]);
	while(index(M->row[i]) >=0){
		Entry temp = get(M->row[i]);
		if(temp->colNum == j){
			found = 1;
		}else{
			found = 0;
		}

		if(found != 0){
			if(x == 0.0){
				delete(M->row[i]);
				M->nnz--;
			}else{
				temp->value = x;
			}
		}
		moveNext(M->row[i]);
	}
	if(found == 1 && x != 0.0){
		Entry N = newEntry(j,x);
		moveFront(M->row[i]);
		if(index(M->row[i]) == -1){
			append(M->row[i], N);
			M->nnz++;
		}else{
			Entry temp = get(M->row[i]);
			while(index(M->row[i]) > -1 && (temp->colNum) < j){
				moveNext(M->row[i]);
			}
			if(index(M->row[i]) > -1){
				insertBefore(M->row[i], N);
				M->nnz++;
			}else{
				append(M->row[i], N);
				M->nnz++;
			}
		}
	} 
	
}

Matrix copy(Matrix A){
	Matrix C = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++){
		moveFront(C->row[i]);
		while(index(C->row[i])>=0){
			Entry temp = get(A->row[i]);
			changeEntry(C, i, temp->colNum, temp->value);
			moveNext(C->row[i]);
		}
	}
	return C;
}

Matrix transpose(Matrix A){
	Matrix C = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++){
		moveFront(A->row[i]);
		while(index(A->row[i]) >= 0){
			Entry temp = get(A->row[i]);
            changeEntry(C, temp->colNum, i, temp->value);
            moveNext(A->row[i]);
		}
	}
	return C;
}

Matrix scalarMult(double x, Matrix A){
	Matrix C = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++){
		moveFront(A->row[i]);
		while(index(A->row[i]) >= 0){
			Entry temp = get(A->row[i]);
            changeEntry(C, temp->colNum, i, (x * temp->value) );
            moveNext(A->row[i]);
		}
	}	
	return C;
}

Matrix sum(Matrix A, Matrix B){
	Matrix C = newMatrix(size(A));
	return C;
}

Matrix diff(Matrix A, Matrix B){
	Matrix C = newMatrix(size(A));
	return C;
}

Matrix product(Matrix A, Matrix B){
	Matrix C = newMatrix(size(A));
	return C;
}

void printMatrix(FILE* out, Matrix M){
	printf("dummy line\n");
}