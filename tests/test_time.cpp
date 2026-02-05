#include <iostream>

#include "gtest/gtest.h"
#include "time.hpp"

TEST(TimeTest, Operators) {
    using novokhatskiy::Time;
    Time t1({1, 2});
    Time t2({3, 4});

    EXPECT_TRUE(t1 < t2);
    EXPECT_FALSE(t1 > t2);
    EXPECT_TRUE(t1 <= t2);
    EXPECT_FALSE(t1 >= t2);
    EXPECT_EQ(t2 - t1, Time({2, 2}));
    EXPECT_EQ(Time({23, 6}) - Time({18, 20}), Time({4, 46}));
    EXPECT_EQ(t1 + t2, Time({4, 6}));
}