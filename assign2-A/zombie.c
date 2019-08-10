#include<stdio.h>
#include<stdlib.h>

void main()
{
	int pid;
	pid=fork();
	if(pid==0)
	{
	   printf("\nChild process is running\n");
	   printf("\nchild id is:%d\n",getpid());
	   printf("\nold parent id is:%d\n",getppid());
	   sleep(1);
	   printf("\nnew parent id is:%d\n",getppid());
	   
	}
	else 
	{
	    printf("\nparent process is running\n");
	    sleep(10);
	    printf("\nparent id is:%d\n",getpid());
	    wait(NULL);
	}
	
}

