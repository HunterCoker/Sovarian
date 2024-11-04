#pragma once

#ifdef _WIN32
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#else
#  include <time.h>
#  include <errno.h>
#  ifdef __APPLE__
#    include <mach/clock.h>
#    include <mach/mach.h>
#  endif
#endif // _WIN32

#include <cstdint>

/**********************************=> unix ************************************/
#ifndef _WIN32
void SleepInMs(uint32_t ms) {
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = ms % 1000 * 1000000;

    while (nanosleep(&ts, &ts) == -1 && errno == EINTR);
}

void SleepInUs(uint32_t us) {
    struct timespec ts;
    ts.tv_sec = us / 1000000;
    ts.tv_nsec = us % 1000000 * 1000;

    while (nanosleep(&ts, &ts) == -1 && errno == EINTR);
}

#ifndef __APPLE__
uint64_t NowInUs() {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return static_cast<uint64_t>(now.tv_sec) * 1000000 + now.tv_nsec / 1000;
}

#else // mac
uint64_t NowInUs() {
    clock_serv_t cs;
    mach_timespec_t ts;

    host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cs);
    clock_get_time(cs, &ts);
    mach_port_deallocate(mach_task_self(), cs);

    return static_cast<uint64_t>(ts.tv_sec) * 1000000 + ts.tv_nsec / 1000;
}
#endif // __APPLE__
#endif // _WIN32
/************************************ unix <=**********************************/

/**********************************=> win *************************************/
#ifdef _WIN32
void SleepInUs(LONGLONG us) {
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);

    LONGLONG targetTicks = (frequency.QuadPart * us) / 1'000'000;

    // Start timing
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);

    // Coarse sleep for most of the interval
    while (true) {
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);

        LONGLONG elapsedTicks = currentTime.QuadPart - startTime.QuadPart;
        if (elapsedTicks >= targetTicks - (frequency.QuadPart / 1'000)) { // 10 ms buffer
            break;
        }

        Sleep(1);  // Coarse sleep to save CPU usage
    }

    // Busy-wait for the remaining microseconds
    while (true) {
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);

        LONGLONG elapsedTicks = currentTime.QuadPart - startTime.QuadPart;
        if (elapsedTicks >= targetTicks) {
            break;
        }
    }
}

void SleepInMs(uint32_t ms) {
    ::SleepInUs(ms * 1000);
}

static inline uint64_t GetPerfFrequency() {
    ::LARGE_INTEGER freq;
    ::QueryPerformanceFrequency(&freq);
    return freq.QuadPart;
}

static inline uint64_t PerfFrequency() {
    static uint64_t xFreq = GetPerfFrequency();
    return xFreq;
}

static inline uint64_t PerfCounter() {
    ::LARGE_INTEGER counter;
    ::QueryPerformanceCounter(&counter);
    return counter.QuadPart;
}

uint64_t NowInUs() {
    return static_cast<uint64_t>(
        static_cast<double>(PerfCounter()) * 1000000 / PerfFrequency());
}
#endif // _WIN32
