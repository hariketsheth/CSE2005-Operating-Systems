#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sighandler(int sig_num){
    switch(sig_num){
        case 8:{
            printf("\n\n------------------------------------\n");
            printf("Caught Division By Zero. Exiting.. :(\n");
            printf("------------------------------------\n");
            exit(1);
        }
        case 11:{
            printf("\n\n------------------------------------\n");
            printf("Caught Segmentation Fault. Exiting.. :(\n");
            printf("------------------------------------\n");
            exit(1);
        }
        case 20:{
            printf("\n\n------------------------------------\n");
            printf("Caught Ctrl+Z. Exiting.. :(\n");
            printf("------------------------------------\n");
            exit(1);
        }
    }
}
  
int main(){
    signal(SIGTSTP, sighandler);
    signal(SIGFPE, sighandler);
    signal(SIGSEGV, sighandler);
    int num1 = 0;
    int num2 = 5/num1;
    
    char *s = "CSE2005: Operating System";
    //*s = 'A';
    while(1){
      printf("This is running..........\n");
      sleep(1);
    }
    return 0;
}
