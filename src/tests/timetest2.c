#include <sys/sysctl.h>
#include <sys/time.h>
#include <stdint.h>
#include <time.h>
#include "header.h"

#define B_ERROR -1

typedef uint64_t bigtime_t;

bigtime_t
system_time(void)
{
    struct timespec ts;

    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
        return (bigtime_t)0;
    }

    return (bigtime_t)ts.tv_sec * 1000000LL
         + (bigtime_t)ts.tv_nsec / 1000LL;
}


void main() {

printf("Uptime: %llu\n", system_time() / 1000 / 1000 / 60 ); 

}
