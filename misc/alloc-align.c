//https://en.cppreference.com/w/c/memory/aligned_alloc

//Defined in header <stdlib.h>
//void *aligned_alloc( size_t alignment, size_t size );

#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
	int *p1 = malloc(10*sizeof *p1);
	printf("default-aligned addr:   %p\n", (void*)p1);
	free(p1);
 
	int *p2 = aligned_alloc(1024, 1024*sizeof *p2);
	printf("1024-byte aligned addr: %p\n", (void*)p2);
	free(p2);
	return 0;
}