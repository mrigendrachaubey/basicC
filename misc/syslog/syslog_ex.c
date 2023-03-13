/* send a message to the control log by syslog() function code example */
//void syslog(int priority, const char *message, ... /* argument */);
#include <stdio.h>
#include <syslog.h>
// #include <stdlib.h> is needed for the resolution of EXIT_SUCCESS
#include <stdlib.h>
// #include <time.h> is needed for the clock() function and the macro CLOCKS_PER_SEC
#include <time.h>
// #include <unistd.h> and #include <sys/types.h> are needed for the functions uid_t getuid(void); and uid_t geteuid(void);
//getuid() returns the real user ID of the calling process.
//geteuid() returns the effective user ID of the calling process.
//These functions are always successful.
#include <unistd.h>
#include <sys/types.h>

#define RANGE (100000)

int main()
{
    {
        const clock_t start = clock();

        unsigned int i;
        for (i = 0; i < RANGE; i++){
            printf ("Program started by Real User %u (Effective User %u)\n", getuid(), geteuid());
        }
        printf("\n");

        const clock_t end = clock();
        const float seconds = (float) (end - start) / CLOCKS_PER_SEC;
        printf("printf: Seconds elapsed %f\n", seconds);
    }
    {
        const clock_t start = clock();

        setlogmask (LOG_UPTO (LOG_NOTICE));
        openlog ("HappyCodings", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
        unsigned int i;
        for (i = 0; i < RANGE; i++){
            syslog (LOG_NOTICE, "Program started by Real User %u (Effective User %u)", getuid(), geteuid());
        }
        closelog ();

        const clock_t end = clock();
        const float seconds = (float) (end - start) / CLOCKS_PER_SEC;
        printf("syslog: Seconds elapsed %f\n", seconds);

    }
    return EXIT_SUCCESS;
}