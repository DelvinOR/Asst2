#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "multitest.h"
 
int searchList(int*,int, int, int, int, int);

const char * mode = "procedure\0";
int SpookySearch(int* arr,int arrSize, int target, int groupSize){// arrSize is going to help to determin how many processes we will need including parent process
    int ulimit = 2000;
    int i;
    if (arrSize < 1){
	printf("ERROR: arrSize too small!\n");
	return -1;
    }
    if (groupSize > 250){
	groupSize = 250;
        printf("Warning: groupSize too large! Defaulting to 250.\n");
    }
    int numProc = (int) ceil(((double)arrSize/groupSize));

    int id;
    int ids[numProc];
    int res;
    // Child processes will now begin here
    for(i = 0; i < numProc && i < ulimit ; i++){
        id = fork();
        if(id == 0){ // We are in the child process
            res = searchList(arr,groupSize*i,groupSize*(i+1), arrSize, target, groupSize);
            if(res != 255){
                exit(res);//found target
            }else{
                exit(255);//did not find target
            }
        }
	else{
		ids[i] = id;
	}
    }

    int status;
    int index = -1;
    unsigned char found = 0;
    i = 0;
    while(i < numProc){
        waitpid(ids[i], &status, 0);
        // Status contatins the exit status
        if(WIFEXITED(status)){
            found = WEXITSTATUS(status);//get lower 8 bits from child
            if(found != 0xFF){//255 means child did not find target
		        index = i*groupSize + (int)found;//target was found
            }
        }
        i++;
    }
    //if (index == -1)
    //	printf("Target not found!\n");
    //else
	//printf("Target found!\n");
    return index;
}

int searchList(int* arr, int startIndex, int endIndex, int arrSize, int target, int groupSize){
    int i;
    for(i = startIndex; i < endIndex && i < arrSize; i++){
        if(arr[i] == target){
            return i%groupSize;//returns index of target if found
        }
    }

    return 255;//returns 255 if not found
}
