/**
 * TP3 - partie 3
 * Implémentation d'une barriére en utilisant les semaphores V et P au lieu de la struct et les fonctions 
 * prédefinies des la biblio <pthread> ( pthread_barrier_t )
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>

// Semaphores : waiting / Unlocking 
#define P(x) sem_wait(x)
#define V(x) sem_post(x)

// Number of threads
#define N 9

sem_t mutex, barrier;
int count = 0;

void *thread_i(void* arg);
void * barrier_thread(void * arg);


int main(void){

	printf("The number of threads to execute is : %d + The barrier thread \n", N);
	pthread_t mes_threads[N];
	pthread_t pid_barrier ;
	
	sem_init(&mutex,0,1);
        sem_init(&barrier,0,0);
	srand(time(NULL));
	
	if(pthread_create(&pid_barrier, NULL, &barrier_thread, NULL) != 0){
		perror("Failed to create barrier thread \n");
	}

	for(int i = 0 ; i < N; i++){
		if(pthread_create(mes_threads + i, NULL, &thread_i, NULL) !=0){
			perror("Failed to create threads");
			return 1;
		}
		count = count + 1;
	}

	pthread_join(pid_barrier, NULL);

	for( int j = 0; j < N; j++){
	       	if(pthread_join(mes_threads[j], NULL) != 0){
                          return 2;
		}
	}

	return 0;
}

// Using the random generator function from part 1.2 to sleep calls.
int mon_rand(int a, int b)
{
	//on suppose que b>a !
	return ( rand()%(b-a) ) + a;
}


// Every thread does this routine 
void* thread_i(void * arg){
	
	usleep(mon_rand(10000,1000000));
	 
	printf("Point achieved \n");	
	

	return NULL;
}


// The ONE barrier thread  
void* barrier_thread(void * arg){
	
	usleep(mon_rand(10000, 1000000));
	printf("Barrier achieved, Waiting ... \n");
	sleep(1);
	P(&mutex);

	if(count == N) {
		V(&barrier);
		printf("Barrier passed, We continue \n");
	}
        V(&barrier);
	P(&barrier);

	return NULL;
}






