#include<stdio.h>

int main()
{
  for(int i=0;i<10;i++) 
  {
    int n=(rand() %3) ;
    printf("%d\n",n);
  }
  return 0;
}
