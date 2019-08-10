#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#define L 10
 
struct v 
{ 
	int i;  //row 
    int j;  //column
	int k; 
}; 
void *mul(void *structure); 
void Accept(int A[][L],int R1 ,int C1)
{
	int i,j;
	for(i=0;i<R1;i++) 
	{ 
		for(j=0;j<C1;j++) 
		{ 
			scanf("%d",&A[i][j]); 
		} 
	}
}

void Display(int A[][L],int r ,int c)
{
	int i,j;
	for(i=0;i<r;i++) 
	{ 
		printf("\n"); 
		for(j=0;j<c;j++) 
			 printf("%d\t",A[i][j]); 
	} 
	printf("\n");
}

int main() 
{ 
	int A[L][L],B[L][L],C[L][L]; 
	int R1,C1,R2,C2;
	int k,i,n,j,sum=0; 
	printf("\nEnter the size of first matrix\n"); 
	printf("\tRow : "); 
	scanf("%d",&R1); 
	printf("\tColumn :"); 
	scanf("%d",&C1); 
	printf("\nEnter the size of second matrix\n"); 
	printf("\tRow :"); 
	scanf("%d",&R2); 
	printf("\tColumn :"); 
	scanf("%d",&C2); 
	printf("Enter the elements of first matrix: \n"); 
	Accept(A,R1,C1); 	
	 	
	printf("Enter the elements of second matrix: \n");
    Accept(B,R2,C2);
	 
	printf("\nFirst Matrix\n"); 
	Display(A,R1,C1);
	
	printf("\nSecond Matrix\n"); 
	Display(B,R2,C2);
	
	void * thread_result;
	for(i=0;i<R1;i++)
	{
		for(j=0;j<C2;j++)
		{
			C[i][j]=0;
			for(n=0;n<C1;n++)
			{
				struct v *data=(struct v*)malloc(sizeof(struct v));
				data->i=A[i][n];
				data->j=B[n][j];
				data->k=n;
				pthread_t tid;
				
				pthread_create(&tid,NULL,mul,data);
				
				pthread_join(tid,&thread_result);
				
				printf("product %d \n",*((int *)thread_result));
				C[i][j]+=*((int *)thread_result);
				
			}
		}
	}
	  
	printf("\nAfter multiplication using pthreads : \n"); 
	Display(C,R1,C2);
	return 0; 
} 
 
void * mul(void * structure ) 
{
	struct v * data=structure;
	int n,*product;
	product=malloc(sizeof(int));
	
	*product=data->i * data->j; 
	printf("\nIn mul :: i: %d  j: %d  k :  %d  product : %d  \n",(data->i),(data->j),(data->k),*product );
	pthread_exit((void *)product);
}
