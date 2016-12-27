#include "orderedLinkedList.h"

void copy(int * hostArray,int * array,int size);
void addArrayInternal(int path[],int cost);
void deleteAllFromInternal();
int * getArrayElementInternal(int i);
void initInternalList();
void addArrayInternal(int path[],int cost);
int getCostElementInternal(int i);
void substituteElementInternal(int path[],int cost,int i);
int countElementsInternal();

typedef struct node{
  struct dataType element;
  struct node * next;
  struct node * previous;
}node;

typedef struct orderedList{
  struct node * first;
}orderedList;

orderedList * list;

orderedList * internalList;

void initList(){
  list = malloc(sizeof(struct orderedList));
  list->first = malloc(sizeof(struct node));
  list->first->next=NULL;
  list->first->previous=NULL;
  initInternalList();
}


void addArray(int path[],int cost){
  node * actualNode = list->first;
  node * newNode = NULL;

  for(;actualNode->next!=NULL;){
    if(actualNode->next->element.cost > cost){
      newNode=malloc(sizeof(struct node));
      newNode->next=actualNode->next;
      actualNode->next->previous=newNode;
      newNode->element.cost=cost;
      copy(newNode->element.path,path,DIMENSION);
      newNode->previous=actualNode;
      actualNode->next=newNode;
      return;
     }
   actualNode = actualNode->next;
  }
  newNode=malloc(sizeof(struct node));
  newNode -> next = NULL;
  newNode->element.cost=cost;
  copy(newNode->element.path,path,DIMENSION);
  newNode->previous=actualNode;
  actualNode->next=newNode;
}

void addArrayFromPosition(int path[],int cost,int position){
  int j = 0;
  node * actualNode = list->first;
  node * newNode = NULL;

  for(j=0;j<position;j++){
    actualNode=actualNode->next;
  }

  for(;actualNode->next!=NULL;){
    if(actualNode->next->element.cost > cost){
      newNode=malloc(sizeof(struct node));
      newNode->next=actualNode->next;
      actualNode->next->previous=newNode;
      newNode->element.cost=cost;
      copy(newNode->element.path,path,DIMENSION);
      newNode->previous=actualNode;
      actualNode->next=newNode;
      return;
     }
   actualNode = actualNode->next;
  }
  newNode=malloc(sizeof(struct node));
  newNode -> next = NULL;
  newNode->element.cost=cost;
  copy(newNode->element.path,path,DIMENSION);
  newNode->previous=actualNode;
  actualNode->next=newNode;
}

void addArrayInPosition(int path[],int cost,int position){
  int j = 0;
  node * actualNode = list->first->next;

  for(j=0;j<position;j++){
    actualNode=actualNode->next;
  }
      actualNode->element.cost=cost;
      copy(actualNode->element.path,path,DIMENSION);
      return;
     }

int * getBestthElementArray(int th){
  node * actualNode = list->first;
  deleteAllFromInternal();
  for(;actualNode->next!=NULL;){
    addArrayInternal(actualNode->next->element.path,actualNode->next->element.cost);
    actualNode=actualNode->next;
  }
  return getArrayElementInternal(th);
}

int getBestthElementDistance(int th){
  node * actualNode = list->first;
  deleteAllFromInternal();
  for(;actualNode->next!=NULL;){
    addArrayInternal(actualNode->next->element.path,actualNode->next->element.cost);
    actualNode=actualNode->next;
  }
  return getCostElementInternal(th);
}

void substituteElement(int path[],int cost,int i){
  int j=0;
  node * actualNode = list->first->next;
  for(j=0;j<i;j++){
    actualNode=actualNode->next;
  }
  copy(actualNode->element.path,path,DIMENSION);
  actualNode->element.cost=cost;
}


void deleteAllButTwo(){
  int i=0;
  node * actualNode = list->first->next;
  for(;actualNode->next!=NULL;){
    actualNode=actualNode->next;
    i++;
  }
  for(i;i>1;i-=1){
    actualNode=actualNode->previous;
      free(actualNode->next);
  }
  actualNode->next=NULL;
}


int * getArrayElement(int i){
  int j=0;
  node * actualNode = list->first->next;
  for(j=0;j<i;j++){
    actualNode=actualNode->next;
  }
  return actualNode->element.path;
}

int getCostElement(int i){
  int j=0;
  node * actualNode = list->first->next;
  for(j=0;j<i;j++){
    actualNode=actualNode->next;
  }
  return actualNode->element.cost;
}

int countElements(){
  int i=0;
  node * actualNode = list->first;
  for(;actualNode->next!=NULL;){
    i++;
    actualNode=actualNode->next;
  }
  return i;
}
void copy(int * hostArray,int * array,int size){
  int i=0;
  for(i=0;i<size;i++){
    hostArray[i]=array[i];
  }
}


/*INTERNAL LIST*/
int countElementsInternal(){
  int i=0;
  node * actualNode = internalList->first;
  for(;actualNode->next!=NULL;){
    i++;
    actualNode=actualNode->next;
  }
  return i;
}
void substituteElementInternal(int path[],int cost,int i){
  int j=0;
  node * actualNode = internalList->first->next;
  for(j=0;j<i;j++){
    actualNode=actualNode->next;
  }
  copy(actualNode->element.path,path,DIMENSION);
  actualNode->element.cost=cost;
}

void deleteAllFromInternal(){
  node * actualNode = internalList->first;
  for(;actualNode->next!=NULL;){
    actualNode=actualNode->next;
  }
  for(;actualNode->previous!=NULL;){
    actualNode=actualNode->previous;
    actualNode->next->previous=NULL;
    free(actualNode->next->previous);
    free(actualNode->next);
  }
  actualNode->next=NULL;
}
int * getArrayElementInternal(int i){
  int j=0;
  node * actualNode = internalList->first->next;
  for(j=0;j<i;j++){
    actualNode=actualNode->next;
  }
  return actualNode->element.path;
}

int getCostElementInternal(int i){
  int j=0;
  node * actualNode = internalList->first->next;
  for(j=0;j<i;j++){
    actualNode=actualNode->next;
  }
  return actualNode->element.cost;
}


void initInternalList(){
  internalList = malloc(sizeof(struct orderedList));
  internalList->first = malloc(sizeof(struct node));
  internalList->first->next=NULL;
  internalList->first->previous=NULL;
}

void addArrayInternal(int path[],int cost){
  node * actualNode = internalList->first;
  node * newNode = NULL;

  for(;actualNode->next!=NULL;){
    if(actualNode->next->element.cost > cost){
      newNode=malloc(sizeof(struct node));
      newNode->next=actualNode->next;
      actualNode->next->previous=newNode;
      newNode->element.cost=cost;
      copy(newNode->element.path,path,DIMENSION);
      newNode->previous=actualNode;
      actualNode->next=newNode;
      return;
     }
   actualNode = actualNode->next;
  }
  newNode=malloc(sizeof(struct node));
  newNode -> next = NULL;
  newNode->element.cost=cost;
  copy(newNode->element.path,path,DIMENSION);
  newNode->previous=actualNode;
  actualNode->next=newNode;
}
