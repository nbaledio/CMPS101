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
   fprintf(out, "Adjacency list representation of G:\n");
   printGraph(out,G); 
   fprintf(out,"\n");

   //Run DFS on G and G^T
   DFS(G,S);
   Graph T = transpose(G);
   DFS(T,S);

   //printGraph(out,Transpose);
   //Determine/Print the strong components of G
   
   //Count number of SCCs to print
   int scc = 0;
   List stack = newList();
   moveFront(S);
   for(int i = 1; i<= getOrder(G); i++){
      if(getParent(T,i) == NIL){
         scc++;
      }
   }

   //Print the strong components
   fprintf(out,"G contains %d strongly connected components:\n",scc);
   
   //Iterate through list and add to stack list of components. Stop and print once NIL is reached
   int count = 1;
   moveBack(S);
   for(int i = 1; i <= length(S); i++){
      prepend(stack,get(S));
      if(getParent(T,get(S)) == NIL){
         fprintf(out,"Component %d: ",count);
         printList(out,stack);
         fprintf(out,"\n");
         clear(stack);
         count++;
      }
      movePrev(S);
   }

   //Frees Memory
   freeList(&stack);
   freeList(&S);
   freeGraph(&G);
   

   //Closes files
   fclose(in);
   fclose(out);
}
