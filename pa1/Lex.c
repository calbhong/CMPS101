/*********************************************************************************
* Calvin Hong, cbhong
* 2019 Summer CMPS101 PA1
* Lex.c
* Lexographic sort
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include <string.h>

#define MAX_LEN 200

int main(int argc, char* argv[]){
	int count = 0;
	FILE *in, *out;
	char line[MAX_LEN];

	//check args
	if(argc != 3){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
	if(in==NULL){
		printf( "Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if(out==NULL){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}

	while( fgets(line, MAX_LEN, in) != NULL)  {
		count++;
	}

	rewind(in);
	char lines[count - 1][MAX_LEN];

	while(fgets(line, MAX_LEN, in) != NULL) {
		strcpy(lines[N], line);
	}

	List list = newList();

	append(list, 0);
	
	

}