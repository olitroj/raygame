#ifndef GLOBALS
#define GLOBALS

#define PHYSICS_FIXED_STEP_TIME 1/60.f

#ifdef DEBUG
#include <stdio.h>
#include <time.h>

#define LOG(fmt, ...) \
    printf("[LOG] " fmt "\n", ##__VA_ARGS__)

#define TIME_START(name) \
    struct timespec name##_start; \
    clock_gettime(CLOCK_MONOTONIC, &name##_start)

#define TIME_END(name) do { \
    struct timespec name##_end; \
    clock_gettime(CLOCK_MONOTONIC, &name##_end); \
    long long elapsed = \
        (long long)(name##_end.tv_sec - name##_start.tv_sec) * 1000000000LL + \
        (name##_end.tv_nsec - name##_start.tv_nsec); \
    printf("[TIME] %s: %lld ns (%.3f ms)\n", \
           #name, elapsed, elapsed / 1000000.0); \
} while (0)

#else

#define LOG(...)
#define TIME_START(name)
#define TIME_END(name)

#endif

#endif