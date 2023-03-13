#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main()
{
	int res = mkfifo("/tmp/myfifo", 0777);
	if(res == 0)
		printf("fifo created\n");
	exit(EXIT_SUCCESS);
}