/*
 * minor3.c - using producer-consumer paradigm.
 * Daniel Koelzer
 * dlk0138
 * 11/3/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NITEMS 10		// number of items in shared buffer

// shared variables
char shared_buffer[NITEMS];	// echo buffer
int shared_count;		// item count

pthread_mutex_t mutex;		// pthread mutex
pthread_cond_t buffer_full; // Condition for full buffer
pthread_cond_t buffer_empty;// Condition for empty buffer
pthread_cond_t buffer_not_empty;// Condition for buffer containing between 1 and NITEMS-1 items
unsigned int prod_index = 0; 	// producer index into shared buffer
unsigned int cons_index = 0; 	// consumer index into shard buffer

// function prototypes
void * producer(void *arg);
void * consumer(void *arg);

int main() 
{ 
	pthread_t prod_tid, cons_tid1, cons_tid2; 

	// initialize pthread variables
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&buffer_full,NULL);
	pthread_cond_init(&buffer_empty,NULL);
	pthread_cond_init(&buffer_not_empty,NULL);
	
	// start producer thread
	pthread_create(&prod_tid, NULL, producer, NULL);

	// start consumer threads
	pthread_create(&cons_tid1, NULL, consumer, NULL);
	pthread_create(&cons_tid2, NULL, consumer, NULL);
	
	// wait for threads to finish
	pthread_join(prod_tid, NULL);
	pthread_join(cons_tid1, NULL);
	pthread_join(cons_tid2, NULL);
			
	// clean up
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&buffer_full);
	pthread_cond_destroy(&buffer_empty);
	pthread_cond_destroy(&buffer_not_empty);
	
	return 0;
}

// producer thread executes this function
void * producer(void *arg)
{
	char key;

	printf("Enter text for producer to read and consumer to print, use Ctrl-C to exit.\n\n");

	// this loop has the producer read in from stdin and place on the shared buffer
	while (1)
	{
		// read input key
		scanf("%c", &key);

		//Lock mutex, check for full condition.
		//If full, signal that the buffer is full and must be emptied by consumer before continuing.
		pthread_mutex_lock(&mutex);
		if (shared_count == NITEMS){
				pthread_cond_signal(&buffer_full);
				while(shared_count == NITEMS){ 
					pthread_cond_wait(&buffer_empty,&mutex); //Spurious wakeup handling
				}
			}
		else if(shared_count != 0) { //Check for between 1 and NITEMS-1 (inclusive) in buffer. If true, signal that buffer is not empty, allowing consumer to print
			pthread_cond_signal(&buffer_not_empty);
		}

		// store key in shared buffer
		shared_buffer[prod_index] = key;

		// update shared count variable
		shared_count++;

		// update producer index
		if (prod_index == NITEMS - 1)
			prod_index = 0;
		else
			prod_index++;
		
		// release mutex lock
		pthread_mutex_unlock(&mutex); 
	}

	return NULL;
}

// consumer thread executes this function
void * consumer(void *arg)
{
	char key;

	long unsigned int id = (long unsigned int)pthread_self();

	// this loop has the consumer gets from the shared buffer and prints to stdout
	while (1)
	{
		//Lock mutex, check for empty condition
		//If empty, signal that buffer is empty and requires filling by produce before continuing
		//Wait until buffer is not empty
		pthread_mutex_lock(&mutex);
		if (shared_count == 0) {
				pthread_cond_signal(&buffer_empty);
				while(shared_count == 0){ 
					pthread_cond_wait(&buffer_not_empty,&mutex); //Spurious wakeup handling
				}
			}

		// read key from shared buffer
		key = shared_buffer[cons_index];
		
		// echo key
		printf("consumer %lu: %c\n", (long unsigned int) id, key);

		// update shared count variable
		shared_count--;

		// update consumer index
		if (cons_index == NITEMS - 1)
			cons_index = 0;
		else
			cons_index++;
	
		// release mutex lock
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}


