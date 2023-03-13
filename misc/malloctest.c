#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <assert.h>

struct metadata
{
	size_t size;
	unsigned char magic;
	struct metadata *next;
};

struct metadata *head = NULL;

void *mymalloc(size_t size);
void myfree(void *ptr);

void *mymalloc(size_t size)
{
	if (size == 0)
		return NULL;
	struct metadata *block = NULL;
	block = sbrk(0);
	size_t fsize = sizeof(block) + size;
	sbrk(fsize);

	block->next = NULL;
	block->size = size - sizeof(struct metadata);
	block->magic = 1;

	if (NULL == head)
	{
		head = block;
	}
	else
	{
		struct metadata *tmp;
		tmp = head;
		while (NULL != tmp->next)
		{
			// printf("%p %p\n", tmp->next, NULL);
			tmp = tmp->next;
		}
		tmp->next = block;
	}
	printf("%p %p %ld %ld\n", block, block + 1, sizeof(block), sizeof(struct metadata));
	return (block + 1); // we return only the memory part not the metadata
}

void myfree(void *mem_ptr)
{
	struct metadata *meta_ptr = NULL;
	if (mem_ptr != NULL)
		meta_ptr = (struct metadata *)mem_ptr - 1; // take pointer to access metadata of this allocation

	printf("metaptr: %p memptr: %p\n", meta_ptr, mem_ptr);

	if (meta_ptr->magic == 1)
		meta_ptr->magic = 0; // this memory is ready to be reused
}

int main(void)
{
	int *arr, *prr;
	arr = mymalloc(3 * sizeof(*arr));
	prr = mymalloc(6 * sizeof(*arr));
	if (NULL != arr)
	{
		arr[0] = 1;
		arr[1] = 2;
		arr[2] = 3;
		printf("arr: %d %d %d\n", arr[0], arr[1], arr[2]);
	}
	if (NULL != prr)
	{
		prr[0] = 4;
		prr[1] = 5;
		prr[2] = 6;
		printf("prr: %d %d %d\n", prr[0], prr[1], prr[2]);
	}
	myfree(arr);
	myfree(prr);
	return 0;
}