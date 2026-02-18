#include <sys/sysctl.h>
#include <sys/time.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>

#define B_ERROR -1

typedef uint64_t bigtime_t;

bigtime_t
system_time(void) {
    struct timeval boottime;
    size_t size = sizeof(boottime);
    struct timeval now;
    struct timezone tz;
    
    if (sysctlbyname("kern.boottime", &boottime, &size, NULL, 0) != 0) {
        return B_ERROR;
    }

    (void)gettimeofday(&now, &tz);

    // Calculate the uptime in microseconds
    time_t seconds = now.tv_sec - boottime.tv_sec;
    suseconds_t microseconds = now.tv_usec - boottime.tv_usec;
    return (bigtime_t)seconds * 1000000 + microseconds;
}


void main() {

printf("Uptime: %llu\n", system_time() / 1000 / 1000 / 60 ); 

}
