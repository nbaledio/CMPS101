//-----------------------------------------------------------------------------
// Graph.h
// Header file for the Graph ADT
//-----------------------------------------------------------------------------

#ifndef Graph_H_INCLUDE_
#define Graph_H_INCLUDE_
#include "List.h"
#define NIL 0
#define UNDEF -1

/***typedef for Graph object***/
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

/*** Manipulation procedures ***/
void addArc(Graph G, int u, int v);
void addEdge(Graph G, int u, int v);
void DFS(Graph G, List s);
void Visit(Graph G, int u, List s);

/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif
