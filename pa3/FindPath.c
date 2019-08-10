/*********************************************************************************
* Calvin Hong, cbhong
* 2019 Summer CMPS101 PA3
* FindPath.c
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

	//check args
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
	//read input
	fgets(line, MAX_LEN, input);
	int size = 0;
	sscanf(line, "%d", &size);

	//gen new graph
	Graph G = newGraph(size);

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
	printGraph(output, G);

	//write to file
	while(fgets(line, MAX_LEN, input) != NULL){
		int u = 0;
		int v = 0;

		sscanf(line, "%d %d", &u, &v);
		if(u == 0 && v == 0){
			break;
		}
		fprintf(output, "\n");
		List L = newList();
		BFS(G, u);
		getPath(L,G,v);

		int distance = getDist(G, v);
		fprintf(output, "The distance from %d to %d is ", u, v);
		
		if(distance == INF){
			fprintf(output, "infinity\n");
		}else{
			fprintf(output, "%d\n", distance);
		}


		if(front(L) == NIL){
			fprintf(output, "No %d-%d path exists", u, v);
		}else{
			fprintf(output, "A shortest %d-%d path is: ", u, v);
			printList(output, L);
		}
		freeList(&L);
	}

	//clear
	freeGraph(&G);
	//close
	fclose(input);
	fclose(output);

	return(0);
}