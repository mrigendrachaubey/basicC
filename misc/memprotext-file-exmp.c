//https://www.informit.com/articles/article.aspx?p=23618&seqNum=10
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static int alloc_size;
static char* memory;

void segv_handler (int signal_number) 
{
	printf ("memory accessed!\n");
	mprotect (memory, alloc_size, PROT_READ | PROT_WRITE);
} 

int main ()
{
	int fd;
	struct sigaction sa;

	/* Install segv_handler as the handler for SIGSEGV. */
	memset (&sa, 0, sizeof (sa));
	sa.sa_handler = &segv_handler;
	sigaction (SIGSEGV, &sa, NULL);

	/* Allocate one page of memory by mapping /dev/zero. Map the memory
	as write-only, initially. */
	alloc_size = getpagesize ();
	printf("alloc size %d %#x\n", alloc_size, alloc_size);

	fd = open ("/dev/zero", O_RDONLY);

	memory = mmap (NULL, alloc_size, PROT_WRITE, MAP_PRIVATE, fd, 0);
	close (fd);

	/* Write to the page to obtain a private copy. */
	memory[0] = 0;
	/* Make the memory unwritable. */
	mprotect (memory, alloc_size, PROT_NONE);

	/* Write to the allocated memory region. */
	memory[0] = 1;

	/* All done; unmap the memory. */
	printf ("all done\n");
	munmap (memory, alloc_size);
	return 0;
}