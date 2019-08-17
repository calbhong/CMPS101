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
	FILE *in;
	FILE *out;
	char line[MAX_LEN];

	if(argc != 3){
		printf("Usage: %s <in file> <out file>\n", argv[0]);
		exit(1);
	}
	//open io
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	if(in == NULL){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}

	if(out == NULL){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}

	fgets(line, MAX_LEN, in);
	int size = 0;
	sscanf(line, "%d", &size);

	Graph G = newGraph(size);

	while(fgets(line, MAX_LEN, in) != NULL){
		int x = 0;
		int y = 0;
		sscanf(line, "%d %d", &x, &y);
		if(x == 0 && y == 0){
			break;
		}else{
			addArc(G, x, y);
		}
	}
    fprintf(out, "Adjacency list representation of G: \n");
    printGraph(out, G);
    fprintf(out, "\n");

    List L = newList();
    for (int i = 1; i <= size; i++){
        append(L, i);
    }

    DFS(G, L);
    Graph trans = transpose(G);
    DFS(trans, L);

    List *comp = calloc((size+1), sizeof(List));
    int k;
    if(length(L) != 0){
        k = 1;
        moveBack(L);
        comp[k] = newList();
        while (index(L) != -1){
            prepend(comp[k], get(L));
            if (getParent(trans, get(L)) == NIL){
                if(index(L) != 0){
                    k++;
                    comp[k] = newList();
                }
            }
            movePrev(L);
        }
    }


    fprintf(out, "G contains %d strongly connected components:\n", k);
    for (int i = 1; i <= k; i++){
        fprintf(out, "Component %d: ", i);
        printList(out, comp[i]);
        fprintf(out, "\n");
    } 

    for (int n = 1; n <= k; n++){
        freeList(&(comp[n]));
    }

    freeList(&L);
    freeList(comp);
    freeGraph(&G);
    freeGraph(&trans);


    fclose(in);
    fclose(out);
    return 0;
}