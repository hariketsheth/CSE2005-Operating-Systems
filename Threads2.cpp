#include <stdio.h>
#include <pthread.h>

const int numberOfThreads = 5;
const int numberOfPrints = 5;

void* showThreadNumber(void* _number)
{
	int number = *(int*)_number;
	for( int i = 0 ; i< numberOfPrints ;i++)
	{
		printf("Hello, World. Thread: %d\n", number+1);
	}
	return NULL;
}

int main(){
	
	pthread_t threads[numberOfThreads];
	
	int number[numberOfThreads];
	for(int i =0;i<numberOfThreads;i++)
		number[i] = i;
		
		
	for(int i = 0 ;i< numberOfThreads;i++){
		if( pthread_create(&threads[i] , NULL ,showThreadNumber,&number[i]) )
			printf("Thread Number %d fail!!\n" ,number[i]);
	}
	
	for(int i = 0 ;i< numberOfThreads;i++)	{
		pthread_join(threads[i],NULL);
	}
	
	return 0;
}