#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>

void *producer(void *arg);
void *consumer(void *arg);

int p,c,in=0,out=0,size,buff[20];

sem_t full,empty;
pthread_mutex_t m;

void write()
{
  int n = rand() % 10;
  if(n==0)
  {
   n=11;
  }
  buff[in]=n;
  in=(in+1)%size;
}

void read()
{
  buff[out]=0;
  out=(out+1)%size;
}

void disp()
{
   for(int i=0;i<size;i++)
   {
       printf(" %d ",buff[i]);
    }
}

int main()
{
  printf("Enter the number of producers:");
  scanf("%d",&p);
  
  printf("Enter the number of consumers:");
  scanf("%d",&c);
  
  printf("Enter the size of buffer:");
  scanf("%d",&size);
  
  pthread_t tidp[p],tidc[c];
  
  for(int i=0;i<size;i++)
       buff[i]=0;
       
   sem_init(&full,0,0);
   sem_init(&empty,0,size);
   
   for(int i=0;i<p;i++)
      pthread_create(&tidp[i],NULL,producer,(i+1));
      
   for(int i=0;i<c;i++)
      pthread_create(&tidc[i],NULL,consumer,(i+1));
   
   for(int i=0;i<p;i++)
      pthread_join(tidp[i],NULL);
      
   for(int i=0;i<c;i++)
      pthread_join(tidc[i],NULL);
      
  return 0;
}
void *producer(void *arg)
{
    int n = (int *)arg;
    printf("producer %d created..\n",n);
    int err=0;
    while(1)
    {
      sleep(rand()%5);
      sem_wait(&empty);
      pthread_mutex_lock(&m);
      
      write();
      printf("\t\tProducer %d has written:\t",n);
      disp();
      printf("\n");
    
      pthread_mutex_unlock(&m);
      sem_post(&full);
      
    }
}
void *consumer(void *arg)
{
    int n = (int *)arg;
    printf("consumer %d created..\n",n);
    int err=0;
    while(1)
    {
      sleep(rand()%5);
      sem_wait(&full);
      pthread_mutex_lock(&m);
      
      read();
      printf("\t\tconsumer %d has read:\t",n);
      disp();
      printf("\n");
    
      pthread_mutex_unlock(&m);
      sem_post(&empty);
      
    }
}
