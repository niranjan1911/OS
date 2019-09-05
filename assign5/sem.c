



//Reader writer problem





#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

void *writer(void *arg);
void *reader(void *arg);

 int p,c,in=0,out=0,buff[20],size,res,readcount=0;
 void *tres_p,*tres_c;

 sem_t wrt;
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
     printf("Enter the numbers of writers:\n");
     scanf("%d",&p);
     
     printf("Enter the numbers of readers:\n");
     scanf("%d",&c);
     
     printf("Enter the Size of buffer:\n");
     scanf("%d",&size);
     
     int prod[p],cons[c];
     pthread_t tid_p[p],tid_c[c];
     
     
     
     for(int i=0;i<size;i++)
       buff[i]=0;
     
    
     
     sem_init(&wrt,0,1);
     
     
     for(int i=0;i<p;i++)
     {
        res=pthread_create(&tid_p[i],NULL,writer,(i+1));
        if(res!=0)
        {
		printf("\nError in creating %d writer",prod[i]);
     		exit(EXIT_FAILURE);
        }
      }
      
     for(int i=0;i<c;i++)
     {
        res=pthread_create(&tid_c[i],NULL,reader,(i+1));
        if(res!=0)
        {
		printf("\nError in creating %d reader",cons[i]);
     		exit(EXIT_FAILURE);
        }
      }
      
     for(int i=0;i<p;i++)
     {  
        res=pthread_join(tid_p[i],tres_p);
        if(res!=0)
        {
		printf("\nError in joining writer");
     		exit(EXIT_FAILURE);
        }
      }
      
     for(int i=0;i<c;i++)
     {
        res=pthread_join(tid_c[i],tres_c);
        if(res!=0)
        {
		printf("\nError in joining reader");
     		exit(EXIT_FAILURE);
        }
     }
     
     return 0;	
}

void *writer(void* arg) 
{

        int i=(int *)arg;
        printf("\nwriter %d created",i);
        int err=0;
        while(1)
        {
            int n=rand() % 5;
            sleep(n);
            
	    sem_wait(&wrt);
	    
	    //err=pthread_mutex_lock(&mutex);
	    //if(err!=0)
       	    //{
		//printf("\nError in locking mutex");
            //}
            	
            write();
            printf("\n\t\twriter %d has written:   ",i);    
            disp();
            
            //err=pthread_mutex_unlock(&mutex);
	    //if(err!=0)
       	    //{
	//	printf("\nError in Unlocking mutex");
          //  }
            sem_post(&wrt);	
        }
	
}

void *reader(void* arg) 
{
        int i=(int *)arg;
        printf("\nreader %d created",i);
	int err=0;
        while(1)
        {
            int n=rand() % 5;
            sleep(n);
             	     // Reader wants to enter the critical section
	    err=pthread_mutex_lock(&mutex);
	    if(err!=0)
       	    {
		printf("\nError in locking mutex");
            }
             // The number of readers has now increased by 1
            readcount++;
            // there is atleast one reader in the critical section
            // this ensure no writer can enter if there is even one reader
   	    // thus we give preference to readers here
            if(readcount==1)	
            {
               sem_wait(&wrt);
            }
             // other readers can enter while this current reader is inside 
             // the critical section
            err=pthread_mutex_unlock(&mutex);
	    if(err!=0)
       	    {
		printf("\nError in Unlocking mutex");
            }
	    // current reader performs reading here	
            read();
            printf("\n\t\t   reader %d has read:   ",i) ;  
            disp();
            // a reader wants to leave
            err=pthread_mutex_lock(&mutex); 
	    if(err!=0)
       	    {
		printf("\nError in locking mutex");
            }
            readcount--;
             // that is, no reader is left in the critical section,
            if(readcount==0)	
            {
               sem_post(&wrt);// writers can enter
            }
            // reader leaves
            err=pthread_mutex_unlock(&mutex);
	    if(err!=0)
       	    {
		printf("\nError in Unlocking mutex");
            }
 	
        }
      
}



