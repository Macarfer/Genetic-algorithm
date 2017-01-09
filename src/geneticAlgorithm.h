#include "fileManager.h"
#include <math.h>
#include <time.h>
#include "orderedLinkedList.h"


#define MAX_ITERATIONS 1000
#define POPULATIONSIZE DIMENSION*DIMENSION
#define PERCENTAGE DIMENSION*0.2
#define EXCHANGE_PROBABILITY 0.9
#define PEN 1.01

#define MAX_INT 2147483647
#define BEST_SOLUTIONS_SIZE 9
#define MU 0.01
#define PHI 0.5

void initWithoutRandom(const char * path);
void initWithRandom(const char * path,const char * path2);
void generateInitialSolution();
void generateGreedyInitialSolution();
void run();
