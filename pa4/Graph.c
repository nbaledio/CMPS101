#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#define INF -1
#define NIL -2
#define WHITE 1
#define GRAY 2
#define BLACK 3

struct GraphObj{
   List *neighbors; //Array of lists whose ith element contains the neighbors of vertex i
   int *colors; //Array of ints whose ith element is the color of vertex i
   int *parents; //Array of ints whose ith element is the parent of vertex i
   int *distance; //Array of ints whose ith element is the distance from the (most recent) source to vertex i
   int vertices; //Order of graph
   int edges; //Size of graph
   int recent; //Label of the vertex that was most recently used as the source for BFS
};

/*** Constructors-Destructors ***/
Graph newGraph(int n){
   Graph NewGraph = calloc(1,sizeof(struct GraphObj));
   NewGraph->neighbors = calloc(n+1,sizeof(List));
   NewGraph->colors = calloc(n+1,sizeof(int));
   NewGraph->parents = calloc(n+1,sizeof(int));
   NewGraph->distance = calloc(n+1,sizeof(int));
   NewGraph->vertices = n;
   NewGraph->edges = 0;
   NewGraph->recent = NIL;
   for(int i = 0; i <= n; i++){
      NewGraph->neighbors[i] = newList();
   }
   return NewGraph;
}
void freeGraph(Graph* pG){
   Graph graph = *pG;
   for(int i = 0; i <= graph->vertices; i++){
      freeList(&graph->neighbors[i]);
   }
   free(graph->neighbors);
   free(graph->colors);
   free(graph->parents);
   free(graph->distance);
   free(graph);
}

/*** Access functions ***/
int getOrder(Graph G){
   return G->vertices;
}

int getSize(Graph G){
   return G->edges;
}

int getSource(Graph G){
   return G->recent;
}

int getParent(Graph G, int u){
   return G->parents[u];
}

int getDist(Graph G, int u){
   return G->distance[u];
}

void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/
void makeNull(Graph G){
   for(int i = 1; i <= G->vertices; i++){
      clear(G->neighbors[i]);
   }
   G->edges = 0;
}

void addEdge(Graph G, int u, int v){
   int found = 0;
   moveFront(G->neighbors[u]);
   while(index(G->neighbors[u]) != -1){
      if(v < get(G->neighbors[u])){
         insertBefore(G->neighbors[u],v);
         found = 1;
         break;
      }
      moveNext(G->neighbors[u]);
   }
   if(found == 0){
       append(G->neighbors[u],v);
   }
   int found2 = 0;
   moveFront(G->neighbors[v]);
   while(index(G->neighbors[v]) != -1){
      if(u < get(G->neighbors[v])){
         insertBefore(G->neighbors[v],u);
         G->edges++;
         found2 = 1;
         break;
      }
      moveNext(G->neighbors[v]);
   }
   if(found2 == 0){
      append(G->neighbors[v],u);
   }
   G->edges++;
}

void addArc(Graph G, int u, int v){
   moveFront(G->neighbors[u]);
   while(index(G->neighbors[u]) != -1){
      if(v < get(G->neighbors[u])){
         insertBefore(G->neighbors[u],v);
         G->edges++;
         return;
      }
      moveNext(G->neighbors[u]);
   }
   append(G->neighbors[u],v);
   G->edges++;
}

void BFS(Graph G, int s){
   for(int i = 1; i <= G->vertices; i++){
      G->colors[i] = WHITE;
      G->distance[i] = INF;
      G->parents[i] = NIL;
   } 
   G->colors[s] = GRAY;
   G->distance[s] = 0;
   G->parents[s] = NIL;
   G->recent = s;
   List queue = newList();
   append(queue,s);
   while(length(queue) != 0){
      int u = back(queue);
      deleteBack(queue);
      moveFront(G->neighbors[u]);
      for(int i = 0; i < length(G->neighbors[u]); i++){
         int v = get(G->neighbors[u]);
         if(G->colors[v] == WHITE){
            G->colors[v] = GRAY;
            G->distance[v] = G->distance[u] + 1;
            G->parents[v] = u;
            prepend(queue,v);
         }
         moveNext(G->neighbors[u]);
      }
      G->colors[u] = BLACK;
   }
   freeList(&queue);
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G){
   for(int i = 1; i <= G->vertices; i++){
      fprintf(out,"%d: ",i);
//printf("%d: ",i);
      moveFront(G->neighbors[i]);
      while(index(G->neighbors[i]) != -1){
         fprintf(out, "%d",get(G->neighbors[i]));
//printf("%d",get(G->neighbors[i]));
         moveNext(G->neighbors[i]);
         if(index(G->neighbors[i]) != -1){
            fprintf(out, " ");
//printf(" ");
         }
      }
      fprintf(out, "\n");
//printf("\n");
   }
}

