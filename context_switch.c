#define _GNU_SOURCE
#include <stdio.h>	
#include <stdint.h>	
#include <stdlib.h>	
#include <time.h>	
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h> 
#include <sched.h>
#include <pthread.h>
#include <math.h>
#include <signal.h>



#define BILLION 1000000000
#define STRSIZE 100
#define MAX 2

int main(void) {
	
	//Initializing and creating Variables
	long int sys_time;

	int sec;
	int nsec;
	int tubo1[2];
	int tubo2[2];
	int parent = getpid();

	struct timespec start, end;
	
	//Creating Pipes
	pipe(tubo1);
	pipe(tubo2);
	
	//Strings to be transferred
	char datadad[STRSIZE] = "I was sent from father ";
	char datachild[STRSIZE] = "I was sent from child ";
	
	cpu_set_t  mask;
    CPU_ZERO(&mask);
    unsigned int lenght = sizeof(mask);
    CPU_SET(0, &mask);

	// USE 0 for READ
	// USE 1 for WRITE
	if ( (sched_setaffinity(0, lenght, &mask) ) < 1) {
		
		fork();
		clock_gettime(CLOCK_MONOTONIC, &start);
		for (int i=0;i<MAX;i++){

			//Parent Process
			if (getpid() == parent) {
				char resultoftubo2[STRSIZE];
				close(tubo1[0]);
				write(tubo1[1], datadad, strlen(datadad)+1);
				close(tubo1[1]);
				wait(NULL);
				close(tubo2[1]);
				read(tubo2[0], resultoftubo2, STRSIZE);
				//printf("The following message was received from CHILD = %s\n", resultoftubo2);
				close(tubo2[0]);

			//Child Process
			} else {
				close(tubo1[1]);
				char resultoftubo[STRSIZE];
			 	read(tubo1[0], resultoftubo, STRSIZE);
			 	close(tubo1[0]);
			 	close(tubo2[0]);
				write(tubo2[1], datachild, strlen(datachild)+1);
				close(tubo2[1]);
				//printf("The following message was received from FATHER =  %s\n", resultoftubo);
			}
		}
		clock_gettime(CLOCK_MONOTONIC, &end);
		
		//Calculating time it took to make a context switch
		sec = end.tv_sec - start.tv_sec;
		nsec = end.tv_nsec - start.tv_nsec;

		if ((sec) == 0){ sys_time =  nsec/MAX;} else { sys_time = (BILLION * sec + nsec) / MAX;}
		sys_time = sys_time / MAX;

	}
	printf("The average time it took for a context switch was %ld nanoseconds per call.\n", sys_time);
}