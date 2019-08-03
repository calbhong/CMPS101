#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "Graph.h"

#define MAX_LEN 255

int main(int argc, char * argv[])
{
    FILE *inputFile;
    FILE *outputFile;
    char line[MAX_LEN];


    if(argc != 3)
    {
        printf("FindPath: Error, wrong number of arguments \n", argv[0]);
        exit(1);
    }

    inputFile = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w");

    if(inputFile == NULL)
    {
        printf("Cannot open file \n", argv[1]);
        exit(1);
    }

    if(outputFile == NULL)
    {
        printf("Cannot open file to write output", argv[2]);
        exit(1);
    }


   fgets(line, MAX_LEN, inputFile);

   int length1 = 0;
   sscanf(line, "%d", &length1);


   Graph G = newGraph(length1);

   while( fgets(line, MAX_LEN, inputFile) != NULL)
   {
      int x;
      int y;
      x, y = 0;
      sscanf(line, "%d %d", &x, &y);
      if(x == 0 && y == 0)
         break;
      addEdge(G, x, y);
   }
   printGraph(outputFile, G);
   int count = 0;


   while( fgets(line, MAX_LEN, inputFile) != NULL)
   {
       int destination = 0;
       int source = 0;

       sscanf(line, "%d %d", &destination, &source);
       if(destination == 0 && source == 0)
       {
           break;
       }
       if(count++ != 0)
        fprintf(outputFile, "\n");
       fprintf(outputFile, "\n");
       BFS(G, destination);

       int distance = getDist(G, source);
       fprintf(outputFile, "The distance from %d to %d is " );
       if(distance == INF){
        fprintf(outputFile, "infinity\n");
       }
       else
        fprintf(outputFile, "%d\n", distance);

       List L = newList();

       getPath(L,G,source);
       if(front(L) == NIL){
        fprintf(outputFile, "No %d-%d path exists", destination, source);
       }
       else{
        fprintf(outputFile, "A shortest %d-%d path is: ", destination, source);
        printList(outputFile, L);
       }
       freeList(&L);
}

    //clearing
    fprintf(outputFile, "\n");
    freeGraph(&G);

    fclose(inputFile);
    fclose(outputFile);

    return(0);


}