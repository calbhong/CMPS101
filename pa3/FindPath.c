#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "Graph.h"

#define MAX_LEN 250

int main(int argc, char * argv[])
{
    FILE *input;
    FILE *output;
    char line[MAX_LEN];


    if(argc != 3){
        printf("FindPath: Error, wrong number of arguments \n", argv[0]);
        exit(1);
    }

    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");

    if(input == NULL){
        printf("Cannot open file \n", argv[1]);
        exit(1);
    }

    if(output == NULL){
        printf("Cannot open file to write output", argv[2]);
        exit(1);
    }
    fgets(line, MAX_LEN, input);

    int length1 = 0;
    sscanf(line, "%d", &length1);

    Graph G = newGraph(length1);

    while( fgets(line, MAX_LEN, input) != NULL){
        int x;
        int y;
         x, y = 0;
        sscanf(line, "%d %d", &x, &y);
        if(x == 0 && y == 0){
            break;
        }
        addEdge(G, x, y);
    }
    printGraph(output, G);
    int count = 0;


    while( fgets(line, MAX_LEN, input) != NULL){
        int destination = 0;
        int source = 0;

        sscanf(line, "%d %d", &destination, &source);
        if(destination == 0 && source == 0){
            break;
        }
        if(count++ != 0){
            fprintf(output, "\n");   
        }
        fprintf(output, "\n");
        BFS(G, destination);

        int distance = getDist(G, source);
        fprintf(output, "The distance from %d to %d is " );
        if(distance == INF){
            fprintf(output, "infinity\n");
        }else{
            fprintf(output, "%d\n", distance);
        }
        

        List L = newList();

        getPath(L,G,source);
        if(front(L) == NIL){
            fprintf(output, "No %d-%d path exists", destination, source);
        }else{
            fprintf(output, "A shortest %d-%d path is: ", destination, source);
            printList(output, L);
        }
        freeList(&L);
    }

    //clearing
    fprintf(output, "\n");
    freeGraph(&G);

    fclose(input);
    fclose(output);

    return(0);
}