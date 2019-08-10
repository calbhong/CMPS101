/*********************************************************************************
* Calvin Hong, cbhong
* 2019 Summer CMPS101 PA3
* Graph.c
* Graph ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"


typedef struct GraphObj{
	List* adj; 
	int* color;
	int* parent;
	int* distance;

	int order;
	int size;
	int source;
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

	for(int i = 1; i <= n; i++){
		graph->adj[i] = newList();
		graph->color[i] = WHITE;
		graph->parent[i] = NIL;
		graph->distance[i] = INF;
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
int getDist(Graph G, int u){
	if (G == NULL){
		printf("Graph Error: calling getDist() on NULL graph reference. \n");
		exit(1);
	}else if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getDist() on NULL graph reference. \n");
		exit(1);
	}else{
		return G->distance[u];		
	}
}

void getPath(List L, Graph G, int u){
	if (G == NULL){
		printf("Graph Error: calling getPath() on NULL graph reference. \n");
		exit(1);
	}else if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getPath() on NULL graph reference. \n");
		exit(1);
	}else if(getSource(G) == NIL){
		printf("Graph Error: calling getPath() on NULL graph reference. \n");
		exit(1);
	}else{
		if (u == getSource(G)) {
			append(L, u);
		}else if(getParent(G, u) == NIL){
			clear(L);
			append(L, NIL);
		}else{
			getPath(L, G, G->parent[u]);
			append(L, u);
		}
	}
}

/*** Manipulation procedures ***/
void makeNull(Graph G){
	if (G == NULL) {
		printf("Graph Error: calling makeNull() on NULL graph reference. \n");
		exit(1);
	}else{
		for (int i = 1; i <= getOrder(G); i++) {
			clear(G->adj[i]);
			G->color[i] = WHITE; 
			G->parent[i] = NIL;
			G->distance[i] = INF;
		}	
 		G->size = 0;
		G->source = NIL;
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
void BFS(Graph G, int s){
	if (G == NULL) {
		printf("Graph Error: BFS() called on NULL Graph reference. \n");
		exit(1);
	} else if(!(s >= 1 && s <= getOrder(G))) {
		printf("Graph Error: calling BFS() with invalid source index. \n");
		exit(1);
	}else{
		for(int i = 0; i < (G->order +1); i++){
			G->color[i] = WHITE;
			G->parent[i] = NIL;
			G->distance[i] = INF;
		}
	    List Q = newList();
	    G->source = s;
	    G->color[s] = GRAY;
	    G->distance[s] = 0;
	    append(Q,s);

	    while(length(Q) > 0){
	        int temp = back(Q);
	        deleteBack(Q);
	        moveFront(G->adj[temp]);
	        while(index(G->adj[temp]) > -1){
	            int u = get(G->adj[temp]);
				if(G->color[u] == WHITE){
	                G->color[u] =  GRAY;
	                G->parent[u] = temp;
	                G->distance[u] = G->distance[temp] + 1;
	                prepend(Q,u);
	            }
	            moveNext(G->adj[temp]);
	        }
	    }
	    freeList(&Q);
	}
}
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


