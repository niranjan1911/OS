#include<stdio.h>
#include<stdlib.h>

void main()
{
	int pid,temp,i,j,min;
	int arr[5];
	printf("\nEnter the five element:\n");
	for(i=0;i<5;i++)
	{
	   printf("%dth:",i+1);
           scanf("%d",&arr[i]);
	}
	
	printf("\nFork time\n");
	pid=fork();
	if(pid==0)
	{
	   printf("\nChild process is running\n");
	   //sorting
	        for(i=0;i<5;i++)
		{
		  for(j=i;j<5;j++)
		  {
		     if(arr[i]>arr[j])
		     {
		       temp=arr[j];
		       arr[j]=arr[i];
		       arr[i]=temp;
		      }
		   }
		}
		printf("sorted array in child:\n");
		for(i=0;i<5;i++)
		{
		   printf("%d\t",arr[i]);
		   
		}
	   printf("\nchild id is:%d\n",getpid());
	   printf("\nold parent id is:%d\n",getppid());
	   sleep(5);
	   printf("\nnew parent id is:%d\n",getppid());
	   
	}
	else 
	{
	    printf("\nparent process is running\n");
	    //sorting
	        for(i=0;i<5;i++)
		{
		  min=arr[i];
		  for(j=i+1;j<5;j++)
		   {
		     if(min>arr[j])
		     {
		       temp=arr[j];
		       arr[j]=min;
		       min=temp;
		      }
		   }
		   arr[i]=min;
		}
		printf("sorted array in parent:\n");
		for(i=0;i<5;i++)
		{
		   printf("%d\t",arr[i]);
		   
		}
	    sleep(1);
	    printf("\nparent id is:%d\n",getpid());
	   
	}
	
}

