/*
 * thread synchronization with mutex
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

pthread_mutex_t work_mutex;
int common_var=2;

void *thread_function()
{
	while(1)
	{
		res = read(pipe_fd, buffer, BUFFER_SIZE);
		if(res != 0)
		{
			pthread_mutex_lock(&work_mutex);
			common_var = common_var+1;
			pthread_mutex_unlock(&work_mutex);
		}
	}
}

int main()
{
	pthread_t a_thread;
	void *thread_result;
	pthread_mutex_init(&work_mutex, NULL);
	pthread_create(&a_thread, NULL, thread_function, NULL);

	exit(EXIT_SUCCESS);
}

