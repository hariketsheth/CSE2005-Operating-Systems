#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void sig_usr(int signo){
    if(signo == SIGINT)
    printf("Signal Received!");
    return;
}

int main(){
    int i, status;
    pid_t pid, ppid;
    ppid = getpid();
    printf("PARENT PROCESS CREATED\n\n");
    printf("Running: \n");
    printf("PARENT PROCESS STARTED\n\n");
    pid = fork();
    if(pid==0){
        printf("CHILD PROCESS CREATED\n\n");
        printf("Running: \n");
        printf("CHILD PROCESS STARTED\n\n");
        for(i=1; i<=50; i++)
            if(i%2==0)
                printf("Even: %d\n",i);
        printf("killing parent...\n");
        kill(ppid, SIGINT);
        printf("CHILD PROCESS ENDED\n\n");
        printf("PARENT PROCESS ENDED\n\n");
    }
    else{
        if(pid>0)
            pid = waitpid(pid, &status,0);
        if(signal(SIGINT,sig_usr) == SIG_ERR)
            printf("Signal processed ");
    }
    return 0;
}