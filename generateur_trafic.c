#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "messages_types.h"

int main(){
  
  
/*********************************
 * LANCEMENT DES AUTRES PROCESSUS
*********************************/


 int pidgentraf = fork();

  if(pidgentraf==0){
    execl("/home/pdesigaud/3TC/PROJETSDE/Generateur_prio","Generateur_prio",NULL);
  }
  else{

  
  
  
  srand(time(NULL));
  printf("Prog generateur_trafic launched\n");
 
  key_t MSGKEY = 100;
  int MSGTYPE = 1;
  int MSGID = msgget(MSGKEY,0666|IPC_CREAT);

  printf("MSGID reçu par generateur: %d\n",MSGID); 
  
  Message message;

  while(1){
    sleep(5);
    message.mtype = MSGTYPE;
    message.source = (int) rand()%4;
    message.dest = (int) rand()%4;
    while(message.dest == message.source){
      message.dest = (int) rand()%4;
    }
    
    printf("*\n");
    printf("Message créé: %d -> %d\n",message.source,message.dest);
    msgsnd(MSGID, &message, 2*sizeof(int),0);
    printf("Message envoyé\n");
    printf("*\n");
  }
 }  
return 0;
}

