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
    // DF EMPTY
    CDataFrame<int> df;
    EXPECT_EQ(df.keys().size(), 0);
    EXPECT_EQ(df.data().dim_h(), 0);
    EXPECT_EQ(df.data().dim_v(), 0);

    // DF WITH KEYS
    CDataFrame<int> df2({"a", "b", "c"});
    EXPECT_EQ(df2.keys().size(), 3);
    EXPECT_TRUE(df2.data().is_empty());

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    CDataFrame<int> df3(data);
    EXPECT_EQ(df3.keys().size(), 0);
    EXPECT_EQ(df3.data(), data);

    // DF WITH KEYS AND DATA
    CDataFrame<int> df4({"a", "b", "c"}, data);
    EXPECT_EQ(df4.keys().size(), 3);
    EXPECT_EQ(df4.data(), data);

    // DF WITH KEYS SIZE DIFFERENT FROM DATA SIZE
    EXPECT_THROW(CDataFrame<int>({"a", "b", "c"}, cmatrix<int>(3, 2)), std::invalid_argument);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
