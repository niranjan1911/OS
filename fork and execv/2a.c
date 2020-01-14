#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void accept(int arr[],int n)
{
   for(int i=0;i<n;i++)
   {
     scanf("%d",&arr[i]);
   }
}

void display(int arr[],int n)
{
   for(int i=0;i<n;i++)
   {
     printf("%d ",arr[i]);
   }
   printf("\n");
}

void sort(int arr[],int n)
{
  for(int i=0;i<n-1;i++)
  {
    for(int j=0;j<n-1-i;j++)
    {
      if(arr[j]>arr[j+1])
      {
        int temp=arr[j];
        arr[j]=arr[j+1];
        arr[j+1]=temp;
      } 
    }
  }
}
int main()
{
 
  int arr[10],n,ch;
  pid_t pid;
  
  printf("Enter the number of element:");
  scanf("%d",&n);
  
  printf("Enter the array elemnt:");
  accept(arr,n);
  
  printf("\n");
 
  display(arr,n);
  
  while(1)
  {
	  printf("\n1.zombie\n2.orphan\n3.exit");
	  scanf("%d",&ch);
	 
	  switch(ch)
	  {	  
		  case 1:
			  pid=fork();
			  if(pid==0)
			  {
			    //child
			   
			    printf("\nchild id is:%d",getpid());
			    printf("\nParent of child is :%d\n",getppid());
			    sleep(1);
			  }
			  else if(pid>0)
			  { 
			    //parent
			    printf("Sotred array in parent:\n");
			    sort(arr,n);
			    display(arr,n);
			   
			    sleep(1);
			    printf("\nParent id is:%d",getpid()); 
			    system("ps -elf | grep a.out");
			    
			    wait(NULL);
			    
			    printf("\n");
			    system("ps -elf | grep a.out");
			    
			  }
			  else
			  {
			   printf("Error in fork");
			  }
			  exit(0);
			  break;
		  case 2:
			  pid=fork();
			  if(pid==0)
			  {
			    //child
			    
			    printf("\nchild id is:%d",getpid());
			    printf("\nParent of child is :%d",getppid());
			    sleep(5);
			    printf("\nThe new Parent of child is :%d",getppid());
			    system("ps -elf | grep a.out");
			    
			  }
			  else if(pid>0)
			  { 
			    //parent
			     printf("Sotred array in parent:\n");
			    sort(arr,n);
			    display(arr,n);
			   
			   sleep(1);
			    printf("\nParent id is:%d",getpid()); 
			    
			    
			    
			  }
			  else
			  {
			   printf("Error in fork");
			  }
			  break;
			  exit(0);
		  case 3:
		         return 0;
		  default:
		         printf("You have entered wrong choice...");
          }
     }
  return 0;
}
