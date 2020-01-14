#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

int main()
{
  int fd1,fd2;
  char buff[100];
  int space=0,words=0,chars=0,arr[3];
  
  fd1 = mkfifo("first",0777);
  fd2 = mkfifo("second",0777);
  
  fd1 = open("first",O_RDONLY);
  read(fd1,buff,sizeof(buff));
  printf("\nRecieved:%s",buff);
  close(fd1);
  
  for(int i=0;i<(strlen(buff));i++)
  {
     if(buff[i]==' ')
     {
       space++;
     }
  }
  words=space+1;
  chars=strlen(buff)-space;
  arr[0]=space;arr[1]=words;arr[2]=chars;
  
  fd2 = open("second",O_WRONLY);
  write(fd2,arr,sizeof(arr));
  close(fd2);
  return 0;
}
