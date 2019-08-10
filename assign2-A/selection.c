#include<stdio.h>
#include<stdlib.h>

void main()
{

	int arr[5],min,temp,i,j;
	printf("\nEnter the five element:\n");
	for(i=0;i<5;i++)
	{
	   printf("%dth:",i+1);
           scanf("%d",&arr[i]);
	}
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
	printf("sorted array :\n");
		for(i=0;i<5;i++)
		{
		   printf("%d\t",arr[i]);
		   
		}
}
