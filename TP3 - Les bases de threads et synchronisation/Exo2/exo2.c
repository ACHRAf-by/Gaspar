#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>		//pour utiliser le rand() => man 3 rand
#include <time.h>		//pour utiliser le time()
#include <unistd.h>		//usleep
#include <semaphore.h>

#define P(x) sem_wait(x)
#define V(x) sem_post(x)

sem_t sem1, sem2;

int mon_rand(int a, int b);

void* thread_1();
void* thread_2();

int main(void)
{
	pthread_t mes_threads[2];
	
	sem_init(&sem1,0,0); //on peut décider de la valeur initiale pour les sem
	sem_init(&sem2,0,0); //contrairement aux mutex
	
	srand(time(NULL));
	
	pthread_create(&mes_threads[0],NULL,thread_1,NULL);
	pthread_create(&mes_threads[1],NULL,thread_2,NULL);
	
	pthread_join(mes_threads[0],NULL);
	pthread_join(mes_threads[1],NULL);
	
	printf("\n");
	return 0;
}

int mon_rand(int a, int b)
{
	//on suppose que b>a !
	return ( rand()%(b-a) ) + a;
}

void* thread_1()
{
	usleep(mon_rand(10000,1000000));
	printf("je ");
	V(&sem1);
	P(&sem2);
	usleep(mon_rand(10000,1000000));
	printf("mes ");
	V(&sem1);
	
	return NULL;
}

void* thread_2()
{
	P(&sem1);
	usleep(mon_rand(10000,1000000));
	printf("synchronise ");
	V(&sem2);
	P(&sem1);
	usleep(mon_rand(10000,1000000));
	printf("threads ");
	
	return NULL;
}

