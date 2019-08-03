#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

typedef struct GraphObj{
   List *adj; //An array of Lists whose ith element contains the neighbors of vertex
   int *color; //An array of ints (or chars, or strings) whose ith ele
   int *parent; //An array of ints whose ith element is the parent o
   int *distance; //An array of ints whose ith element is the distance
   int order; //the number of vertices
   int size; //the number of edges
   int source;//label of the vertex that was most recently used as source for BFS
} GraphObj;

Graph newGraph(int n){
	
}
void freeGraph(Graph* pG){}
/*** Access functions ***/
int getOrder(Graph G){}
int getSize(Graph G){}
int getSource(Graph G){}
int getParent(Graph G, int u){}
int getDist(Graph G, int u){}
void getPath(List L, Graph G, int u){}
/*** Manipulation procedures ***/
void makeNull(Graph G){}
void addEdge(Graph G, int u, int v){}
void addArc(Graph G, int u, int v){}
void BFS(Graph G, int s){}
/*** Other operations ***/
void printGraph(FILE* out, Graph G){}


