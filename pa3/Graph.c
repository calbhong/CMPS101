#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

#define WHITE 1
#define GRAY 2
#define BLACK 3

typedef struct GraphObj{
   List *adj; //An array of Lists whose ith element contains the neighbors of vertex
   int *color; //An array of ints (or chars, or strings) whose ith ele
   int *parent; //An array of ints whose ith element is the parent o
   int *distance; //An array of ints whose ith element is the distance

   int order; //V
   int size; //E
   int source;//label of the vertex that was most recently used as source for BFS
} GraphObj;

Graph newGraph(int n){
    Graph graph = malloc(sizeof(struct GraphObj));

    graph->adj = calloc(n+1, sizeof(List));
    graph->color = calloc(n+1, sizeof(int));
    graph->parent = calloc(n+1, sizeof(int));
    graph->distance = calloc(n+1, sizeof(int));

    graph->order = n;
    graph->size = 0;
    graph->source = NIL;

    for(int i = 0; i<(n+1); i++)
    {
        graph->adj[i] = newList();
        graph->color[i] = WHITE;
        graph->parent[i] = NIL;
        graph->distance[i] = INF;
    }

    return graph;

}
void freeGraph(Graph* pG){
    Graph temp = *pG;
    for(int i = 0; i<(temp->order + 1); i++)
    {
        freeList(&(temp->adj[i]));
    }


    free(temp->adj);
    free(temp->parent);
    free(temp->distance);
    free(temp->color);

    free(*pG);
    *pG = NULL;

}
/*** Access functions ***/
int getOrder(Graph G){
    if (G == NULL) {
        printf("Graph Error: getOrder() called on NULL Graph. \n");
        exit(1);
    }
    return G->order;
}
int getSize(Graph G){
    if (G == NULL) {
        printf("Graph Error: getSize() called on NULL Graph. \n");
        exit(1);
    }
    return G->size;
}
int getSource(Graph G){
    if (G == NULL) {
        printf("Graph Error: getSource() called on NULL Graph. \n");
        exit(1);
    }
    return G->source;
}
int getParent(Graph G, int u){
  	if(G == NULL){
    	printf("Graph Error: getParent() called on NULL grpah reference. \n");
    	exit(1);
  	}else if( u < 1 || u > getOrder(G) ) {
    	printf("Graph Error: getParent() called on invalid vertex index. \n");
    	exit(1);
  	}
    return G->parent[u];
}
int getDist(Graph G, int u){}
void getPath(List L, Graph G, int u){}
/*** Manipulation procedures ***/
void makeNull(Graph G){}
void addEdge(Graph G, int u, int v){}
void addArc(Graph G, int u, int v){}
void BFS(Graph G, int s){}
/*** Other operations ***/
void printGraph(FILE* out, Graph G){
    if (G == NULL) {
        printf("Graph Error: printGraph() called on NULL graph reference. \n");
        exit(1);
    }else{
        for(int i = 1; i <= getOrder(G); i++){
            fprintf(out, "%d: ", i);
            printList(out, G->adj[i]);
            fprintf(out, "\n");
        }
    }
}


