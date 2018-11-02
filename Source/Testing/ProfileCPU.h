#ifndef _PROFILE_CPU_H
#define _PROFILE_CPU_H

#define PROFILER_INIT(file_name) \
FILE * fp; \
fopen_s(&fp,file_name,"a"); \
LARGE_INTEGER frequency; \
LARGE_INTEGER tStart,tStop; \
double dElapsedTime; \
QueryPerformanceFrequency(&frequency);

#define PROFILER_START \
QueryPerformanceCounter(&tStart);

#define PROFILER_STOP(comment) \
QueryPerformanceCounter(&tStop); \
dElapsedTime=(double)(tStop.QuadPart-tStart.QuadPart)/frequency.QuadPart; \
fprintf(fp,"%s:%f\n",comment,dElapsedTime);

#define PROFILER_DEINIT \
fclose(fp);
#elif
#define TIMER_INIT(file_name)
#define TIMER_START
#define TIMER_STOP(comment)

#endif