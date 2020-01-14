#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>

int main()
{
  int fd1,fd2,arr[3];
  char buff[100];
  
  printf("Enter the sentence:");
  gets(buff);
  
  fd1 = mkfifo("first",0777);
  fd2 = mkfifo("second",0777);
  
  fd1 = open("first",O_WRONLY);
  write(fd1,buff,sizeof(buff));
  close(fd1);
  
  fd2 = open("second",O_RDONLY);
  read(fd2,arr,sizeof(arr));
  
  printf("\nWords:%d",arr[1]);
  printf("\nCharacters:%d",arr[2]);
  printf("\nSpaces:%d",arr[0]);
  
  close(fd2);
  return 0;
}
