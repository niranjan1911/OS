#include<stdio.h>

int main()
{
     int i,j,n,a=1,k,temp;
     scanf("%d",&n);
     temp=n;
     char c=64;
     for(i=1;i<=n;i++)	
     {  
	      for(k=i;k<temp;k++)
	      {
			printf(" ");
	       
	       }
	       for(j=0;j<a;j++)
	       {
	         c=c+1;
			
		 if(c>90)
		 {
		    c -= 26;
		 }
		  printf("%c",c);
	       }
		c=64; 
	       a=a+2;
	       printf("\n");
     }   
}
