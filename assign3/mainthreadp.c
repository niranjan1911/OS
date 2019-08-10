#include <stdio.h>
#include <stdlib.h>	
#include<pthread.h>
#define max 10

void *tdemo(void *arg);

struct node 
{
	int x,y;
};
void accept(int *mat1,int r1,int c1)
{
	int i,j;
	for(i=0;i<r1;i++)
	{
	    for(j=0;j<c1;j++)
	    {
	        printf("\nEnter [%d][%d]:",i,j);
	        scanf("%d",(mat1 + i*c1 +j));
	    }	
	}
}
void display(int *mat,int r,int c)
{
	int i,j;
	for(i=0;i<r;i++)
	{
	  for(j=0;j<c;j++)
	  {
	    printf("%d\t",*(mat + i*c +j));
	  }
	  printf("\n");
	}
}

int main()
{
     
     pthread_t tid;
     void *tres;
     int r1,c1,r2,c2,flag=0,check;
     int i,j,k;
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
     int *a=(int *)malloc(r1*c1*sizeof(int));
     int *b=(int *)malloc(r2*c2*sizeof(int));
     int *res=(int *)malloc(r1*c2*sizeof(int));
     
     printf("\nEnter the elements of matrix 1:");
     accept(a,r1,c1);
     
     printf("\nEnter the elements of matrix 2:");
     accept(b,r2,c2);
     
     printf("\nMatrix 1:\n");
     display(a,r1,c1);
     
     printf("\nMatrix 2:\n");
     display(b,r2,c2);
     
      for(i=0;i<r1;i++)
      {
	       for(j=0;j<c2;j++)
	       {
			*(res + i*c2 +j) = 0;
			for(k=0;k<c1;k++)
			{
				   //struct node *s=(struct node*)malloc(sizeof(struct));
				   struct node s;
				   s.x=*(a + i*c1 +k);
				   s.y=*(b + k*c2 +j);
				   
				   check=pthread_create(&tid,NULL,tdemo,(void *)s);
				   if(check!=0)
				   {
				     	printf("\nError in creating main thread");
				     	exit(EXIT_FAILURE);
				   }
				   
				   check=pthread_join(tid,&tres);
	     			   if(check!=0)
				   {
				     	printf("\nError in creating main thread");
				     	exit(EXIT_FAILURE);
				   }
    			           
				   *(res + i*c2 +j) +=	(int *)tres;
			 }
		}
	}
      printf("\nResultant matrix:\n");
      display(res,r1,c2);
     return 0; 	
     
 }    
 void * tdemo(void* arg) 
{
	struct node data=(struct node*)arg;
	int n,product;
	//product=malloc(sizeof(int));
	
	product=data.x * data.y; 
	printf("\nArguments:%d %d",data.x,data.y);
	//printf("\nIn mul :: i: %d  j: %d  k :  %d  product : %d  \n",(data->i),(data->j),(data->k),*product );
	pthread_exit((void *)product);
}    
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
    
