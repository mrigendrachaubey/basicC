#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <linux/unistd.h>       /* for _syscallX macros/related stuff */
#include <linux/kernel.h>       /* for struct sysinfo */
#include <sys/sysinfo.h>

/* Compile as 
	$ gcc -o linux_uptime linux_uptime.c 
   Run as,
	$ ./linux_uptime
*/

long get_uptime(void) {
	struct sysinfo s_info;
	int error = sysinfo(&s_info);
	if(error != 0) {
		printf("code error = %d\n", error);
	}
	return s_info.uptime;
}

long read_proc_uptime() {
	FILE * uptimefile;
	char uptime_chr[28];
	long uptime = 0;

	if((uptimefile = fopen("/proc/uptime", "r")) == NULL) {
		printf("can't read /proc/uptime\n");
		exit(EXIT_FAILURE);
	}

	fgets(uptime_chr, 12, uptimefile);
	fclose(uptimefile);

	uptime = strtol(uptime_chr, NULL, 10);
	return uptime;
}

int main(int argc, char **argv) {
	long uptime = get_uptime();
	printf("Update is: %ld\n", uptime/60);
	printf("System up for %ld seconds, %ld hours\n", uptime, uptime / 3600);

	printf("Uptime by reading /proc/uptime\n");
	uptime = read_proc_uptime();
	printf("System up for %ld seconds, %ld hours\n", uptime, uptime / 3600);

	/* Both above methods are correct, but preferred will be first 
	using struct sysinfo */

	return 0;
}
