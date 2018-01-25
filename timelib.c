#include <stdlib.h>
#include "timelib.h"

static struct timeval timer;

void time_start_timer()
{
    gettimeofday(&timer, NULL);
}

double time_get_sim_seconds()
{
    struct timeval time_now;
    gettimeofday(&time_now, NULL);

    return (double) (time_now.tv_sec - timer.tv_sec) +
        (double) (time_now.tv_usec - timer.tv_usec) / 1e6;

}
