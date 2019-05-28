#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[]){
   Graph G = newGraph(6);
   addEdge(G,1,2);
   addEdge(G,2,4);
   addEdge(G,2,5);
   addEdge(G,5,6);
   addEdge(G,6,3);
   addEdge(G,2,1);
   BFS(G,2);
   List L = newList();
   getPath(L,G,3);
   printList(stdout,L);
   printf("\n");
   printf("%d\n",getOrder(G));
   printf("%d\n",getSize(G)); 
   printf("%d\n",getParent(G,2));
   printf("%d\n",getParent(G,5));
   printf("%d\n",getDist(G,3));
   printf("%d\n",getDist(G,1));
   printGraph(stdout,G); 
   freeList(&L);
   freeGraph(&G);
}
