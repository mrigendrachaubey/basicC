#include <stdio.h>
#include <pthread.h>
        
/*thread function definition*/
/*
pthread_create (thread, attr, start_routine, arg)

Parameter	Description
-----------------------------
thread	        An opaque, unique identifier for the new thread returned by the subroutine.
attr	        An opaque attribute object that may be used to set thread attributes. You can specify a thread attributes object, or NULL for the default values.
start_routine	The C routine that the thread will execute once it is created.
arg	        A single argument that may be passed to start_routine. It must be passed by reference as a pointer cast of type void. NULL may be used if no argument is to be passed.

*/
void* threadFunction(void* args)
{
    while(1)
    {
        printf("I am threadFunction.\n");
    }
}
int main()
{
    /*creating thread id*/
    pthread_t id;
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
        return 0; /*return from main*/
    }
    
    while(1)
    {
        printf("I am main function.\n");      
    }
    
    return 0;
}
