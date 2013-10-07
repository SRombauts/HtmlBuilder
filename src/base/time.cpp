/**
 * @file    time.cpp
 * @ingroup base
 * @brief   Simple time tools.
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "time.h"


time_t Time::getTickMs() {
    time_t          TickMs = 0;
    int             Res;
    struct timespec ts_now;

    // Get current time, using the MONOTONIC clock
    Res = clock_gettime(CLOCK_MONOTONIC, &ts_now);
    if (0 == Res) {
        TickMs = (ts_now.tv_sec * 1000) + (ts_now.tv_nsec / 1000000);
    }

    return TickMs;
}

time_t Time::getTickUs() {
    time_t          TickUs = 0;
    int             Res;
    struct timespec ts_now;

    // Get current time, using the MONOTONIC clock
    Res = clock_gettime(CLOCK_MONOTONIC, &ts_now);
    if (0 == Res) {
        TickUs = (ts_now.tv_sec * 1000000) + (ts_now.tv_nsec / 1000);
    }

    return TickUs;
}

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

