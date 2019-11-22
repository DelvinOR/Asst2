#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "multitest.h"

//int SpookySearch(int*, int, int, int);

typedef struct thread_arguments{
	int startIndex;
	int endIndex;
	int grpSize;
	//int* result;
}t_args;


const char * mode = "thread\0";
int*numList;
int sizeOfArray;
//int startIndex;
//int endIndex;
int searchTarget;

void * threadHelper(void * args){
    int * arguments = (int *) args;
    //printf("DEBUG: ARG0 Grab\n");
    int startIndex = arguments[0];
    //printf("DEBUG: ARG1 Grab\n");
    int endIndex = arguments[1];
    //printf("DEBUG: ARG2 Grab\n");
    int groupSize = arguments[2];
    //int * result = arguments[3];
    int * result = malloc(sizeof(int));
    if (result == NULL){
	printf("DEBUG: result is null. malloc failed!\n");
    }
    *result = 255;
    int i;
    int found = 255;
    for(i = startIndex; i < endIndex && i < sizeOfArray; i++){
	//printf("DEBUG: i: %d sI: %d eI: %d sA: %d\n", i, startIndex, endIndex, sizeOfArray);
	//printf("DEBUG: a[%d]: %d\n", i, numList[i]);
        if(numList[i] == searchTarget){
            found = i%groupSize;
	    *result = found;
        }
    }
    //printf("DEBUG: thread exit\n");
    if (result == NULL)
	printf("DEBUG: NULL RETVAL: %d\n", i);
    pthread_exit(result);
}

int SpookySearch(int * arr, int arrSize, int target, int groupSize){
    numList = arr;
    sizeOfArray = arrSize;
    searchTarget = target;

    if (arrSize < 1){
	printf("ERROR: arrSize too small!\n");
	return -1;
    }
    if (groupSize > 250){
	groupSize = 250;
        printf("Warning: groupSize too large! Defaulting to 250.\n");
    }
    int ulimit = 2000;
    int i;
    int numOfThreads = (int) ceil((double)arrSize/groupSize);
    pthread_t threads[numOfThreads];


    // Inside of this loop, we will create all of the threads and use our helper function.
    // We pass a struct filled with the relevant search info to each thread
    for(i = 0; i < numOfThreads && i < ulimit; i++){
	t_args * new = malloc(sizeof(t_args));
	new->startIndex  = groupSize * i;
        new->endIndex = groupSize * (i + 1);
	new->grpSize = groupSize;
	//new->result = malloc(sizeof(int *));
	//printf("DEBUG: Thread created!\n");
        pthread_create(&threads[i], NULL, threadHelper, new);
    }

    // Waiting for the threads to finish and checking each thread's exit status
    void* threadReturn = NULL;
    int res;
    int index = -1;
    //printf("DEBUG: Returning threads\n");
    for(i = 0; i < numOfThreads; i++){
	//printf("DEBUG: At join\n");
        pthread_join(threads[i], &threadReturn);
	//printf("DEBUG: at thread return val\n");
	//printf("DEBUG: ptr: %x\n", (int*)threadReturn);
        res = *(int *) threadReturn;
	//printf("DEBUG: Passed thread ret\n");
        if(res != 255){
	    //printf("Target found!\n");
            index = ((i*groupSize) + res);
        }
    }
    //if (index == -1)
    //	printf("Target not found!\n");
    //else
	//printf("Target found!\n");
    return index;
}
