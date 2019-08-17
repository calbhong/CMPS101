/*********************************************************************************
* Calvin Hong, cbhong
* 2019 Summer CMPS101 PA4
* Graph.c
* Graph ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#include "Graph.h"

typedef struct GraphObj{
	List* adj; 
	int* color;
	int* parent;
	int* discover;
	int* finish;
	int order;
	int size;
	int time;
} GraphObj;

Graph newGraph(int n){ 
	Graph graph = malloc(sizeof(struct GraphObj));

	graph->adj = calloc(n+1, sizeof(List));
	graph->color = calloc(n+1, sizeof(int));
	graph->parent = calloc(n+1, sizeof(int));
	graph->discover = calloc(n+1, sizeof(int));
	graph->finish = calloc(n+1, sizeof(int));

	graph->order = n;
	graph->size = 0;
	graph->time = UNDEF;

	for(int i = 1; i <= n; i++){
		graph->adj[i] = newList();
		graph->color[i] = WHITE;
		graph->parent[i] = NIL;
		graph->discover[i] = UNDEF;
		graph->finish[i] = UNDEF;
	}
	return graph;
}
void freeGraph(Graph* pG){
	Graph temp = *pG;
	for(int i = 0; i<(temp->order + 1); i++){
		freeList(&(temp->adj[i]));
	}

	free(temp->adj);
	free(temp->parent);
	free(temp->discover);
	free(temp->finish);
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

int getParent(Graph G, int u){
	if (G == NULL){
		printf("Graph Error: getParent() called on NULL grpah reference. \n");
		exit(1);
	}else if( u < 1 || u > getOrder(G) ) {
		printf("Graph Error: getParent() called on invalid vertex index. \n");
		exit(1);
	}else{
		return G->parent[u];
	}
	
}
int getDiscover(Graph G, int u){
	if (G == NULL){
		printf("Graph Error: calling getDiscover() on NULL graph reference. \n");
		exit(1);
	}else if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getDiscover() on NULL graph reference. \n");
		exit(1);
	}else{
		return G->discover[u];		
	}
}

int getFinish(Graph G, int u){
	if (G == NULL){
		printf("Graph Error: getFinish() called on NULL graph reference. \n");
		exit(1);
	} else if(u < 1 || u > getOrder(G)){
		printf("Graph Error: getFinish() called on invalid vertex index. \n");
		exit(1);
	} 
	return G->finish[u];
}

/*** Manipulation procedures ***/
void addArc(Graph G, int u, int v){
	if (G == NULL) {
		printf("Graph Error: calling addArc() on NULL Graph reference. \n");
		exit(1);
	}else if (u < 1 || u > getOrder(G)){
		printf("Graph Error: calling addArc() on invalid vertex index. \n");
		exit(1);
	}else if (v < 1 || v > getOrder(G)){
		printf("Graph Error: calling addArc() on invalid vertex index. \n");
		exit(1);
	}else{
		if (length(G->adj[u]) != 0) {
			moveFront(G->adj[u]);
			while(index(G->adj[u]) != -1){
				if (v < get(G->adj[u])) {
					insertBefore(G->adj[u], v);
					break;
				}else if (v > back(G->adj[u])) {
					append(G->adj[u], v);
					break;
				}else if (get(G->adj[u]) == v) {
					break;
				}
				moveNext(G->adj[u]);
			}
		} else {
			append(G->adj[u], v);
		}
		G->size++;
	}
}

void addEdge(Graph G, int u, int v){
	if (G == NULL) {
		printf("Graph Error: calling addEdge() on NULL Graph reference. \n");
		exit(1);
	}else if (u < 1 || u > getOrder(G)){
		printf("Graph Error: calling addArc() on invalid vertex index. \n");
		exit(1);
	}else if (v < 1 || v > getOrder(G)){
		printf("Graph Error: calling addArc() on invalid vertex index. \n");
		exit(1);
	}else{
		addArc(G, u, v);
		addArc(G, v, u);
		G->size--;
	}
}

void Visit(Graph G, List S, int u){
	if (G == NULL){
		printf("Graph Error: calling Visit() on NULL Graph reference. \n");
		exit(1);		
	}else {
		G->color[u] = GRAY;
		G->discover[u] = ++G->time;
		if (length(G->adj[u]) > 0){
			moveFront(G->adj[u]);
			for(int i=0; i<length(G->adj[u]); i++){
				int v = get(G->adj[u]);
				if(G->color[v] == WHITE){
					G->parent[v] = u;
					Visit(G, S, v);
				}
			moveNext(G->adj[u]);
			}
		}
		G->color[u] = BLACK;
		G->finish[u] = ++G->time;
		prepend(S, u);
		deleteBack(S);	
	}
}

void DFS(Graph G, List S){
	if (G == NULL) {
		printf("Graph Error: DFS() called on NULL Graph reference. \n");
		exit(1);
	} else if(length(S) != getOrder(G)) {
		printf("Graph Error: calling DFS() with invalid source index. \n");
		exit(1);
	}else{
		for(int i=1; i<=getOrder(G); i++){
			G->color[i] = WHITE;
			G->parent[i] = NIL;
			G->discover[i] = UNDEF;
			G->finish[i] = UNDEF;
		}
		List L = copyList(S);
		moveFront(L);
		G->time = 0;
		for(int i=1; i<= getOrder(G); i++){
			int x = get(L);
			if(G->color[x] == WHITE){
				Visit(G, S, x);
			}
			moveNext(L);
		}
		freeList(&L);
		return;
	}
}
/*** Other operations ***/
Graph transpose(Graph G){
	if(G == NULL){
		printf("Graph Error: transpose() called on NULL graph reference. \n");
		exit(1);
	}
	Graph H = newGraph(getOrder(G));
	for(int i=1; i<=getOrder(G); i++){
		if(length(G->adj[i]) > 0){
			moveFront(G->adj[i]);
			for(int j=0; j<length(G->adj[i]); j++){
				addArc(H, get(G->adj[i]), i);
				moveNext(G->adj[i]);
		   }
		}
	}
	return H;
}
Graph copyGraph(Graph G){
	if(G == NULL){
		printf("Graph Error: transpose() called on NULL graph reference. \n");
		exit(1);
	}
	Graph H = newGraph(G->order);
	for(int i=1; i<=getOrder(G); i++){
		if(length(G->adj[i]) > 0){
			moveFront(G->adj[i]);
			for(int j=0; j<length(G->adj[i]); j++){
				addArc(H, i, get(G->adj[i]));
				moveNext(G->adj[i]);
			}
		}
		H->color[i] = G->color[i];
		H->parent[i] = G->parent[i];
		H->discover[i] = G->discover[i];
		H->finish[i] = G->finish[i]; 
	}
	return H;
}

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


