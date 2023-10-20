/**
 * @file CDataFrameTest.tpp
 * @brief File containing unit tests for the 'DataFrame' class.
 * 
 * @see CDataFrame.hpp
 * @defgroup test
 */

#include <gtest/gtest.h>
#include "CDataFrame.hpp"

TEST(CDataFrameTest, Constructor)
{
    CDataFrame<int> df;
    EXPECT_EQ(df.keys().size(), 0);
    EXPECT_EQ(df.data().dim_h(), 0);
    EXPECT_EQ(df.data().dim_v(), 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
