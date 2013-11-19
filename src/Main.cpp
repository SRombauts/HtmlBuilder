/**
 * @file    Main.cpp
 * @ingroup CppSkeleton
 * @brief   A simple skeleton for C++ development with CMake and Google Test.
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <cstdio>

#include "Utils/Time.h"

/**
 * @brief Entry-point of the application, showing how to play with precise time ticks.
 */
int main() {
    using Utils::Time;

    time_t startUs = Time::getTickUs();
    // Do something in a few us ...
    time_t endUs   = Time::getTickUs();
    time_t deltaUs = Time::diff(startUs, endUs);
    printf("elpased time: %luus\n", deltaUs);

    time_t startMs = Time::getTickMs();
    // Do something in a few ms...
    time_t endMs   = Time::getTickMs();
    time_t deltaMs = Time::diff(startMs, endMs);
    printf("elpased time: %lums\n", deltaMs);

    return 0;
}
