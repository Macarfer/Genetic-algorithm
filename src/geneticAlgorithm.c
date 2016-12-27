#include "geneticAlgorithm.h"

int populationArray[POPULATIONSIZE][DIMENSION+1]={0};
int populationDistances[POPULATIONSIZE]={0};
int exchangeCandidates[POPULATIONSIZE];
int sons[POPULATIONSIZE][DIMENSION+1]={0};
int sonsDistance[POPULATIONSIZE]={0};
int usedIndexInExchange[POPULATIONSIZE][DIMENSION+1]={0};
int auxiliarNullArray[DIMENSION]={0};


int solIterations=0;
int solDistance=MAX_INT;
int solPath[DIMENSION+1];

int distanceMatrix[DIMENSION][DIMENSION];
int swapMatrix[DIMENSION]={7};
int actualSolution[DIMENSION+1];
int solution[DIMENSION+1];
double TEMPERATURE=0;
double TEMPERATURE_ZERO=0;
double EXPONENTIAL=0;
int DELTA = 0;
short ACEPTED=0;
short ACEPTED_SOLUTIONS=0;
short POSIBLE_SOLUTIONS=0;
short cooled=1;
int tDistance=0;
int iterations=0;
int bestIndex0;
int bestIndex1;
int numberOfCities;
int actualDistance;
int newDistance=0;
int swapArrayCount;
int swapArrayDimension=0;
int minimalDistance;
int restart = 1;
short activatedRandoms=0;
double * randoms;
int actualRandom=-1;

void printMatrix();
float calculateRandom();
short isvalueinarray(int val, int *arr, int size);
void printActualSolution();
void calculateInitialDistance();
void swap(int * vector,int index0,int index1);
void copyArray(int * hostArray, int * array,int size);
void calculateNeighbors();
void printArray(int * array,int size);
int calculateDistance(int * vector);void mainLoop();
void binaryTournamentSelection();
void exchange();
void mutation();
void mainLoop();
void replacement();
void printInlineArray(int * array,int size);


void run(){
  initList(); swapMatrix[1]=1;
  int i;
  printf("POBLACION INICIAL\n");
  generateInitialSolution();
  generateGreedyInitialSolution();
  for(i=0;i<POPULATIONSIZE;i++){
    printf("INDIVIDUO %d = {FUNCION OBJETIVO (km): %d, ",i,populationDistances[i]);
    printArray(populationArray[i],DIMENSION);
    printf("}\n");
  }
  mainLoop();
  printf("\n\nMEJOR SOLUCION: \nRECORRIDO: ");
  printInlineArray(solPath,DIMENSION);
  printf("\nFUNCION OBJETIVO (km): %d\n",solDistance);
  printf("ITERACION: %d\n",solIterations);
}

void generateInitialSolution(){
int index=1,actualValue,indexSolutions=0;
int usedNumbers[POPULATIONSIZE][DIMENSION]={0};

  for(indexSolutions; indexSolutions< POPULATIONSIZE/2 ; indexSolutions++){
  populationArray[indexSolutions][0]=0;
  populationArray[indexSolutions][DIMENSION]=0;

  for(index=1;index<DIMENSION;index++){
    actualValue = 1+ floor (calculateRandom() * numberOfCities);
    for(;usedNumbers[indexSolutions][actualValue];){
    actualValue=(int) fmod(actualValue,numberOfCities);
      actualValue++;
    }
    usedNumbers[indexSolutions][actualValue]=1;
    populationArray[indexSolutions][index]=actualValue;
  }
    populationDistances[indexSolutions]=calculateDistance(populationArray[indexSolutions]);
    addArray(populationArray[indexSolutions],populationDistances[indexSolutions]);
}
}

void generateGreedyInitialSolution(){
  int index0=0,index,asignations,indexSolutions=POPULATIONSIZE/2;
  int usedNumbers[POPULATIONSIZE][DIMENSION]={0};
  for(indexSolutions; indexSolutions< POPULATIONSIZE ; indexSolutions++){
  populationArray[indexSolutions][0]=0;
  populationArray[indexSolutions][DIMENSION]=0;
  usedNumbers[indexSolutions][populationArray[indexSolutions][0]]=1;
  populationArray[indexSolutions][1]=1+floor (calculateRandom() * numberOfCities);
  populationDistances[indexSolutions]=distanceMatrix[0][populationArray[indexSolutions][1]];
  usedNumbers[indexSolutions][populationArray[indexSolutions][1]]=1;
  actualDistance = MAX_INT;
  for(asignations=1;asignations<numberOfCities;asignations++){
    for(index=1;index<=numberOfCities;index++){
      newDistance = distanceMatrix[populationArray[indexSolutions][asignations]][index];
      if(newDistance < actualDistance && usedNumbers[indexSolutions][index]==0){
        index0=index;
        actualDistance=newDistance;
      }
      }
    usedNumbers[indexSolutions][index0]=1;
    populationArray[indexSolutions][asignations+1]=index0;
    populationDistances[indexSolutions]+=actualDistance;
    actualDistance = MAX_INT;
  }
  populationDistances[indexSolutions]+=distanceMatrix[0][populationArray[indexSolutions][numberOfCities]];
  addArray(populationArray[indexSolutions], populationDistances[indexSolutions]);
}
}


int calculateDistanceOptimized(int * vector,int index0,int index1,int previousDistance){
  newDistance=previousDistance;


  newDistance-=distanceMatrix[vector[index0]][vector[index0-1]];
  newDistance-=distanceMatrix[vector[index0]][vector[index0+1]];
  newDistance-=distanceMatrix[vector[index1]][vector[index1-1]];
  newDistance-=distanceMatrix[vector[index1]][vector[index1+1]];

  vector[index1]=actualSolution[index0];
  vector[index0]=actualSolution[index1];


  newDistance+=distanceMatrix[vector[index0]][vector[index0-1]];
  newDistance+=distanceMatrix[vector[index0]][vector[index0+1]];
  newDistance+=distanceMatrix[vector[index1]][vector[index1-1]];
  newDistance+=distanceMatrix[vector[index1]][vector[index1+1]];

  vector[index0]=actualSolution[index0];
  vector[index1]=actualSolution[index1];
  return newDistance;
}

void mainLoop(){
  for(iterations=1;iterations<=MAX_ITERATIONS;iterations++){
    actualDistance=getBestthElementDistance(0);
    if(actualDistance<solDistance){
      solIterations=iterations-1;
      copyArray(solPath,getBestthElementArray(0),DIMENSION);
      solDistance=actualDistance;
    }
  binaryTournamentSelection();
  exchange();
  mutation();
  replacement();
}
}

void binaryTournamentSelection(){
  int i,rand01,rand02,minRand,maxRand;
  printf("\nITERACION: %d, SELECCION\n",iterations);
  for(i=0;i<(POPULATIONSIZE-2);i++){
    rand01= floor (calculateRandom() * POPULATIONSIZE);
    rand02= floor (calculateRandom() * POPULATIONSIZE);
    if  (populationDistances[rand01] <= populationDistances[rand02]) {
      exchangeCandidates[i]=rand01;
    }else{
      exchangeCandidates[i]=rand02;
    }
    // (populationDistances[rand01] <= populationDistances[rand02]) ? (exchangeCandidates[i]=rand01) : (exchangeCandidates[i]=rand02);
    printf("\tTORNEO %d: %d %d GANA %d\n",i,rand01,rand02,exchangeCandidates[i]);
  }
}

void exchange(){
  int i,rand01,minRand,maxRand,j,k=0,w=0;
  double aleatorio;
  printf("\nITERACION: %d, CRUCE \n",iterations);
  for(i=0;i<(POPULATIONSIZE-2);i+=2){
    aleatorio=calculateRandom();
    printf("\tCRUCE: (%d, %d) (ALEATORIO: %f)\n\t\tPADRE: = {FUNCION OBJETIVO (km): %d, ",i,i+1,aleatorio,populationDistances[exchangeCandidates[i]]);
    printArray(populationArray[exchangeCandidates[i]],DIMENSION);
    printf("}\n\t\tPADRE: = {FUNCION OBJETIVO (km): %d, ",populationDistances[exchangeCandidates[i+1]]);
    printArray(populationArray[exchangeCandidates[i+1]],DIMENSION);

    if(EXCHANGE_PROBABILITY>aleatorio){
      maxRand=floor(calculateRandom() * numberOfCities);
      rand01=floor(calculateRandom()*numberOfCities);
      printf("}\n\t\tCORTES: (%d, %d)\n",maxRand,rand01);
      (rand01 > maxRand) ? ((minRand=maxRand) & (maxRand=rand01)) : (minRand=rand01);
      /*
        Now the crossover is applied
      */
      for(j=minRand+1;j<=maxRand+1;j++){
        sons[i][j]=populationArray[exchangeCandidates[i]][j];
        usedIndexInExchange[i][sons[i][j]]=1;
        sons[i+1][j]=populationArray[exchangeCandidates[i+1]][j];
        usedIndexInExchange[i+1][sons[i+1][j]]=1;
      }
      for(j=0;j<numberOfCities;j++){
        (!usedIndexInExchange[i][populationArray[exchangeCandidates[i+1]][(j+maxRand+1)%numberOfCities+1]]) ? ((sons[i][(maxRand+k+1)%numberOfCities+1]=populationArray[exchangeCandidates[i+1]][(j+maxRand+1)%numberOfCities+1]) && (usedIndexInExchange[i][populationArray[exchangeCandidates[i+1]][(j+maxRand+1)%numberOfCities+1]]=1) && (k++)): i ;
        (!usedIndexInExchange[i+1][populationArray[exchangeCandidates[i]][(j+maxRand+1)%numberOfCities+1]]) ? ((sons[i+1][(maxRand+w+1)%numberOfCities+1]=populationArray[exchangeCandidates[i]][(j+maxRand+1)%numberOfCities+1]) && (usedIndexInExchange[i+1][populationArray[exchangeCandidates[i]][(j+maxRand+1)%numberOfCities+1]]=1) && (w++)): i ;
      }
      k=0;
      w=0;
      sonsDistance[i]=calculateDistance(sons[i]);
      sonsDistance[i+1]=calculateDistance(sons[i+1]);
      printf("\t\tHIJO: = {FUNCION OBJETIVO (km): %d, ",sonsDistance[i]);
      printArray(sons[i],DIMENSION);
      printf("}\n\t\tHIJO: = {FUNCION OBJETIVO (km): %d, ",sonsDistance[i+1]);
      printArray(sons[i+1],DIMENSION);
      printf("}\n\n");
  }else{
      sonsDistance[i]=populationDistances[i];
      sonsDistance[i+1]=populationDistances[i+1];
      copyArray(sons[i],populationArray[exchangeCandidates[i]],DIMENSION);
      copyArray(sons[i+1],populationArray[exchangeCandidates[i+1]],DIMENSION);
      printf("}\n\t\tNO SE CRUZA\n\n");
  }
    /*End of crossover*/
  }

}

void mutation(){
  int i,j,swapElement;
  double rand;
  copyArray(populationArray[0],getBestthElementArray(1),DIMENSION);
  copyArray(populationArray[1],getBestthElementArray(0),DIMENSION);
  populationDistances[0]=getBestthElementDistance(1);//calculateDistance(populationArray[0]);
  populationDistances[1]=getBestthElementDistance(0);//calculateDistance(populationArray[1]);
  deleteAllButTwo();
  printf("ITERACION: %d, MUTACION\n",iterations);
    for(i=0;i<(POPULATIONSIZE-2);i++){
      printf("\tINDIVIDUO %d\n\tRECORRIDO ANTES: ",i);
      printInlineArray(sons[i],DIMENSION);
      for(j=0;j<numberOfCities;j++){
        rand=calculateRandom();
        if(rand>0.01){
          printf("\n\t\tPOSICION: %d (ALEATORIO %6lf) NO MUTA",j,rand);
        }else{
          swapElement=(int)floor(calculateRandom()*numberOfCities);
          printf("\n\t\tPOSICION: %d (ALEATORIO %6lf) INTERCAMBIO CON: %d",j,rand,swapElement);
          swap(sons[i],j,swapElement);
        }
      }
      sonsDistance[i]=calculateDistance(sons[i]);
      addArrayFromPosition(sons[i],sonsDistance[i],2);
      printf("\n\tRECORRIDO DESPUES: ",i);
      printInlineArray(sons[i],DIMENSION);
      printf("\n\n");
    }
  substituteElement(populationArray[0],populationDistances[0],0);
  substituteElement(populationArray[1],populationDistances[1],1);
}

void replacement(){
  int i;
  printf("\nITERACION: %d, REEMPLAZO\n",iterations);
    for(i=0;i<countElements();i++){
    copyArray(usedIndexInExchange[i], auxiliarNullArray,DIMENSION);
    copyArray(populationArray[i],getArrayElement(i),DIMENSION);
    populationDistances[i]=getCostElement(i);
      printf("INDIVIDUO %d = {FUNCION OBJETIVO (km): %d, ",i,populationDistances[i]);
      printArray(populationArray[i],DIMENSION);
      printf("}\n");
    }
}


/*Auxiliar functions*/

void swap(int * vector,int index0,int index1){
  int tmp;
  tmp = vector[index1+1];
  vector[index1+1] = vector[index0+1];
  vector[index0+1]=tmp;
}

short isvalueinarray(int val, int *arr, int size){
    int i;
    for (i=0; i < size; i++) {
        if (arr[i] == val)
            return 1;
    }
    return 0;
}

void copyArray(int * hostArray,int * array,int size){
  int i=0;
  for(i=0;i<size;i++)
    hostArray[i]=array[i];
  hostArray[DIMENSION]=0;
}

float calculateRandom(){
  if(activatedRandoms<=0){
    srand(time(NULL)*rand());
    return ((float)rand())/RAND_MAX;
  }
  actualRandom++;
  return randoms[actualRandom];
}

void printMatrix(){
  int i,j;
  for (i=0;i<DIMENSION;i++) {
    for(j=0;j<i;j++){
    printf("%d ",**(distanceMatrix+i*j+j));
  }
    printf("\n");
  }
}

void printActualSolution(){
  int i;
  printf("\tRECORRIDO: ");
  for(i=1;i<=numberOfCities;i++)
    printf("%d ",actualSolution[i]);
  printf("\n");
}

void printArray(int * array,int size){
  int i;
  printf("RECORRIDO: ");
  for(i=1;i<  size;i++)
    printf("%d ",array[i]);
  // printf("\n");
}

void printInlineArray(int * array,int size){
  int i;
  for(i=1;i<  size;i++)
    printf("%d ",array[i]);
}

int calculateDistance(int * vector){
  /*Modificala para sumar en funcion da distancia previa*/
  int i=0,index01=0,index02=0;
  newDistance=0;
  for(i=0;i<DIMENSION;i++){
    index01=vector[i];
    index02=vector[i+1];
    newDistance+=distanceMatrix[index01][index02];
  }
  return newDistance;
}

void calculateInitialDistance(){
  int i=0,index01=0,index02=0;
  actualDistance=distanceMatrix[0][actualSolution[1]];
  for(i=1;i<=numberOfCities;i++){
    index01=actualSolution[i];
    index02=actualSolution[i+1];
    actualDistance+=distanceMatrix[index01][index02];
  }
  newDistance=actualDistance;
}
void initWithoutRandom(const char * path){
    openFile(path,distanceMatrix);
    numberOfCities=DIMENSION-1;
}

void initWithRandom(const char *path,const char * pathToRandom){
  openFile(path,distanceMatrix);
  numberOfCities=DIMENSION-1;
  randoms=openRandoms(pathToRandom);
  activatedRandoms=1;
}
