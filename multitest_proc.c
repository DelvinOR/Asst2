#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "multitest.h"
    
int procSpookySearch(int*,int, int);
int seachList(int*, int, int, int, int);

int procSpookySearch(int* arr,int arrSize, int target){// arrSize is going to help to determin how many processes we will need including parent process
    int ulimit = 2000;
    int i;
    int numProc = ceil(((double)arrSize/250));

    int firstCheck = searchList(arr, 0, 250, arrSize, target);
    if(firstCheck == 1){
        return 1; //1 for found, 0 for not found *Need to confirm*
    }

    int id;
    int res;
    // Child processes will now begin here and we start with i = 1 because we allow the parent process to search the array first
    for(i = 1; i < numProc && i < ulimit ; i++){
        id = fork();
        if(id == 0){ // We are in the child process
            res = searchList(arr,250*i,250*(i+1), arrSize, target);
            if(res == 1){
                exit(1);
            }else{
                exit(0);
            }
        }
    }

    int status;
    int found = 0;
    while(numProc > 0){
        wait(&status);
        // Status contatins the exit status
        if(WIFEXITED(status)){
            found = WEXITSTATUS(status);
            if(found == 1){
                break;
            }
        }
        --numProc;
    }

    return found;
}

int searchList(int* arr, int startIndex, int endIndex, int arrSize, int target){
    int i;
    for(i = startIndex; i < endIndex && i < arrSize; i++){
        if(arr[i] == target){
            return 1;
        }
    }

    return 0;
}