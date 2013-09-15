#include "foo.h"
#include "gtest/gtest.h"

#include <limits>

TEST(Foo,Incr)
{
    EXPECT_EQ(0, Foo::Incr(-1));
    EXPECT_EQ(1, Foo::Incr(0));
    EXPECT_EQ(2, Foo::Incr(1));
    // Incrementing the maximum int value overflows and gives the minimum int value
    EXPECT_EQ(std::numeric_limits<int>::min(), Foo::Incr(std::numeric_limits<int>::max()));
}
