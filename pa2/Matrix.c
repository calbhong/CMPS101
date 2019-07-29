/*********************************************************************************
* Calvin Hong, cbhong
* 2019 Summer CMPS101 PA2
* Matrix.c
* C source file for Matrix ADT
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "Matrix.h"

typedef struct EntryObj{
	int listNum;
	double value;
} EntryObj;

typedef EntryObj* Entry;

typedef struct MatrixObj{

}Matrix;

Matrix newMatrix(int n){

}

void freeMatrix(Matrix* pM){

}

int size(Matrix M){

}

int equals(Matrix A, Matrix B){}

void makeZero(Matrix M){}

void changeEntry(Matrix M, int i, int j, double x){}

Matrix copy(Matrix A){}

Matrix transpose(Matrix A){}

Matrix scalarMult(double x, Matrix A){}

Matrix sum(Matrix A, Matrix B){}

Matrix diff(Matrix A, Matrix B){}

Matrix product(Matrix A, Matrix B){}

void printMatrix(FILE* out, Matrix M){}