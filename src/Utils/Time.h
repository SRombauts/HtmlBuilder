/**
 * @file    Time.h
 * @ingroup Utils
 * @brief   Tools for precise time measurement.
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include <ctime>    // time_t

namespace Utils {

/**
 * @brief   Tools for precise time measurement.
 * @ingroup Utils
 *
 * Portable way to get ticks to the microsecond.
 *
 * @see #Utils::Measure
 */
class Time {
public:
    /**
     * @brief Get tick in microseconds.
     *
     * @return Current time in milliseconds.
     */
    static time_t getTickMs();

    /**
     * @brief Get tick in milliseconds.
     *
     * @return Current time in microseconds.
     */
    static time_t getTickUs();

    /**
     * @brief Calculate difference between consecutive ticks.
     *
     * @param[in] aStartTime    First time measurement.
     * @param[in] aEndTime      Second time measurement.
     *
     * @return Number of ticks between the two measurements.
     */
    static time_t diff(const time_t aStartTime, const time_t aEndTime);
};

} // namespace Utils
