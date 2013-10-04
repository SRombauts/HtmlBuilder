/**
 * @file    foo_test.cpp
 * @ingroup CppSkeleton
 * @brief   A simple skeleton for C++ development with CMake and Google Test.
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "foo.h"

#include <limits>

#include "gtest/gtest.h"

TEST(Foo, Incr) {
    EXPECT_EQ(0, Foo::Incr(-1));
    EXPECT_EQ(1, Foo::Incr(0));
    EXPECT_EQ(2, Foo::Incr(1));
    // Incrementing the maximum int value overflows and gives the minimum int value
    EXPECT_EQ(std::numeric_limits<int>::min(), Foo::Incr(std::numeric_limits<int>::max()));
}
