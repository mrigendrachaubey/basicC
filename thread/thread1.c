#include <stdio.h> //printf etc
#include <pthread.h> //pthread functions
#include <stdlib.h> //for EXIT_FAILURE
        
/*thread function definition*/
/*
pthread_create (thread, attr, start_routine, arg)

Parameter	Description
-----------------------------
thread	        An opaque, unique identifier for the new thread returned by the subroutine.
attr	        An opaque attribute object that may be used to set thread attributes. You can specify a thread attributes object, or NULL for the default values.
start_routine	The C routine that the thread will execute once it is created.
arg	        A single argument that may be passed to start_routine. It must be passed by reference as a pointer cast of type void. NULL may be used if no argument is to be passed.

compile: gcc thread1.c -lpthread -D_REENTRANT
*/
void* threadFunction(void* args)
{
	printf("I am threadFunction.\n");
	pthread_exit("threadFunction exiting");
}

int main()
{
	/*creating thread id*/
	pthread_t id;
	void *thread_result;
	int ret;

	/*creating thread*/
	ret=pthread_create(&id,NULL,&threadFunction,NULL);
	if(ret == 0)
	{
		printf("Thread created successfully.\n");
	}
	else
	{
		printf("Thread not created.\n");
		exit(EXIT_FAILURE);
	}
	printf("waiting for the thread to finish\n");
	pthread_join(id, &thread_result);
	printf("thread joined, return:%s.\nI am mainFunction.\n", (char *)thread_result);
	return 0;
}
