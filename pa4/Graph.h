/*********************************************************************************
* Calvin Hong, cbhong
* 2019 Summer CMPS101 PA4
* Graph.h
* Header File for Graph ADT
*********************************************************************************/
#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
/***macros****/
#define NIL -2
#define INF -1
#define WHITE 1
#define GRAY 2
#define BLACK 3
#include "List.h"
// Exported type --------------------------------------------------------------
typedef struct GraphObj* Graph;
/* Constructors-Destructors */
Graph newGraph(int n);
void freeGraph(Graph* pG);
/* Access functions */
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
/* Manipulation procedures */
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */
/* Other Functions */
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);
#endif // GRAPH_H_INCLUDED