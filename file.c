#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>

struct node 
{
  int roll;
  char name[20];
  float marks;
};

int main()
{ 
  int ch,id,fd,flag=0;
  int key;
  	
  while(1)
  {
          
	  printf("\nPress \n1.Insert\n2.Display\n3.Search\n4.Modify\n5.Delete\n6.Exit\n") ;
	  scanf("%d",&ch);
	  switch(ch)
	  {
	     case 1:  
	            			
  		    id = open("abc.txt",O_RDWR | O_APPEND | O_CREAT,0777);
	            
	            if(id == -1)
	              printf("Error in opening file...");
	            
	            //A	cepting data from user
	            struct node s;
	            
	            printf("Enter the Roll no, Name and Marks of student");
	            scanf("%d %s %f",&s.roll,s.name,&s.marks);
	            printf("%d %s %f",s.roll,s.name,s.marks);
	            write(id,&s,sizeof(s));
	            break;
	     case 2:  
	            			
  		    id = open("abc.txt",O_RDONLY);
  		    
  		    
  		    
  		    if(id == -1)
	              printf("Error in opening file...");
	              
	            printf("\nRoll\t\tName\t\tMarks\n");  
	            while(read(id,&s,sizeof(s)))
	            {
	               
	               printf("%d\t\t %s\t\t %f\n",s.roll,s.name,s.marks);
	            }
	            
	            break;
	     case 3:
	     	     
	     	     id = open("abc.txt",O_RDONLY);
  		     printf("Enter the roll number:");
  		     scanf("%d",&key);
  		    if(id == -1)
	              printf("Error in opening file...");
	              
	            printf("\nRoll\t\tName\t\tMarks\n");  
	            while(read(id,&s,sizeof(s)))
	            {
	               
	               if(s.roll==key)
	               {
	                  printf("%d\t\t %s\t\t %f\n",s.roll,s.name,s.marks);
	                  flag=1;
	                  break;
	               }
	            }	
	            if(flag==0)
	            {
	              printf("\nRecord not found....!");
	            }  
	            break;
	     case 4: 
	               fd= open("xyz.txt",O_WRONLY | O_APPEND | O_CREAT,0777);
	                flag=0;
	     	        id = open("abc.txt",O_RDONLY);
	  		     printf("Enter the roll number:");
	  		     scanf("%d",&key);
	  		    if(id == -1)
			      printf("Error in opening file...");
			      
			    
			    while(read(id,&s,sizeof(s)))
			    {
			       
			       if(s.roll==key)
			       {
			          printf("Enter the other details:");
			          printf("\nEntr name:");
			          scanf("%s",s.name);
			          printf("\nEnter marks:");
			          scanf("%f",&s.marks);
			          s.roll=key;
			          
			         
			          
			          flag=1;
			          printf("\nRecord modified...");
			       }
			        write(fd,&s,sizeof(s));
			    }	
			    if(flag==0)
			    {
			      printf("\nRecord not found....!");
			    } 
			    remove("abc.txt");
			    rename("xyz.txt","abc.txt");  
	            break;
	     case 5:  
	             fd= open("xyz.txt",O_WRONLY | O_APPEND | O_CREAT,0777);
	                flag=0;
	     	        id = open("abc.txt",O_RDONLY);
	  		     printf("Enter the roll number:");
	  		     scanf("%d",&key);
	  		    if(id == -1)
			      printf("Error in opening file...");
			      
			    
			    while(read(id,&s,sizeof(s)))
			    {
			       
			       if(s.roll==key)
			       {
			         flag=1;
			         continue;
			       }
			        write(fd,&s,sizeof(s));
			    }	
			    if(flag==0)
			    {
			      printf("\nRecord not found....!");
			    } 
			    else
			    {
			      printf("\nRecord deleted....!");
			    }
			    remove("abc.txt");
			    rename("xyz.txt","abc.txt");
	            break;
	     case 6:
	            return 0;
	     default:
	             printf("\nYou have Entered wrong choice...");
          }
  }
  return 0;
}
