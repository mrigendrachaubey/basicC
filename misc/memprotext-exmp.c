#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)	//for error handling

static char *buffer;						//pointer to static buffer variable

static void handler(int sig, siginfo_t *si, void *unused)	//function to handle segfaults signals here
{
	printf("Got SIGSEGV at address: 0x%lx\n",(long) si->si_addr);
	/* print address where program gets segfault. Should be the read only area i.e. buffer+2*pagesize */
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	char *p;
	int pagesize;
	struct sigaction sa;

	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handler;			//setup signal handler
	if (sigaction(SIGSEGV, &sa, NULL) == -1)
		handle_error("sigaction");

	pagesize = sysconf(_SC_PAGE_SIZE);		//function to find pagesize of the system
	if (pagesize == -1)
		handle_error("sysconf");
	printf("Pagesize is:		0x%x\n",pagesize);
	/* Allocate a buffer aligned on a page boundary; initial protection is PROT_READ | PROT_WRITE */

	buffer = memalign(pagesize, 4 * pagesize);	//allocate memory of size 4*pagesize aligned to pagesize on heap
	if (buffer == NULL)
		handle_error("memalign");
	printf("Start of region:        0x%lx\n", (long) buffer);	//print start of buffer memory region
	
	if (mprotect(buffer + pagesize * 2, pagesize, PROT_READ) == -1)
	/* Make memory at address buffer+2*pagesize of size [pagesize] to read only */
		handle_error("mprotect");

	for (p = buffer ; ; )		//loop to keep writing in the memory region after buffer
		*(p++) = 'a';
	/* Will give segfault when you it tries to write in region which we make read only with mprotect */

	printf("Loop completed\n");     /* Should never happen */
	exit(EXIT_SUCCESS);
}
