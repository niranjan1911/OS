#include<stdio.h>
#include<stdlib.h>

void binary(int arr[],int l,int h,int key)
{

  int mid=(l+h)/2;
  if(key==arr[mid])
  {
    printf("found at %d location..",mid+1);
  }
  else if(key<arr[mid])
  { 
    binary(arr,l,mid-1,key);
  }
  else if(key>arr[mid])
  {
    binary(arr,mid+1,h,key);
  }
  else
  {
    printf("Element not found..");
  }
}
int main(int argc,char *argv[])
{
  int arr[20],n,key;
  n=argc;
  for(int i=0;i<n;i++)
  {
    arr[i]=atoi(argv[i]);
  }
  printf("array in 2nd:");
   for(int i=0;i<n;i++)
  {
    printf("%d ",arr[i]);
  }
  printf("Enter the key:");
  scanf("%d",&key);
  binary(arr,0,n-1,key);
 return 0;
}
