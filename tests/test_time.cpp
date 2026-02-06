#include <iostream>
#include <sstream>
#include <limits>
#include <fstream>

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

TEST(TimeTest, InputTest)
{
    using novokhatskiy::Time;

    std::ifstream file(std::string(TEST_DATA_DIR) + "/time.txt");
    ASSERT_TRUE(file.is_open());

    std::string line;
    int ok = 0;
    int bad = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Time t;

        if (iss >> t && iss.eof())
            ++ok;
        else
            ++bad;
    }

    EXPECT_EQ(ok, 1);
    EXPECT_EQ(bad, 5);

    file.close();
}

TEST(TimeTest, OutputTest)
{
    using novokhatskiy::Time;

    testing::internal::CaptureStdout();
    std::cout << Time({15, 15});
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "15:15");

    testing::internal::CaptureStdout();
    std::cout << Time({9, 9});
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "09:09");

    testing::internal::CaptureStdout();
    std::cout << Time({0, 0});
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "00:00");
}