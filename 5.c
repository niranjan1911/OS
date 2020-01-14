#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>

void *writer(void *arg);
void *reader(void *arg);

int p,c,in=0,out=0,size,buff[20],readcount=0;

sem_t m;
pthread_mutex_t mutex;

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
  printf("Enter the number of writers:");
  scanf("%d",&p);
  
  printf("Enter the number of readers:");
  scanf("%d",&c);
  
  printf("Enter the size of buffer:");
  scanf("%d",&size);
  
  pthread_t tidp[p],tidc[c];
  
  for(int i=0;i<size;i++)
       buff[i]=0;
       
   
   sem_init(&m,0,1);
    //sem_init(&mutex,0,1);
   
   
   for(int i=0;i<p;i++)
      pthread_create(&tidp[i],NULL,writer,(i+1));
      
   for(int i=0;i<c;i++)
      pthread_create(&tidc[i],NULL,reader,(i+1));
   
   for(int i=0;i<p;i++)
      pthread_join(tidp[i],NULL);
      
   for(int i=0;i<c;i++)
      pthread_join(tidc[i],NULL);
      
  return 0;
}
void *writer(void *arg)
{
  int n=(int *)arg;
  while(1)
  {
          sleep(rand()%5);
	  sem_wait(&m);
	  
	  //sem_wait(&mutex);
	  pthread_mutex_lock(&mutex);
	  
	  printf("\nWriter %d is writing...",n);
	  write();
	  disp();
	  sleep(rand()%5);
	  printf("\nWriter %d is exited...",n);
	  
	  pthread_mutex_unlock(&mutex);
	  //sem_post(&mutex);
	  sem_post(&m);
  }
  
}
void *reader(void *arg)
{
 
    int n=(int *)arg;
    while(1)
    {
            sleep(rand()%10);
	    //sem_wait(&mutex);
	    pthread_mutex_lock(&mutex);
	    
	    readcount++;
	    if(readcount==1)
	       sem_wait(&m);
	    
	    pthread_mutex_unlock(&mutex);
	    //sem_post(&mutex);
	    
	    printf("\nReader %d is reading...",n);
	    read();
	    disp();
	    sleep(rand()%5);
	    printf("\nReader %d is exited...",n);
	    
	    //sem_wait(&mutex);
	    pthread_mutex_lock(&mutex);
	    
	    readcount--;
	    if(readcount==0)
	       sem_post(&m);
	    
	    pthread_mutex_unlock(&mutex);
	    //sem_post(&mutex);
    }
    
}
