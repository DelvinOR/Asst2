#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "multitest.h"



int A(int* array){
	return Search(array, 10000, 923, 250);
}

int B(int* array){
	return Search(array, 10000, 923, 100);
}

int C(int* array){
	return Search(array, 10000, 923, 50);
}

int D(int* array){
	return Search(array, 10000, 923, 20);
}

int E(int* array){
	return Search(array, 10000, 923, 10);
}

int F(int* array){
	return Search(array, 1000, 923, 250);
}

int G(int* array){
	return Search(array, 1000, 923, 100);
}

int H(int* array){
	return Search(array, 1000, 923, 50);
}

int I(int* array){
	return Search(array, 1000, 923, 20);
}

int J(int* array){
	return Search(array, 1000, 923, 10);
}

int K(int* array){
	return Search(array, 100, 923, 100);
}

int L(int* array){
	return Search(array, 100, 923, 50);
}

int M(int* array){
	return Search(array, 100, 923, 20);
}

int N(int* array){
	return Search(array, 100, 923, 10);
}

int main(int argc, char**argv){
    printf("Running in %s mode.\n", mode);


	int arrSize = 10000;
    int* myList = (int*)malloc(sizeof(int) * arrSize);
   	int i;
   	 //printf("DEBUG: Filling array\n");
    for(i = 0; i < arrSize; i++){
     	myList[i] = i;
    }
    // Array completely filled in
    // Now we have to randomize the elements in the array
    int index1 = 0;
    int index2 = 0;
    for(i = 0; i < arrSize; i++){
       	index1 = rand()%arrSize;
		index2 = rand()%arrSize;
        int temp = myList[index1];
        myList[index1] = myList[index2];
        myList[index2] = temp;
    }
    //elements randomized
	//run tests
	//timer
    struct timeval start, end;
    long times[10000];
	int asz[14] = {10000, 10000, 10000, 10000, 10000, 1000, 1000, 1000, 1000, 1000, 100, 100, 100, 100};
	int gsz[14] = {250, 100, 50, 20, 10, 250, 100, 50, 20, 10, 100, 50, 20, 10};
	int (*fp[])(int *) = {A, B, C, D, E, F, G, H, I, J, K, L, M, N};
	int T = 0;
    for(T = 0; T < 14; T++){
		
		if (asz[T] != arrSize){
			arrSize = asz[T];
			free(myList);
    		myList = (int*)malloc(sizeof(int) * arrSize);
   			 //printf("DEBUG: Filling array\n");
    		for(i = 0; i < arrSize; i++){
       			myList[i] = i;
    		}
   	 		// Array completely filled in
   	 		// Now we have to randomize the elements in the array
    		index1 = 0;
    		index2 = 0;
    		for(i = 0; i < arrSize; i++){
        		index1 = rand()%arrSize;
				index2 = rand()%arrSize;
        		int temp = myList[index1];
        		myList[index1] = myList[index2];
        		myList[index2] = temp;
			}
    	}

		
		char c = 65;
    	printf("Beginning Test %c: Array Size: %d Group Size: %d [x1000]\n", c+T, asz[T], gsz[T]);
    	int j = 0;
   		for(j = 0; j < 1000; j++){
			printf("Iteration: %d\r", j+1);
			index1 = rand()%arrSize;
	
			gettimeofday(&start, NULL);
			index2 = fp[T](myList);
			gettimeofday(&end, NULL);

			long elapsedtimeu = end.tv_usec - start.tv_usec;
      		long elapsedtimes = end.tv_sec - start.tv_sec;
      		long total = elapsedtimeu + elapsedtimes*1000000;
			if (total < 0)
				//printf("DEBUG:neg val! u:%ld s:%ld\n", elapsedtimeu, elapsedtimes);
			times[j] = total;
			int temp = myList[index2];
			myList[index2] = myList[index1];
			myList[index1] = temp;
	//printf("\r");
	//sleep(0.5);
    	}
        
   		printf("\nTest %c complete!\n", c+T);
    	long min = 10000000000000000;
    	long max = 0;
   		long long total = 0;
		double stdDev[1000];
    	for(j=0; j < 1000; j++){
			if (times[j] > max)
	    		max = times[j];
			if (times[j] < min)
	    		min = times[j];
			total += times[j];
			stdDev[j] = (double)times[j];
    	}
		long avg = total/j;
		double stdD = 0;
		for(j=0; j < 1000; j++){
			stdDev[j] = pow((stdDev[j] - (double)avg), 2);
			stdD += stdDev[j];
		}
		stdD = sqrt(stdD/1000);
    	printf("Times(usec): Total: %lld Avg: %ld StdDev: %f Min: %ld Max: %ld\n", total, avg, stdD, min, max);
	}


    return 1;
}
