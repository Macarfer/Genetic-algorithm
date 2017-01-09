#include "fileManager.h"
#include <stdio.h>
#include <limits.h>

typedef struct dataType{
  int cost;
  int path[DIMENSION];
}dataType;

void initList();
void addArray(int[],int);
int * getArrayElement(int index);
int countElements();
int getCostElement(int i);
void deleteAllButTwo();
void substituteElement(int path[],int cost,int i);
void addArrayFromPosition(int path[],int cost,int position);
void addArrayInPosition(int path[],int cost,int position);
int * getBestthElementArray(int th);
int getBestthElementDistance(int th);
void deleteAllBut(int number);
