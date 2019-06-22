#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   //Check if input is valid. Throws a Usage error if it is not
   if(argc != 3){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   FILE* in;
   FILE* out;
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   int first = 0;
   int second = 0;

   //Reads number of vertices in graph and makes a graph
   fscanf(in,"%d",&first);
   Graph G = newGraph(first);
   List S = newList();
   for(int i = 1; i <= first; i++){
      append(S,i);
   }

   //Assembles Graph G
   while(!feof(in)){
      fscanf(in,"%d",&first);
      fscanf(in,"%d",&second);
      if(first == 0 && second == 0){
         break;
      }
      addArc(G,first,second);
   }

   //Prints adjacently list
   printGraph(out,G); 
   fprintf(out,"\n");

   //Run DFS on G and G^T
   DFS(G,S);
   Graph Transpose = transpose(G);
   DFS(Transpose,S);

   //printGraph(out,Transpose);
   //Determine the strong components of G
   int scc = 0;

   for(int i = 1; i <= getOrder(G); i++){
      if(getParent(Transpose,i) == NIL){
         scc++;
      }
   }

fprintf(out,"G contains %d strongly connected components:\n",scc);
 
   //Print the strong components

   //Closes files
   fclose(in);
   fclose(out);
}
