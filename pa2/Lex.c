#include<stdio.h>
#include<stdlib.h>
#include "List.h"

int main(int argc, char* argv[]){

   //Check if input is valid. Throws a Usage error if it is not
   if(argc != 3){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   List test = newList();
   List test2 = newList();
   //List test3 = newList();
   prepend(test,10);
   prepend(test,20);
   prepend(test,30);
   clear(test);
   //prepend(test,20);
   prepend(test2, 10);
   //int res = equals(test,test2);
   printf("%d\n",length(test));
   //printf("%d\n",front(test));
   //printf("%d\n",back(test));
   //printf("%d\n",length(test2)); 
   //printf("%d\n",length(test3));

}
