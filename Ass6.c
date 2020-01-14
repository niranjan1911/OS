#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>


#define N 5

#define THINKING 1
#define HUNGRY 2
#define EATING 3

#define LEFT (no+4)%N
#define RIGHT (no+1)%N

sem_t mutex;
sem_t sem[N];

int phil[N]={0,1,2,3,4};

int state[N];


void *phil_func(void*);

void eat(int);
void test(int);

void take_fork(int);
void put_fork(int);


//---------------------------------------------------------------------------------------------------------------------------------------

void *phil_func(void *no)
{
	int i;
	i=*(int*)no;
	
	sleep(1);	
	take_fork(i);
	eat(i);
	
	sleep(1);
	put_fork(i);
}

//---------------------------------------------------------------------------------------------------------------------------------------

void eat(int no)
{
	printf("\nPhilosopher %d takes fork :- %d and %d",no+1,LEFT+1,no+1);
	printf("\nPhilosopher %d is eating.....!!!",no+1);
}

//---------------------------------------------------------------------------------------------------------------------------------------

void test(int no)
{
	if(state[no]==HUNGRY && state[LEFT]!=EATING && state[RIGHT]!=EATING)
	{
		state[no]=EATING;
		
		sleep(2);
		sem_post(&sem[no]);
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------

void take_fork(int no)
{
	sem_wait(&mutex);
	state[no]=HUNGRY;
	
	printf("\nPhilosopher %d is Hungry...!!!",no+1);
	test(no);
	
	sem_post(&mutex);
	sem_wait(&sem[no]);
	sleep(2);
}

//---------------------------------------------------------------------------------------------------------------------------------------

void put_fork(int no)
{
	sem_wait(&mutex);
	state[no]=THINKING;
	
	printf("\nPhilosopher %d putting fork....!!! Down---> %d and %d",no+1,LEFT+1,no+1);
	printf("\nPhilosopher %d is Thinking....!!!",no+1);

	test(LEFT);
	test(RIGHT);
	
	sem_post(&mutex);
}

//---------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	int i;
	
	pthread_t th[N];
	
	sem_init(&mutex,0,1);
	
	for(i=0;i<N;i++)
	{
		sem_init(&sem[i],0,0);
	}	
	
	for(i=0;i<N;i++)
	{
		pthread_create(&th[i],NULL,phil_func,&phil[i]);	
		printf("\nPhilosopher %d is thinking....!!!",i+1);
	}
	
	for(i=0;i<N;i++)
	{
		pthread_join(th[i],NULL);
	}
	
	
	printf("\n");
	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------
