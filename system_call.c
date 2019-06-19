#include <stdio.h>	
#include <stdint.h>	
#include <stdlib.h>	
#include <time.h>	
#include <unistd.h>

#define MAX 1000000
#define BILLION 1000000000


int main(void) {

	//Initializing and creating Variables
	long int sys_time;
	long int for_time;

	int sec;
	int nsec;
	
	struct timespec start, end;

	//clock_t begin = clock();
	clock_gettime(CLOCK_MONOTONIC, &start);
	
	for (int i=0;i<MAX;i++){
	  	read(0, 0, 0);
	}

	clock_gettime(CLOCK_MONOTONIC, &end);

	sec = end.tv_sec - start.tv_sec;
	nsec = end.tv_nsec - start.tv_nsec;

	if ((sec) == 0){ sys_time =  nsec/MAX;} else { sys_time = (BILLION * sec + nsec) / MAX;}
	
	//Debugging
	//printf("%ld\n", end.tv_sec);
	//printf("%ld\n", end.tv_nsec);
	//printf("%ld\n", start.tv_sec);
	//printf("%ld\n", start.tv_nsec);
	//printf("%d\n", sec);
	//printf("%d\n", nsec);
	//printf("Read took: %ld nanoseconds\n", sys_time);

	clock_gettime(CLOCK_MONOTONIC, &start);	

	//Empty for loop for timing purposes
	for (int i=0;i<MAX;i++){}

	clock_gettime(CLOCK_MONOTONIC, &end);

	sec = end.tv_sec - start.tv_sec;
	nsec = end.tv_nsec - start.tv_nsec;

	if ((sec) == 0){ for_time =  nsec/MAX; } else {	for_time = (BILLION * sec + nsec) / MAX;}

	sys_time = sys_time - for_time;
	printf("The average time that %d system calls took was %ld nanoseconds per call.\n", MAX, sys_time);

	exit(0);
}