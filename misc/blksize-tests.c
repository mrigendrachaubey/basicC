#include <linux/fs.h>
#include <sys/ioctl.h>
#include <linux/fs.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <stdint.h> //uint64_t

int blkgetsize(int fd, uint64_t *psize)
{
#ifdef BLKGETSIZE64
	int ret = ioctl(fd, BLKGETSIZE64, psize);
#elif BLKGETSIZE
	unsigned long sectors = 0;
	int ret = ioctl(fd, BLKGETSIZE, &sectors);
	*psize = sectors * 512ULL;
#else
# error "Linux configuration error (blkgetsize)"
#endif
	printf("blkgetsize: %ld %ld\n",*psize , *psize/512);
	return ret;
}

int blkgetsectorsize(int fd, int *size)
{
#ifdef BLKSSZGET
	int ret = ioctl(fd, BLKSSZGET, size);
#else
# error "Linux configuration error (BLKSSZGET)"
#endif
	printf("blkgetsectorsize: %ld\n", *size );
	return ret;
}

int main()
{
	int fd = open("/dev/sda", O_RDONLY);
	uint64_t psize;
	int size;
	printf("blkgetsize: %d\n", blkgetsize(fd, &psize) );
	printf("blkgetsectorsize: %d\n", blkgetsectorsize(fd, &size) );
	close(fd);
	return 0;
}