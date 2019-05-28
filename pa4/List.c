#include<stdio.h>
#include<stdlib.h>
#include "List.h"

typedef struct NodeObj{
        int number;
        struct NodeObj* next;
        struct NodeObj* prev;
}NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
        int size;
        Node cursor;
        Node front;
        Node back;
}ListObj;

// Constructors-Destructors ---------------------------------------------------
List newList(void){
   List newlist = malloc(sizeof(ListObj));
   newlist->cursor = NULL;
   newlist->front = NULL;
   newlist->back = NULL;
   newlist->size = 0;
   return newlist;
}
void freeList(List* pL){
   clear(*pL);
   free(*pL); 
}

// Access functions -----------------------------------------------------------
int length(List L){
   return L->size;
}
int index(List L){
   if(L->cursor == NULL){
      return -1;
   }else{
      int index = 0;
      Node iter = L->front;
      while(iter != L->cursor){
         index++;
         iter = iter->next;
      }
      return index;
   }
}
int front(List L){
   return L->front->number;
}
int back(List L){
   return L->back->number;
}
int get(List L){
   return L->cursor->number;
}
int equals(List A, List B){
   if(A->size != B->size){
      return 0;
   }
   Node A_iter = A->front;
   Node B_iter = B->front;
   for(int i = 0; i < A->size; i++){
      if(A_iter->number != B_iter->number){
         return 0;
      }
      A_iter = A_iter->next;
      B_iter = B_iter->next;
   }
   return 1;
}

// Manipulation procedures ----------------------------------------------------
void clear(List L){
   if(L->size == 1){
      Node deleted = L->front;
      free(deleted);
      L->front = NULL;
      L->back = NULL;
      L->cursor = NULL;
      L->size = 0;
   }else{
      //For some reason, looping deleteFront gives no errors 
      //vs. iterating and freeing
      int size = L->size;
      for(int i = 0; i < size; i++){
         deleteFront(L);
      }
      L->cursor = NULL;
   }
}
void moveFront(List L){
   if(L->size != 0){
      L->cursor = L->front;
   }
}
void moveBack(List L){
   if(L->size != 0){
      L->cursor = L->back;
   }
}
void movePrev(List L){
   if(L->cursor != NULL){
      L->cursor = L->cursor->prev;
   }
}
void moveNext(List L){
   if(L->cursor != NULL){
      L->cursor = L->cursor->next;
   }
}
void prepend(List L, int data){
   if(length(L) == 0){
      Node newelement = malloc(sizeof(NodeObj));
      newelement->number = data;
      L->front = newelement;
      L->back = newelement;
      L->size++;
   }else if(length(L) == 1){
      Node newelement = malloc(sizeof(NodeObj));
      newelement->number = data;
      newelement->next = L->back;
      L->back->prev = newelement;
      L->front = newelement;
      L->size++;
   }else{
      Node newelement = malloc(sizeof(NodeObj));
      newelement->number = data;
      newelement->next = L->front;
      L->front->prev = newelement;
      L->front = newelement;
      L->size++;
   }
}
void append(List L, int data){
   if(length(L) == 0){
      Node newelement = malloc(sizeof(NodeObj));
      newelement->number = data;
      L->front = newelement;
      L->back = newelement;
      L->size++;
   }else if (length(L) == 1){
      Node newelement = malloc(sizeof(NodeObj));
      newelement->number = data;
      newelement->prev = L->front;
      L->front->next = newelement;
      L->back = newelement;
      L->size++;
   }else{
      Node newelement = malloc(sizeof(NodeObj));
      newelement->number = data;
      newelement->prev = L->back;
      L->back->next = newelement;
      L->back = newelement;
      L->size++;
   }
}
void insertBefore(List L, int data){
   if (L->cursor == L->front || L->size == 1){
      prepend(L,data);
   }else{
      Node newelement = malloc(sizeof(NodeObj));
      newelement->number = data;
      newelement->next = L->cursor;
      newelement->prev = L->cursor->prev;
      L->cursor->prev->next = newelement;
      L->cursor->prev = newelement;
      L->size++;
   }
}
void insertAfter(List L, int data){
   if(L->cursor == L->back || L->size == 1){
      append(L,data);
   }else{
      Node newelement = malloc(sizeof(NodeObj));
      newelement->number = data;
      newelement->next = L->cursor->next;
      newelement->prev = L->cursor;
      L->cursor->next->prev = newelement;
      L->cursor->next = newelement;
      L->size++;
   }
}
void deleteFront(List L){
   if(L->cursor == L->front){
      L->cursor = NULL;
   }
   if(L->size == 1){
      free(L->front);
      L->front = NULL;
      L->back = NULL;
      L->size--;
   }else{
      Node deleted = L->front;
      L->front = L->front->next;
      free(deleted);
      L->size--;
   }
}
void deleteBack(List L){
   if(L->cursor == L->back){
      L->cursor = NULL;
   }
   if(L->size == 1){
      free(L->back);
      L->front = NULL;
      L->back = NULL;
      L->size--;
   }else{
      Node deleted = L->back;
      L->back = L->back->prev;
      free(deleted);
      L->size--;
   }
}
void delete(List L){
   if(L->cursor == L->front){
      deleteFront(L);
      L->cursor = NULL;
   }else if(L->cursor == L->back){
      deleteBack(L);
      L->cursor = NULL;
   }else{
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
      Node deleted = L->cursor;
      free(deleted);
      L->cursor = NULL;
      L->size--;
   }
}

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L){
   Node iter = L->front;
   for(int i = 0; i < L->size; i++){
      fprintf(out,"%d", iter->number);
      iter = iter->next;
      if(i + 1 != L->size){
         fprintf(out,"%s"," ");
      }
   }
}
List copyList(List L){
   List copy = newList();
   Node iter = L->front;
   if(L->size == 1){
      copy->front = L->front;
      copy->back = L->back;
      copy->size++;
   }else{
      for(int i = 0; i < L->size; i++){
         append(copy, iter->number);
         iter = iter->next;
      }
   }
   return copy;
}
int isFront(List L){
   if(L->cursor == L->front){
      return 1;
   }
   return 0;
}
int isBack(List L){
   if(L->cursor == L->back){
      return 1;
   }
   return 0;
}
