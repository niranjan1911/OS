#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define wserver 1
#define rserver 2
#define wclient 3
#define rclient 4
 
 struct node
 {
   int status;
   char data[20];
   char data2[20];
 };

int main()
{ 
  struct node *str;
  key_t key=ftok("shmfile",16);
  
  int shm_id = shmget(key,sizeof(struct node),0777|IPC_CREAT);
  
  str=(struct node *) shmat(shm_id,(void *)0,0);
  
  while(str->status!=wserver);
  printf("Server:%s",str->data);
 
  
  str->status=rclient;
  
 //**********
  printf("\nClient:");
  gets(str->data2);
  
  str->status=wclient;
  
  
  shmdt(str);
  
  shmctl(shm_id,IPC_RMID,0);
}
