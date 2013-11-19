/**
 * @file    Random_test.cpp
 * @ingroup Utils
 * @brief   Generating random data.
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "Utils/Random.h"

#include <limits>

#include "gtest/gtest.h"

/// Test Random::genChar() random character generator
TEST(Random, genChar) {
    EXPECT_NE(Utils::Random::genChar(), Utils::Random::genChar());
}

#define RANDOM_TEST_NB_CHAR 10 ///< Size of random string
/// Test RandomgenString() random string generator
TEST(Random, genString) {
    char str1[RANDOM_TEST_NB_CHAR+1] = "";
    char str2[RANDOM_TEST_NB_CHAR+1] = "";
    Utils::Random::genString(str1, RANDOM_TEST_NB_CHAR);
    Utils::Random::genString(str2, RANDOM_TEST_NB_CHAR);
    EXPECT_STRNE(str1, str2);
}
