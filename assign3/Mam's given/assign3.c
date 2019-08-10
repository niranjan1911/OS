


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int **mat1, **mat2, **res;
int row1, row2, col1, col2;

typedef struct index
{
	int row;
	int col;
}index;

void* matmul(void* ind);
void print_mat(int, int, int**);

int main()
{
	pthread_t *threads;
	int check=0,i,j,count;
	index *ind;
	
	
	//TAKING INPUT NO. OF ROWS & COLS AND VALIDATING
	while(check==0)
	{
		printf("\nEnter the number of rows and columns in the first matrix:");
		scanf("%d %d",&row1,&col1);
	
		printf("\nEnter the number of rows and columns in the second matrix:");
		scanf("%d %d",&row2,&col2);
	
		if(col1==row2)
			check=1;
		else
			printf("\nInvalid size of matrix!\nPlease enter again......\n");
	}
	
	
	//DYNAMICALLY ALLOCATING MEMORY TO MATRICES
	mat1 = (int**) malloc(row1*sizeof(int*));
	for(i=0;i<row1;i++)
		mat1[i] = (int*) malloc(col1*sizeof(int));
	
	mat2 = (int**) malloc(row2*sizeof(int*));
	for(i=0;i<row2;i++)
		mat2[i] = (int*) malloc(col2*sizeof(int));
	
	res = (int**) malloc(row1*sizeof(int*));
	for(i=0;i<row1;i++)
		res[i] = (int*) malloc(col2*sizeof(int));
	
	
	//TAKING MATRIX INPUT
	printf("\nEnter the elements of mat1:");
	for(i=0;i<row1;i++)
		for(j=0;j<col1;j++)
			scanf("%d",&mat1[i][j]);
			
	printf("\nEnter the elements of mat2:");
	for(i=0;i<row2;i++)
		for(j=0;j<col2;j++)
			scanf("%d",&mat2[i][j]);
	
	
	//CALCULATING MULTIPLICATION		
	count=0;
	ind = (index*) malloc(row1*col2*sizeof(index));	
	threads = (pthread_t*) malloc(row1*col2*sizeof(pthread_t));	
	for(i=0;i<row1;i++)
	{
		for(j=0;j<col2;j++)
		{
			ind[count].row=i;
			ind[count].col=j;
			check=pthread_create(&(threads[count]),NULL,matmul,(void*)&ind[count]);
			count++;
			if(check!=0)
				printf("\nError in thread creation!\n");
		}
		
	}
	
	
	//JOINIG THREADS
	for(i=0;i<count;i++)
	{
		check=pthread_join(threads[i],NULL);
		if(check!=0)
				printf("\nError in thread joining!\n");
	}
	//PRINTING RESULT
	printf("\n\tMat1:\n");
	print_mat(row1,col1,mat1);
	
	printf("\n\tMat2:\n");
	print_mat(row2,col2,mat2);
	
	printf("\n\tResult:\n");
	print_mat(row1,col2,res);
	
return 0;
}


void print_mat(int row, int col, int **mat)
{
	int i,j;
	
	for(i=0;i<row;i++)
	{
		printf("\n\t");
		for(j=0;j<col;j++)
			printf("  %d",mat[i][j]);
	}
	printf("\n");
}


void* matmul(void* ind)
{
	index indx;
	int r,c,i,sum=0;
	indx=*(index*)ind;
	r=indx.row;
	c=indx.col;
	
	for(i=0;i<col1;i++)
		sum += (mat1[r][i] * mat2[i][c]);  
	
	res[r][c] = sum;
	pthread_exit("work done");
}


