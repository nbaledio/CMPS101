#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "List.h"

int main(int argc, char* argv[]){

   //Check if input is valid. Throws a Usage error if it is not
   if(argc != 3){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(EXIT_FAILURE);
   }
 
   FILE* in;  /* file handle for input */  
   FILE* out; /* file handle for output */
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   
   //Opens file to count number of words for array size
   int length = 0;
   char line[256];
   while(fgets(line,256,in) != NULL){
      length++;
   } 
   fclose(in);
   
   //Re-opens file to read line-by-line and add words to array
   in = fopen(argv[1], "r");
   char *array[length];
   int counter = 0;
   while(fgets(line,256,in) != NULL){
      array[counter] = malloc(strlen(line)+1);
      strcpy(array[counter],line);
      counter++;
   }   
   //List creation and sorting (insertion sort)
   List list = newList();
   for(int i = 0; i < length; i++){
      if(i == 0){
         prepend(list, i);
      }else{
         moveBack(list);
         bool inserted = false;
         while(inserted == false){
            int check = strcmp(array[i],array[get(list)]);
            if(check <= 0){
               if(isFront(list) == 1){
                  prepend(list,i);
                  inserted = true;
               }else{
                  movePrev(list);
               }
            }else{
               if(isBack(list) == 1){
                  append(list,i);
                  inserted = true;
               }else{
                  insertAfter(list,i);
                  inserted = true;
               }
            }
         }
      }
   }  

   //Prints lexicographic sorting of input file to output file
   moveFront(list);
   for(int i = 0; i < length; i++){
      fprintf(out,array[get(list)]);
      moveNext(list);
   }

   //Closes files
   fclose(in);
   fclose(out);

   //Frees memory   
   freeList(&list);
   for(int i = 0; i < length; i++){
      free(array[i]);
   }
}
