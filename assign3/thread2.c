#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>	
#include <string.h>
#include <sys/types.h>
#include<pthread.h>

void *tADD(void *arg);
void *tSUB(void *arg);
void *tMUL(void *arg);
void *tDIV(void *arg);
int main()
{
     int a[2],i;
     int *temp;  	
     int res;
     pthread_t tid_add;
     void *tres;
     printf("\nInside main thread");
     printf("\nEnter the two number:");
     scanf("%d %d",&a[0],&a[1]);
    //calling thread for addition
     res=pthread_create(&tid_add,NULL,tADD,(void *)a);
     if(res!=0)
     {
     	printf("\nError in creating main thread");
     	exit(EXIT_FAILURE);
     }
     
     printf("\nJoining ADD child thread");
     res=pthread_join(tid_add,&tres);
      if(res!=0)
     {
     	printf("\nError in joining child thread");
     	exit(EXIT_FAILURE);
     }
     
     printf("\nBack to the main thread");     
     printf("\nChild sent -%d- message...",(int *)tres);
     
     //calling thread for substraction
     res=pthread_create(&tid_add,NULL,tSUB,(void *)a);
     if(res!=0)
     {
     	printf("\nError in creating main thread");
     	exit(EXIT_FAILURE);
     }
     
     printf("\nJoining SUB child thread");
     res=pthread_join(tid_add,&tres);
      if(res!=0)
     {
     	printf("\nError in joining child thread");
     	exit(EXIT_FAILURE);
     }
     
     printf("\nBack to the main thread");     
     printf("\nChild sent -%d- message...",(int *)tres);
     
     //calling thread for Multiplication
     res=pthread_create(&tid_add,NULL,tMUL,(void *)a);
     if(res!=0)
     {
     	printf("\nError in creating main thread");
     	exit(EXIT_FAILURE);
     }
     
     printf("\nJoining MUL child thread");
     res=pthread_join(tid_add,&tres);
      if(res!=0)
     {
     	printf("\nError in joining child thread");
     	exit(EXIT_FAILURE);
     }
     
     printf("\nBack to the main thread");     
     printf("\nChild sent -%d- message...",(int *)tres);
     
     //calling thread for division
     res=pthread_create(&tid_add,NULL,tDIV,(void *)a);
     if(res!=0)
     {
     	printf("\nError in creating main thread");
     	exit(EXIT_FAILURE);
     }
     
     printf("\nJoining DIV child thread");
     res=pthread_join(tid_add,&tres);
      if(res!=0)
     {
     	printf("\nError in joining child thread");
     	exit(EXIT_FAILURE);
     }
     
     printf("\nBack to the main thread");     
     printf("\nChild sent -%d- message...",(float *)tres);
     
     exit(EXIT_SUCCESS);
}
void *tADD(void* arg) 
{
        int add,*a;
        a=(int *)malloc(2*sizeof(int));
        a=(int *)arg;
	printf("\nInside child thread");
	printf("\nArgument: %d %d ",a[0],a[1]);
	add=a[0]+a[1];
	printf("\nAdd:%d",add);
	pthread_exit((void *)add);
}
void *tSUB(void* arg) 
{
        int sub,*a;
        a=(int *)malloc(2*sizeof(int));
        a=(int *)arg;
	printf("\nInside child thread");
	printf("\nArgument: %d %d ",a[0],a[1]);
	sub=a[0]-a[1];
	printf("\nSub:%d",sub);
	pthread_exit((void *)sub);
}
void *tMUL(void* arg) 
{
        int mul,*a;
        a=(int *)malloc(2*sizeof(int));
        char str[10];
        a=(int *)arg;
	printf("\nInside child thread");
	printf("\nArgument: %d %d ",a[0],a[1]);
	mul=a[0]*a[1];
	printf("\nMul:%d",mul);
	pthread_exit((void *)mul);
}
void *tDIV(void* arg) 
{
        int div;
        int *a;
        a=(int *)malloc(2*sizeof(int));
        char str[10];
        a=(int *)arg;
	printf("\nInside child thread");
	printf("\nArgument: %d %d ",a[0],a[1]);
	div=a[0]/a[1];
	printf("\nDiv:%d",div);
	pthread_exit((void *)div);
}
