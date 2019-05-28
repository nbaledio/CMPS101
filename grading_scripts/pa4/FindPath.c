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

   //Reads edge pairs
   while(!feof(in)){
      fscanf(in,"%d",&first);
      fscanf(in,"%d",&second);
      if(first == 0 && second == 0){
         break;
      }
      addEdge(G,first,second);
      printf("%d ",first);
      printf("%d\n",second);   
   }
   
   //Prints adjacently list
   printGraph(out,G); 
   fprintf(out,"\n");
   List L = newList();

   //Reads path inputs
   while(!feof(in)){
      fscanf(in,"%d",&first);
      fscanf(in,"%d",&second);
      if(first == 0 && second == 0){
         break;
      }
      BFS(G,first);
      int distance = getDist(G,second);
      if(distance != -1){
         fprintf(out,"The distance from %d to %d is %d\n",first,second,distance);
         fprintf(out, "A shortest %d-%d path is: ",first,second);
         getPath(L,G,second);
         printList(out,L);
         fprintf(out,"\n");
      }else{
         fprintf(out,"The distance from %d to %d is infinity\n",first,second);
         fprintf(out,"No %d-%d path exists\n",first, second);
      }
      fprintf(out,"\n");
      clear(L);
   }

   //Frees memory
   freeList(&L);
   freeGraph(&G);

   //Close input and output files
   fclose(in);
   fclose(out);
}
