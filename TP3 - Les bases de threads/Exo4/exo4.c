/**
 * TP3 - Partie 4
 * Gestion de parallélisme
 * Ecriture / Lecture d'un Tampon partagé utilisant des threads. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

// Macros :
// Semaphores : Waiting/Unlocking
#define P(x) sem_wait(x)
#define V(x) sem_post(x)
// Array size : 
#define N 6

// Libre/Ocuupe
sem_t Lib, Occ ;

// Our 2 threads : Producer(writer)/Consumer(reader)
void* thread_writer(void* arg);
void* thread_reader(void* arg);

// shared buffer 
char shared__Array[N];

// Read\write indexes
int write_index = 0;
int read_index = 0;



int main(void){
	
	pthread_t writer;
	pthread_t reader;

	// Init des semaphores 
	sem_init(&Lib,0,N);
	sem_init(&Occ,0,0);

	// Creation des threads 
	pthread_create(&writer, NULL, thread_writer, NULL);
	pthread_create(&reader, NULL, thread_reader, NULL);

	// Execution des threads
	pthread_join(writer, NULL);
	pthread_join(reader, NULL);

	return 0;
}


void ecrire_tampon(char data){
	
	shared__Array[write_index] = data;
	printf("Write %c at index %d \n", data, write_index);
	write_index = write_index + 1;
	
}


void lecture_tampon(){
	
	printf("Read %c at index %d \n", shared__Array[read_index], read_index);
	shared__Array[read_index] = -1;	
	read_index = read_index + 1;
}


void* thread_writer(void* arg){
	int count = 0;
	char data = 'F';
	while(count < N) {
		P(&Lib);
		ecrire_tampon(data);
		sleep(1);
	        data++;
		V(&Occ);
		count ++;
	}

	return NULL;
}

void* thread_reader(void* arg){
	int count;
	while(count < N) {
		P(&Occ);
		lecture_tampon();
		sleep(1);
		V(&Lib);
		count ++;
	}

	return NULL;
}

