#include <sys/ioctl.h>
#include <linux/fs.h>
#include <stddef.h>
#include <stdio.h>

int main()
{
	int fd = open("/dev/sda");
	size_t blockSize;
	int rc = ioctl(fd, BLKSSZGET, &blockSize);
	printf("%ld rc %d\n", blockSize, rc);
	return 0;
}