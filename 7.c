#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>


int main()
{ 
  int pd[2],pd1[2];
  char file1[20],buff[20],content[100],buffer[100];
  
  pipe(pd);
  pipe(pd1);
  
  pid_t pid;
  pid=fork();
  
			  if(pid==0)
			  {
			    //child
			    close(pd[1]);
			    read(pd[0],buff,sizeof(buff));
			    printf("\nFile name:%s",buff);
			    
			    
			    int f;
			    f=open(buff,O_RDWR);
			    read(f,content,sizeof(content));
			    
			    printf("\nContents in child:%s",content);
				   close(pd1[0]);
				   write(pd1[1],content,sizeof(content));
				   close(pd1[1]); 
			    
			    
			    close(pd[0]);
			 
			  }
			  else if(pid>0)
			  { 
			    //parent
			   printf("Enter the file name:");
  			   scanf("%s",file1);
			   
			   close(pd[0]);
			   write(pd[1],file1,sizeof(file1));
			   close(pd[1]);
			  
			   close(pd1[1]);
			   read(pd1[0],buffer,sizeof(buffer));
			   
			   printf("\nContents of file:%s",buffer);
			   close(pd1[0]);
			  }
			  else
			  {
			   printf("Error in fork");
			  }
			
 
  return 0;
}
