#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>		//pour utiliser le rand() => man 3 rand
#include <time.h>		//pour utiliser le time()
#include <unistd.h>		//usleep

pthread_mutex_t m1;
pthread_mutex_t m2;

int mon_rand(int a, int b);

void* thread_1();
void* thread_2();

int main(void)
{
	pthread_t mes_threads[2];
	
	srand(time(NULL));
	
	//il faut bloquer le premier thread dès le départ
	//les mutex sont unlock au démarrage !
	pthread_mutex_lock(&m1);
	pthread_mutex_lock(&m2);
		
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
	pthread_mutex_unlock(&m1);
	pthread_mutex_lock(&m2);
	usleep(mon_rand(10000,1000000));
	printf("mes ");
	pthread_mutex_unlock(&m1);
	
	return NULL;
}

void* thread_2()
{
	pthread_mutex_lock(&m1);
	usleep(mon_rand(10000,1000000));
	printf("synchronise ");
	pthread_mutex_unlock(&m2);
	pthread_mutex_lock(&m1);
	usleep(mon_rand(10000,1000000));
	printf("threads ");
	
	return NULL;
}

