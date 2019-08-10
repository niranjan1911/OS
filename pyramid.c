#include<stdio.h>

int main()
{
     int i,j,n,a=1,k,temp;
     scanf("%d",&n);
     temp=n;
     for(i=1;i<=n;i++)	
     {  
	      for(k=i;k<temp;k++)
	      {
			printf(" ");
	       
	       }
	       for(j=0;j<a;j++)
	       {
			 printf("*");
		 
	       }
		 
	       a=a+2;
	       printf("\n");
     }   
}
