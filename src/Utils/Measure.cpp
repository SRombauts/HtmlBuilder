/**
 * @file    Measure.cpp
 * @ingroup Utils
 * @brief   Encapsulate a microsecond time measurement.
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "Utils/Measure.h"
#include "Utils/Time.h"

namespace Utils {

// Constructor measure and save the first time tick.
Measure::Measure() {
    mStartTimeUs = Time::getTickUs();
}

// Measure a second time tick and return the difference since the first one.
time_t Measure::diff() {
    time_t  EndTimeUs   = Time::getTickUs();
    time_t  DeltaTimeUs = Time::diff(mStartTimeUs, EndTimeUs);

    return DeltaTimeUs;
}

} // namespace Utils

