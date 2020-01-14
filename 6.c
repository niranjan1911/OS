#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>

#define n 5

#define thinking 1
#define hungry 2
#define eating 3

#define left (no+4)%n
#define right (no+1)%n

sem_t var;
sem_t sem[n];
int  state[n],phil[n]={1,2,3,4,5};

void putfork(int no)
{
  sem_wait(&var);
  state[no]=thinking;
  printf("\nphilosopher %d puts the fork:",no+1);
  printf("\putting the Fork: %d %d",left+1,no+1);
  
  test(left);
  test(right);
  sem_post(&var);
  
}
 
void eat(int no)
{
  printf("\nPhilosopher %d is eating...",no+1);
  printf("\neat with Fork: %d %d",left+1,no+1);
}

void test(int no)
{
  if(state[no]==hungry && state[left]!=eating && state[right]!=eating)
  {
    state[no]=eating;
    
    sem_post(&sem[no]);
  }
}

void getfork(int no)
{
 
  sem_wait(&var);
  state[no]=hungry;
  
  test(no);
  sem_post(&var);
  sleep(2);
  sem_wait(&sem[no]);
 
}

void *philosopher(void * no)
{
 while(1){
  int i; 
  i=(int *)no;
   
  sleep(1);
  getfork(i);
  eat(i);
  
  sleep(1);
  putfork(i);
  }
}

int main()
{
  pthread_t p[n];
  sem_init(&var,0,1);
  
  for(int i=0;i<n;i++)
  { 
     sem_init(&sem[i],0,0);
  }
  for(int i=0;i<n;i++)
  { 
     pthread_create(&p[i],NULL,philosopher,i);
     printf("\nPhilosopher %d is thinking....!!!",i+1);
  }
  for(int i=0;i<n;i++)
  { 
     pthread_join(p[i],NULL);
  }
  return 0;
}
