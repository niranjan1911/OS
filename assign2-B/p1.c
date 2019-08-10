#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>	
#include <string.h>
#include <sys/types.h>

int main(int argc,char *argv[])
{
	int pid,n,j,temp;
	int desc[2];
	
	printf("\nEnter size of array:");
	scanf("%d",&n);
  	
  	char *arr1[n] ,str[sizeof(int)];
        int arr[n], i;
        
        printf("\nEnter Elements:-");
        for(i=0;i<n;i++)
        {
             scanf("%d",&arr[i]);
        }
       //pipe descriptor
       pipe(desc);
        
        //start
	if(fork()==0)
	{
	   printf("Child is running\n");
	   
	   //reading from pipe
	   close(desc[1]);
	   read(desc[0],arr,sizeof(arr));
	   
	   
             for(i=0;i<n;i++)
             {
                sprintf(str,"%d",arr[i]);
                arr1[i] = malloc(sizeof(str));
                strcpy(arr1[i],str);
       	     } 
             arr1[i] = '\0';
          close(desc[0]);
          
	   execv("./p2",arr1);
	   printf("Sorry can't execute\n");
	}
	else 
	{
	    printf("parent is running\n");
	     for(i=0;i<n;i++)
	     {
	       for(j=0;j<n-i-1;j++)
	       {
		 if(arr[j]>arr[j+1])
	          {
	             temp=arr[j];
	             arr[j]=arr[j+1];
	             arr[j+1]=temp;
	          }
	       }
	     }
	     
	    //writing in pipe
	    
	    close(desc[0]);
	    write(desc[1],arr,sizeof(arr));
	    close(desc[1]);
		
	    wait(NULL);
	    printf("\nParent Executed..");
	}
        return 0;	
}



