#include<stdio.h>
#include<stdlib.h>

void main()
{
	int pid;
	pid=fork();
	if(pid==0)
	{
	   printf("\nChild process is running");
	   printf("\nchild id is:%d",getpid());
	   printf("\told parent id is:%d",getppid());
	   sleep(5);
	   printf("\tnew parent id is:%d",getppid());
	   
	}
	else 
	{
	    printf("\nparent process is running");
	    sleep(1);
	    printf("\nparent id is:%d",getpid());
	   
	}
	
}

