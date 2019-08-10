#include <stdio.h>
#include <stdlib.h>	
#include<pthread.h>
#define max 10


void accept(int mat1[max][max],int r1,int c1)
{
	int i,j;
	for(i=0;i<r1;i++)
	{
	    for(j=0;j<c1;j++)
	    {
	        printf("\nEnter [%d][%d]:",i,j);
	        scanf("%d",&mat1[i][j]);
	    }	
	}
}
void display(int mat[max][max],int r,int c)
{
	int i,j;
	for(i=0;i<r;i++)
	{
	  for(j=0;j<c;j++)
	  {
	    printf("%d\t",mat[i][j]);
	  }
	  printf("\n");
	}
}

int main()
{
     
     pthread_t tid;
     void *tres;
     int r1,c1,r2,c2,flag=0;
     while(flag==0)
     {
	     printf("\nEnter the dimention of matrx 1:");
	     scanf("%d %d",&r1,&c1);
	     printf("\nEnter the dimention of matrx 2:");
	     scanf("%d %d",&r2,&c2);
	     if(c1==r2)
	     {
	       flag=1;
	     }
	     else
	     {
	     	printf("\nThe number of column of first matrix and number of rows of second matrix must same...\nEnter again:");
	     	flag=0;
	     }
	     
     }
     int mat1[max][max],mat2[max][max];
     
     printf("\nEnter the elements of matrix 1:");
     accept(mat1,r1,c1);
     
     printf("\nEnter the elements of matrix 2:");
     accept(mat2,r2,c2);
     
     printf("\nMatrix 1:\n");
     display(mat1,r1,c1);
     
     printf("\nMatrix 2:\n");
     display(mat2,r2,c2);
     
    
     return 0; 	
     
 }    
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
    
