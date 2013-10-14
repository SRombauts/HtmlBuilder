/**
 * @file    random_test.cpp
 * @ingroup Utils
 * @brief   Generating random data.
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "utils/random.h"

#include <limits>

#include "gtest/gtest.h"

TEST(Random, genChar) {
    EXPECT_NE(Utils::Random::genChar(), Utils::Random::genChar());
}

TEST(Random, genString) {
    #define NB_CHAR 10
    char str1[NB_CHAR+1] = "";
    char str2[NB_CHAR+1] = "";
    Utils::Random::genString(str1, NB_CHAR);
    Utils::Random::genString(str2, NB_CHAR);
    EXPECT_STRNE(str1, str2);
}
