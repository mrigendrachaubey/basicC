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
	printf("%d: thread:%d\n",__LINE__, common_var);
	pthread_mutex_lock(&work_mutex);
	common_var = common_var+1;
	pthread_mutex_unlock(&work_mutex);
	printf("%d: thread:%d\n",__LINE__, common_var);
}

int main()
{
	pthread_t a_thread;
	void *thread_result;
	pthread_mutex_init(&work_mutex, NULL);
	pthread_create(&a_thread, NULL, thread_function, NULL);

	printf("%d: main:%d\n",__LINE__, common_var);
	pthread_mutex_lock(&work_mutex);
	common_var = common_var+1;
	pthread_mutex_unlock(&work_mutex);
	printf("%d: main:%d\n",__LINE__, common_var);
	pthread_join(a_thread, &thread_result);
	printf("thread joined\n");
	pthread_mutex_destroy(&work_mutex);
	exit(EXIT_SUCCESS);
}

