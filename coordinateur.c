/*********************************************************
 * PROJET SDE
 * CARREFOUR ROUTIER
 * TEDDY TOUSSAINT / PAUL DESIGAUD
 * 3TC
 * GROUPE 2
*********************************************************/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include "messages_types.h"
#include "semaphore.h"
#include "shmem.h"

int main(){

/*********************************
 * LANCEMENT DES AUTRES PROCESSUS
*********************************/




/*****************************
 * CREATION ET INI DES IPCs
*****************************/

    key_t MSGKEY = 100;
    key_t MEMKEY = 200;
    key_t MUTKEY = 300;
    
    
    int idMut;
    if((idMut = create_semaphore(MUTKEY))==-1){printf("erreur création mutex"); exit(1);}
    int valMut;
    if((valMut = init_semaphore(idMut, 1))==-1){printf("erreur initialisation"); exit(1);}

    int MSGTYPE = 1;
    int compteur = 1;
    int MSGID = msgget(MSGKEY,0666|IPC_CREAT);
    printf("MSGID reçu par coordinateur: %d\n",MSGID); 

    int idMem;
    if((idMem = create_shmem(MEMKEY, 7*sizeof(int)))==-1){printf("erreur");
    printf(" création mémoire."); exit(1);}

    int* memory;
    int mutexPris;
     
    printf("On tente la prise !\n");
    if((mutexPris = down(idMut))==-1){ printf("erreur prise mutex"); exit(1);}
    printf("Prise du mutex.\n");


    
    if((memory=attach_shmem(idMem))==NULL){printf("Erreur attachment");exit(1);}
    memory[0]=0;
    memory[1]=1;
    memory[2]=0;
    memory[3]=1;
    memory[4]=getpid();
    printf("Mémoire initialisée.\n");
    int* rdMem = attach_shmem(idMem);
    printf("Valeurs mises en mémoires: %d %d %d %d %d\n",rdMem[0],rdMem[1],rdMem[2],rdMem[3],rdMem[4]);
    
    
    if((mutexPris = up(idMut))==-1){ printf("erreur releasing mutex"); exit(1);}
    printf("Mutex relaché.\n");



    Voiture voiture;
    Message message;

/************************************
 * BOUCLE INFINIE
************************************/

    while(1){
    

    
    printf("Coordinateur en attente de msg\n");
    msgrcv(MSGID,&message,MSGKEY,MSGTYPE,0);
    printf("*\n"); 
    printf("Reçu: voiture n°%d, %d -> %d\n",compteur,message.source,message.dest);
    printf("Sauvegarde en cours\n");
    
    voiture.source = message.source;
    voiture.dest = message.dest;
    printf("Saved: voiture n°%d, %d -> %d\n",compteur,voiture.source,voiture.dest);
    printf("*\n");
    compteur++;
    }

    //TODO

return 0;
}



