#include <stdio.h>
#include <stdlib.h>
#include "multitest.h"

int main(int argc, char**argv){
    int arrSize = 0;
    printf("Enter a random number\n");
    scanf("%d",&arrSize);

    int* myList = (int*)malloc(sizeof(int) * arrSize);

    int i;
    for(i = 0; i < arrSize; i++){
        myList[i] = i;
    }
    // Array completely filled in

    // Now we have to randomize the elements in the array
    int ind = 0;
    int j;
    for(j = 0; j < arrSize; j++){
        ind = (rand() % (arrSize + 1));
        int temp = myList[j];
        myList[j] = myList[ind];
        myList[ind] = temp;
    }

    





}