#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


void *demo(void *arg);
struct node
{
 int x,y;
};

void accept(int *mat,int r,int c)
{
  for(int i=0;i<r;i++)
  {
    for(int j=0;j<c;j++)
    {
      scanf("%d",(mat+ i*c +j));
    }
  }
}
void display(int *mat,int r,int c)
{
  for(int i=0;i<r;i++)
  {
    printf("|"); 
    for(int j=0;j<c;j++)
    {
      printf("%d ",*(mat+ i*c +j));
    }
    printf("|\n");
  }
}

int main()
{
  int *a,*b,*res,r1,c1,r2,c2,flag=0;
  pthread_t tid;
  void *tres;	
  while(flag==0)
  {
         
	  printf("Enter the dimenstion of matrix 1:");
	  scanf("%d %d",&r1,&c1);
	 
	  printf("Enter the dimenstion of matrix 2:");
	  scanf("%d %d",&r2,&c2);
	  
	  if(c1!=r2)
	  {
	    printf("\nThe number of column of first matrix and number of rows of second matrix must same...\nEnter again:");
	    flag=0;
	  }
	  else
	  {
	    flag=1;
	  }
   }
  
  a=malloc(r1*c1*sizeof(int));
  b=malloc(r2*c2*sizeof(int));
  res=malloc(r1*c2*sizeof(int));
  
  printf("Enter the matrix 1:\n");
  accept(a,r1,c1);
  
  
  printf("Enter the matrix 2:\n");
  accept(b,r2,c2);

  
  printf("\nMatrix 1:\n");
  display(a,r1,c1);
  printf("\nMatrix 2:\n");
  display(b,r2,c2);
  
  for(int i=0;i<r1;i++)
  {
    for(int j=0;j<c2;j++)
    {
      *(res+ i*c2 +j)=0;
      for(int k=0;k<c1;k++)
      {
           struct node *s;
           s->x=*(a+ i*c1 +k);
           s->y=*(b+ k*c2 +j);
           
           printf("\nPassed:%d %d",s->x,s->y);
           pthread_create(&tid,NULL,demo,s);
           
           pthread_join(tid,&tres);
           
           //printf("\nAdd:%d",*(res+ i*c2 +j));
           *(res+ i*c2 +j) += *(int *)tres;
            printf("	Upper result:%d",*(res+ i*c2 +j));
      }
    }
  }
   printf("\nResultant matrix:\n");
   display(res,r1,c2);
  return 0;
}
void *demo(void *arg)
{
  struct node *data=arg;
  int *mul;
  mul=malloc(sizeof(int));
  
  *mul=data->x * data->y;
  printf("	Result in thread:%d",*mul);
  pthread_exit((void *)mul);
}
