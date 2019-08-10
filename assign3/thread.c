#include <stdio.h>
#include <stdlib.h>	
#include<pthread.h>

void *tdemo(void *arg);
int main()
{
     char *msg="first thread argument";
     int res;
     pthread_t tid;
     void *tres;
     printf("\nInside main thread");
     
     res=pthread_create(&tid,NULL,tdemo,(void *)msg);
     if(res!=0)
     {
     	printf("\nError in creating main thread");
     	exit(EXIT_FAILURE);
     }
     
     printf("\nJoining child thread");
     res=pthread_join(tid,&tres);
     
      if(res!=0)
     {
     	printf("\nError in joining child thread");
     	exit(EXIT_FAILURE);
     }
     
     printf("\nBack to the main thread");     
     printf("\nChild sent -%s- message...",(char *)tres);
     
     exit(EXIT_SUCCESS);
}
void *tdemo(void *arg) 
{
	printf("\nInside child thread");
	printf("\nArgument: %s ",(char *)arg);
	pthread_exit("Exiting from child");
}

