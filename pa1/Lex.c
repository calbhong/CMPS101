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
	FILE *input, *output;
	char line[MAX_LEN];

	//check args
	if(argc != 3){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");
	if(input==NULL){
		printf( "Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if(output==NULL){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}

	while( fgets(line, MAX_LEN, input) != NULL)  {
		count++;
	}

	char lines[count - 1][MAX_LEN];
	int i = 0;
	rewind(input);
	
	while(fgets(line, MAX_LEN, input) != NULL) {
		strcpy(lines[i], line);
		i++;
	}

	List list = newList();

	append(list, 0);

	for(int j = 1; j < count; ++j){
		char *tmp = lines[j];
		int i =  j - 1;
		moveBack(list);
		while(i >= 0 && strcmp(tmp, lines[get(list)]) <= 0 ){
			--i;
			movePrev(list);
		}
		if (index(list) >= 0){
			insertAfter(list, j);
		} else{
			prepend(list, j);
		}
	}


	moveFront(list);

	while(index(list)>=0){
		fprintf(output, "%s", lines[get(list)]);
		moveNext(list);
	}

	fclose(input);
	fclose(output);

	freeList(&list);

	return 0;
}