/**
 * @file    Time.cpp
 * @ingroup Utils
 * @brief   Simple time tools.
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "Utils/Time.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

namespace Utils {

// Get tick in milliseconds
time_t Time::getTickMs() {
    time_t          TickMs = 0;
#if defined(__GNUC__)
    int             Res;
    struct timespec ts_now;

    // Get current time, using the MONOTONIC clock
    Res = clock_gettime(CLOCK_MONOTONIC, &ts_now);
    if (0 == Res) {
        TickMs = (ts_now.tv_sec * 1000) + (ts_now.tv_nsec / 1000000);
    }
#elif defined(_WIN32)
    LARGE_INTEGER freq;
    if (FALSE != QueryPerformanceFrequency(&freq)) {
        LARGE_INTEGER t1;
        QueryPerformanceCounter(&t1);
        TickMs = (time_t) ((t1.QuadPart) / (freq.QuadPart / 1000));
    }
#endif

    return TickMs;
}

// Get tick in microseconds
time_t Time::getTickUs() {
    time_t          TickUs = 0;
#if defined(__GNUC__)
    int             Res;
    struct timespec ts_now;

    // Get current time, using the MONOTONIC clock
    Res = clock_gettime(CLOCK_MONOTONIC, &ts_now);
    if (0 == Res) {
        TickUs = (ts_now.tv_sec * 1000000) + (ts_now.tv_nsec / 1000);
    }
#elif defined(_WIN32)
    LARGE_INTEGER freq;
    // TODO(SRombauts) could be done only once ?
    if (FALSE != QueryPerformanceFrequency(&freq)) {
        LARGE_INTEGER t1;
        QueryPerformanceCounter(&t1);
        TickUs = (time_t) ((t1.QuadPart) / (freq.QuadPart / 1000000));
    }
#endif  // __GNUC__

    return TickUs;
}

// Calculate difference between consecutive ticks
time_t Time::diff(const time_t aStartTime, const time_t aEndTime) {
    time_t deltaTime;
    if (aStartTime <= aEndTime) {
        // 0 --- t1 --- t2 --- max
        deltaTime = aEndTime - aStartTime;
    } else {
        // 0 --- t2 --- t1 --- max
        deltaTime = ((time_t)-1 - aStartTime) + 1 + aEndTime;
    }

    return deltaTime;
}

} // namespace Utils

