#include<iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

void *print( void *ptr );
int main(){
     pthread_t thread1, thread2;
     char *msg1 = "Operating System Hariket 1";
     char *msg2 = "Operating System Hariket 2";
     int  p1, p2;
 
     p1 = pthread_create( &thread1,  NULL, print, (void*) msg1);
     p2 = pthread_create( &thread2, NULL, print, (void*) msg2);
 
     pthread_join(thread1, NULL);
     pthread_join(thread2, NULL);
 
     exit(0);
}
void *print( void *ptr ){
        
     char *message;
     message = (char *) ptr;
     printf("%s \nThread ID: %lu\nProcess ID: %d\n", message, pthread_self(), getpid());
     
}