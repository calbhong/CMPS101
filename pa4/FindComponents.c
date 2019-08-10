/*********************************************************************************
* Calvin Hong, cbhong
* 2019 Summer CMPS101 PA4
* FindComponents.c 
* Implementation of Graph & List ADT 
*********************************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "Graph.h"

#define MAX_LEN 1000

int main(int argc, char * argv[]){
	FILE *input;
	FILE *output;
	char line[MAX_LEN];

	if(argc != 3){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	//open io
	input = fopen(argv[1], "r");
	output = fopen(argv[2], "w");

	if(input == NULL){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}

	if(output == NULL){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}

	fgets(line, MAX_LEN, input);
	int size = 0;
	sscanf(line, "%d", &size);

	Graph G = newGraph(size);
	List L = newList();

	while(fgets(line, MAX_LEN, input) != NULL){
		int x = 0;
		int y = 0;
		sscanf(line, "%d %d", &x, &y);
		if(x == 0 && y == 0){
			break;
		}else{
			addEdge(G, x, y);
		}

	}
}