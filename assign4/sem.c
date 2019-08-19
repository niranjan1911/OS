#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

void *producer(void *arg);
void *consumer(void *arg);

 int p,c,in=0,out=0,buff[20],size,res;
 void *tres_p,*tres_c;

 sem_t empty,full;
 pthread_mutex_t mutex;
     
void write()
{
   int n=rand() % 10;
   if(n==0)
   {
     n=11;
   }
   buff[in]=n;
   in = (in + 1) % size;
}
void read()
{
   buff[out]=0;
   out = (out + 1) % size;
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
     printf("Enter the numbers of Producers:\n");
     scanf("%d",&p);
     
     printf("Enter the numbers of Consumers:\n");
     scanf("%d",&c);
     
     printf("Enter the Size of buffer:\n");
     scanf("%d",&size);
     
     int prod[p],cons[c];
     pthread_t tid_p[p],tid_c[c];
     
     
     
     for(int i=0;i<size;i++)
       buff[i]=0;
     
    
     
     sem_init(&full,0,0);
     sem_init(&empty,0,size);
     
     for(int i=0;i<p;i++)
     {
        res=pthread_create(&tid_p[i],NULL,producer,(i+1));
        if(res!=0)
        {
		printf("\nError in creating %d producer",prod[i]);
     		exit(EXIT_FAILURE);
        }
      }
      
     for(int i=0;i<c;i++)
     {
        res=pthread_create(&tid_c[i],NULL,consumer,(i+1));
        if(res!=0)
        {
		printf("\nError in creating %d consumer",cons[i]);
     		exit(EXIT_FAILURE);
        }
      }
      
     for(int i=0;i<p;i++)
     {  
        res=pthread_join(tid_p[i],tres_p);
        if(res!=0)
        {
		printf("\nError in joining producer");
     		exit(EXIT_FAILURE);
        }
      }
      
     for(int i=0;i<c;i++)
     {
        res=pthread_join(tid_c[i],tres_c);
        if(res!=0)
        {
		printf("\nError in joining consumer");
     		exit(EXIT_FAILURE);
        }
     }
     
     return 0;	
}

void *producer(void* arg) 
{
        int i=(int *)arg;
        printf("\nProducer %d created",i);
        int err=0;
        while(1)
        {
            int n=rand() % 5;
            sleep(n);
            
	    sem_wait(&empty);
	    
	    err=pthread_mutex_lock(&mutex);
	    if(err!=0)
       	    {
		printf("\nError in locking mutex");
            }
            	
            write();
            printf("\n\t\tProducer %d has written:   ",i);    
            disp();
            
            err=pthread_mutex_unlock(&mutex);
	    if(err!=0)
       	    {
		printf("\nError in Unlocking mutex");
            }
            sem_post(&full);	
        }
	
}

void *consumer(void* arg) 
{
        int i=(int *)arg;
        printf("\nconsumer %d created",i);
	int err=0;
        while(1)
        {
           
            int n=rand() % 5;
            sleep(n);
            
	    sem_wait(&full);
	    
	    err=pthread_mutex_lock(&mutex);
	    if(err!=0)
       	    {
		printf("\nError in locking mutex");
            }
            	
            read();
            printf("\n\t\t   Consumer %d has read:   ",i) ;  
            disp();
            
            err=pthread_mutex_unlock(&mutex);
	    if(err!=0)
       	    {
		printf("\nError in Unlocking mutex");
            }
            sem_post(&empty);	
        }
      
}
