#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

#define WHITE 1
#define GRAY 2
#define BLACK 3

struct GraphObj{
   List *neighbors; //Array of lists whose ith element contains the neighbors of vertex i
   int *colors; //Array of ints whose ith element is the color of vertex i
   int *parents; //Array of ints whose ith element is the parent of vertex i
   int *discover; //Array of ints whose ith element is the discover time of vertex i
   int *finish; //Array of ints whose ith element is the finish time of vertex i
   int vertices; //Order of graph
   int edges; //Size of graph
   int time; //Timer for search time
};

/*** Constructors-Destructors ***/
Graph newGraph(int n){
   Graph NewGraph = calloc(1,sizeof(struct GraphObj));
   NewGraph->neighbors = calloc(n+1,sizeof(List));
   NewGraph->colors = calloc(n+1,sizeof(int));
   NewGraph->parents = calloc(n+1,sizeof(int));
   NewGraph->discover = calloc(n+1,sizeof(int));
   NewGraph->finish = calloc(n+1,sizeof(int));
   NewGraph->vertices = n;
   NewGraph->edges = 0;
   NewGraph->time = UNDEF;
   for(int i = 0; i <= n; i++){
      NewGraph->neighbors[i] = newList();
      NewGraph->colors[i] = WHITE;
      NewGraph->parents[i] = NIL; 
      NewGraph->discover[i] = UNDEF;
      NewGraph->finish[i] = UNDEF;
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
   free(graph->discover);
   free(graph->finish);
   free(graph);
}

/*** Access functions ***/
int getOrder(Graph G){
   return G->vertices;
}

int getSize(Graph G){
   return G->edges;
}

int getParent(Graph G, int u){
   return G->parents[u];
}

int getDiscover(Graph G, int u){
   return G->discover[u];
}
int getFinish(Graph G, int u){
   return G->finish[u];
}

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v){
   int found = 0;
   moveFront(G->neighbors[u]);
   while(index(G->neighbors[u]) != -1){
      if(v == get(G->neighbors[u])){
         return;
      }
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
   for(int i = 0; i < length(G->neighbors[u]); i++){
      if(v == get(G->neighbors[u])){
         return;
      }
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
//Copy s, and use s for order
//CHANGE: use copy for order, s for decreasing list
void DFS(Graph G, List s){
 if(length(s) != getOrder(G)){
        printf("Error: Graph and list are different sizes");
        exit(1);
    }
   for(int i = 1; i <= G->vertices; i++){
      G->colors[i] = WHITE;
      G->parents[i] = NIL;
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
   }
   G->time = 0;
   List order = copyList(s);
   clear(s);
   moveFront(order);
   while(index(order) != -1){
      if(G->colors[get(order)] == WHITE){
         Visit(G,get(order),s);
      }
      moveNext(order);
   }
   freeList(&order);
}

void Visit(Graph G, int u,List s){
   G->time++;
   G->discover[u] = G->time;
   G->colors[u] = GRAY;
   moveFront(G->neighbors[u]);
   for(int i = 0; i < length(G->neighbors[u]); i++){
      if(G->colors[get(G->neighbors[u])] == WHITE){
         G->parents[get(G->neighbors[u])] = u;
         Visit(G,get(G->neighbors[u]),s);
      }
      moveNext(G->neighbors[u]);
   }
   G->colors[u] = BLACK;
   G->time++;
   G->finish[u] = G->time;
   prepend(s,u); 
}

/*** Other operations ***/
//USE ACTUAL LIST. COPYLIST DOES NOT WORK
Graph transpose(Graph G){
   Graph T = newGraph(G->vertices);
   for(int i = 1; i <= G->vertices; i++){
      moveFront(G->neighbors[i]);
      for(int j = 0; j < length(G->neighbors[i]); j++){
        addArc(T,get(G->neighbors[i]),i);
        moveNext(G->neighbors[i]);
      }
   }
   return T;
}
//COPYLIST WORKS HERE THOUGH
Graph copyGraph(Graph G){
   Graph copy = newGraph(G->vertices);
   for(int i = 0; i <= G->vertices; i++){
      copy->neighbors[i] = copyList(G->neighbors[i]);
      copy->colors[i] = G->colors[i];
      copy->parents[i] = G->parents[i];
      copy->discover[i] = G->discover[i];
      copy->finish[i] = G->finish[i];
   }
   copy->edges = G->edges;
   copy->time = G->time;
   return copy;
}
void printGraph(FILE* out, Graph G){
   for(int i = 1; i <= G->vertices; i++){
      fprintf(out,"%d: ",i);
//printf("%d: ",i);
      moveFront(G->neighbors[i]);
      for(int j = 0; j < length(G->neighbors[i]); j++){
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

