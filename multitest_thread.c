#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "multitest.h"

int threadSpookySearch(int*, int, int);

int threadCounter = 0;

int*numList;
int sizeOfArray;
int startIndex;
int endIndex;
int searchTarget;

void * threadHelper(void * val){
    threadCounter++;
    // 0 false
    // 1 true
    int * found = (int *) val;
    
    int i;
    for(i = startIndex; i < endIndex && i < sizeOfArray; i++){
        if(numList[i] == searchTarget){
            found[0] = 1;
        }
    }

    pthread_exit(found);
}

int threadSpookySearch(int * arr, int arrSize, int target){
    numList = arr;
    sizeOfArray = arrSize;
    startIndex = 0;
    endIndex = 250;
    searchTarget = target;

    int ulimit = 2000;
    int i;
    int numOfThreads = ceil((double)arrSize/250);
    pthread_t threads[numOfThreads];

    //First we let the main thread search for the target in the first 250 elements of the list
    for(i = 0; i < 250 && i < arrSize; i++){
        if(arr[i] == target){
            return 1;
        }
    }

    // Inside of this loop, we will create all of the threads and use our helper function.
    // Does not make sense to pass variables on to the create thread function so what we will do is
    // set gloabal variables for the array, starting index, ending, index, and search target.
    int n = 0;
    for(i = 1; i < numOfThreads && i < ulimit; i++){
        startIndex  = 250* i;
        endIndex = 250 *(i + 1);
        pthread_create(&threads[i], NULL, threadHelper, &n);
    }

    // Waiting for the threads to finish and checking each thread's exit status
    void* threadReturn;
    int* res;
    for(i = 0; i < threadCounter; i++){
        pthread_join(threads[i], &threadReturn);
        res = (int *) threadReturn;
        if(res[0] == 1){
            return 1;
        }
    }

    return EXIT_SUCCESS;
}