#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<sys/types.h>

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
  
  char *str[n],c[sizeof(int)];
  printf("Enter the array elemnt:");
  accept(arr,n);
  
  printf("\n");
 
  display(arr,n);
   
  int pd[2]; 
  pipe(pd);   
  
	 	 	 int i;
			  pid=fork();
			  if(pid==0)
			  {
			    //child
			    close(pd[1]);
			    read(pd[0],arr,sizeof(arr));
			    for(i=0;i<n;i++)
			    {
			      sprintf(c,"%d",arr[i]);
			      str[i] = malloc(sizeof(c));
			      strcpy(str[i],c);
			    }
			    str[i]='\0';
			    
			    execv("2b2",str);
			    printf("Cant execute...!");
			    close(pd[1]);
			    
			  }
			  else if(pid>0)
			  { 
			    //parent
			   sort(arr,n);
			   display(arr,n);
			   
			   close(pd[0]);
			   write(pd[1],arr,sizeof(arr));
			   close(pd[1]);
			 
			   wait(NULL);
			   printf("\nParent completed");
			  }
			  else
			  {
			   printf("Error in fork");
			  }
			
  return 0;
}
