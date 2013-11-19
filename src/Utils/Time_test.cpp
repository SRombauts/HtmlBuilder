/**
 * @file    Time_test.cpp
 * @ingroup Utils
 * @brief   Simple time tools.
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "Utils/Time.h"

#include <limits>

#include "gtest/gtest.h"

/// Test Time::diff() utility
TEST(Time, diff) {
    using Utils::Time;
    EXPECT_EQ(0,            Time::diff(0, 0));
    EXPECT_EQ(123,          Time::diff(0, 123));
    EXPECT_EQ((time_t)-123, Time::diff(123, 0));
    EXPECT_EQ(0,            Time::diff(123, 123));
    EXPECT_EQ(1,            Time::diff(123, 124));
    EXPECT_EQ((time_t)-1,   Time::diff(124, 123));
    EXPECT_EQ(0,            Time::diff(-1, -1));
    EXPECT_EQ(1,            Time::diff(-1, 0));
    EXPECT_EQ((time_t)-1,   Time::diff(0, -1));
}
