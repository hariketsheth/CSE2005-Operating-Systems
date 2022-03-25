#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/shm.h>

#define FILLED 0
#define Ready 1
#define NotReady -1

struct memory {
	char buff[100];
	int status, pid1, pid2;
};

struct memory* shmptr;
void sig_usr(int signo){
    if(signo == SIGINT)
    printf("Signal Received!");
    return;
}

//handler function to print message received from parent
void handler(int signum){
	/*if signum is SIGUSR1, then user 1 is receiving a message user 1 */
	if(signum==SIGUSR2){
		printf("\nKill Signal Received............\n");
		kill(shmptr->pid1,SIGINT);
		printf("Child killed :(\n");
		exit(1);
		
	}
}
	
int main(){
	//process id of user 1
	int pid=getpid();
	int shmid;
	//key value of shared memory
	int key=12345;
	//shared memory create
	shmid = shmget(key, sizeof(struct memory), IPC_CREAT | 0666);
	//attaching the shared memory
	shmptr = (struct memory*)shmat(shmid, NULL, 0);
	//store the process id of user 1 in shared memory
	shmptr->pid2 = pid;
	shmptr->status = NotReady;
	
	//calling the signal function using signal type SIGparent
	signal(SIGUSR2, handler);

	while(1){		
		//taking input from child
		printf("Child: ");
		shmptr->status = Ready;
		
		kill(shmptr->pid1,SIGUSR1);
		
		while(shmptr->status ==Ready){
			printf("\nProcess ID: %d\n",shmptr->pid2);
			sleep(2);
			continue;
		}
	}
	
	shmdt((void*)shmptr); 
	return 0;
}
