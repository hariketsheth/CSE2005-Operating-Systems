#include <stdio.h>
#include <pthread.h>

const int numberOfThreads = 2;
const int numberOfPrints = 50;

void* execute(void* _number)
{
	int number = *(int*)_number;
	if(number==1){
	    for( int i = 0 ; i< numberOfPrints ;i++){
    		printf("Register Number: 20BCE1975. Thread Number: %d\n", number);
    	}
	}
	else{
	    for( int i = 0 ; i< numberOfPrints ;i++){
    		printf("First Name: Hariket. Thread Number: %d\n", number);
    	}
	}
	
	return NULL;
}

int main(){
	
	pthread_t threads[numberOfThreads];
	
	int number[numberOfThreads];
	for(int i =0;i<numberOfThreads;i++)
		number[i] = i+1;
		
		
	for(int i = 0 ;i< numberOfThreads;i++){
		if( pthread_create(&threads[i] , NULL , execute,&number[i]) )
			printf("Thread Number %d fail!!\n" ,number[i]);
	}
	
	for(int i = 0 ;i< numberOfThreads;i++)	{
		pthread_join(threads[i],NULL);
	}
	
	return 0;
}