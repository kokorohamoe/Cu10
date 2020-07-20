#include <iostream>
#include <string.h>
#include <vector>

       #include <sys/time.h>
       #include <sys/resource.h>
struct timespec ts_res;
struct timespec ts_start;
struct timespec ts_stop;
#define CLOCKID CLOCK_REALTIME
float operator - (struct timespec &tv_stop,struct timespec &tv_start){
    float r1;
    float r2;
    r1 = tv_stop.tv_sec - tv_start.tv_sec;
    r2 = tv_stop.tv_nsec - tv_start.tv_nsec;
    r1 *= (1000*1000);
    r2 /= 1000;
    return r1+r2;
}

#define clock_stop     ::clock_gettime(CLOCKID ,&ts_stop)
#define clock_start     ::clock_gettime(CLOCKID ,&ts_start)
#define clock_out       std::cout <<"clock : "<<(ts_stop -ts_start)<<std::endl;
#define clock_save(x)       x = (ts_stop -(ts_start))


