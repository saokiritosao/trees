#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "timer.h"


struct timeval tv1,tv2,dtv;

struct timezone tz;

void time_start()
{

    gettimeofday(&tv1, &tz);

}

long time_stop()
{
    gettimeofday(&tv2, &tz);

    dtv.tv_sec= tv2.tv_sec -tv1.tv_sec;
    dtv.tv_usec=tv2.tv_usec-tv1.tv_usec;

    if(dtv.tv_usec<0) { dtv.tv_sec--; dtv.tv_usec+=1000000; }

    return dtv.tv_sec*1000+dtv.tv_usec/1000;

}