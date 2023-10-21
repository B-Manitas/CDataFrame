/**
 * @file CDataFrameTest.tpp
 * @brief File containing unit tests for the 'DataFrame' class.
 *
 * @see CDataFrame.hpp
 * @defgroup test
 */

#include <gtest/gtest.h>
#include "CDataFrame.hpp"

// ==================================================
// Constructor

TEST(CDataFrameTest, Constructor)
{
    // DF EMPTY
    cdata_frame<int> df;
    EXPECT_EQ(df.keys().size(), 0);
    EXPECT_EQ(df.data().dim_h(), 0);
    EXPECT_EQ(df.data().dim_v(), 0);

    // DF WITH KEYS
    cdata_frame<int> df2({"a", "b", "c"});
    EXPECT_EQ(df2.keys().size(), 3);
    EXPECT_TRUE(df2.data().is_empty());

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    EXPECT_EQ(df3.keys().size(), 0);
    EXPECT_EQ(df3.data(), data);

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    EXPECT_EQ(df4.keys().size(), 3);
    EXPECT_EQ(df4.data(), data);

    // DF WITH KEYS SIZE DIFFERENT FROM DATA SIZE
    EXPECT_THROW(cdata_frame<int>({"a", "b", "c"}, cmatrix<int>(3, 2)), std::invalid_argument);

    // DF WITH KEYS NOT UNIQUE
    EXPECT_THROW(cdata_frame<int>({"a", "b", "b"}, cmatrix<int>(3, 3)), std::invalid_argument);
    EXPECT_THROW(cdata_frame<int>({"a", "b", "b"}), std::invalid_argument);
}

// ==================================================
// Getter

TEST(CDataFrameTest, keys)
{
    // DF EMPTY
    cdata_frame<int> df;
    EXPECT_TRUE(df.keys().empty());

    // DF WITH KEYS
    cdata_frame<int> df2({"a", "b", "c"});
    EXPECT_EQ(df2.keys(), (std::vector<std::string>{"a", "b", "c"}));

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    EXPECT_TRUE(df3.keys().empty());

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    EXPECT_EQ(df4.keys(), (std::vector<std::string>{"a", "b", "c"}));
}

TEST(CDataFrame, data)
{
    // DF EMPTY
    cdata_frame<int> df;
    EXPECT_TRUE(df.data().is_empty());

    // DF WITH KEYS
    cdata_frame<int> df2({"a", "b", "c"});
    EXPECT_TRUE(df2.data().is_empty());

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    EXPECT_EQ(df3.data(), data);

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    EXPECT_EQ(df4.data(), data);
}

// ==================================================
// Setter

TEST(CDataFrameTest, set_keys)
{
    // DF EMPTY
    cdata_frame<int> df;
    df.set_keys({"a", "b", "c"});
    EXPECT_EQ(df.keys(), (std::vector<std::string>{"a", "b", "c"}));

    // DF WITH KEYS
    cdata_frame<int> df2({"a", "b", "c"});
    df2.set_keys({"d", "e", "f"});
    EXPECT_EQ(df2.keys(), (std::vector<std::string>{"d", "e", "f"}));

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    df3.set_keys({"a", "b", "c"});
    EXPECT_EQ(df3.keys(), (std::vector<std::string>{"a", "b", "c"}));

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    df4.set_keys({"d", "e", "f"});
    EXPECT_EQ(df4.keys(), (std::vector<std::string>{"d", "e", "f"}));

    // DF WITH KEYS SIZE DIFFERENT FROM DATA SIZE
    EXPECT_THROW(df4.set_keys({}), std::invalid_argument);
    EXPECT_THROW(df4.set_keys({"a", "b", "c", "d"}), std::invalid_argument);

    // DF WITH KEYS NOT UNIQUE
    EXPECT_THROW(df4.set_keys({"a", "b", "b"}), std::invalid_argument);
}

TEST(CDataFrameTest, set_data)
{
    // DF EMPTY
    cdata_frame<int> df;
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    df.set_data(data);
    EXPECT_EQ(df.data(), data);

    // DF WITH KEYS
    cdata_frame<int> df2({"a", "b", "c"});
    df2.set_data(data);
    EXPECT_EQ(df2.data(), data);

    // DF WITH DATA
    cmatrix<int> data2({{7, 8, 9}, {10, 11, 12}});
    cdata_frame<int> df3(data);
    df3.set_data(data2);
    EXPECT_EQ(df3.data(), data2);

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    df4.set_data(data2);
    EXPECT_EQ(df4.data(), data2);

    // DF WITH KEYS SIZE DIFFERENT FROM DATA SIZE
    EXPECT_THROW(df4.set_data(cmatrix<int>(3, 2)), std::invalid_argument);
}

// ==================================================
// Manipulation

TEST(CDataFrameTest, insert_row)
{
    // DF EMPTY
    cdata_frame<int> df;
    df.insert_row(0, {1, 2, 3});
    EXPECT_EQ(df.data(), (cmatrix<int>{{1, 2, 3}}));

    // DF WITH KEYS
    cdata_frame<int> df2({"a", "b", "c"});
    df2.insert_row(0, {1, 2, 3});
    EXPECT_EQ(df2.data(), (cmatrix<int>{{1, 2, 3}}));

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    df3.insert_row(0, {7, 8, 9});
    EXPECT_EQ(df3.data(), (cmatrix<int>{{7, 8, 9}, {1, 2, 3}, {4, 5, 6}}));

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    df4.insert_row(0, {7, 8, 9});
    EXPECT_EQ(df4.data(), (cmatrix<int>{{7, 8, 9}, {1, 2, 3}, {4, 5, 6}}));

    // DF WITH KEYS SIZE DIFFERENT FROM DATA SIZE
    EXPECT_THROW(df4.insert_row(0, {7, 8}), std::invalid_argument);
    EXPECT_THROW(df4.insert_row(0, {7, 8, 9, 10}), std::invalid_argument);
}

TEST(CDataFrameTest, insert_column)
{
    // DF EMPTY
    cdata_frame<int> df;
    df.insert_column(0, {1, 2, 3});
    EXPECT_EQ(df.data(), (cmatrix<int>{{1}, {2}, {3}}));

    // DF WITH KEYS
    cdata_frame<int> df2({"a", "b", "c"});
    df2.insert_column(0, {1, 2, 3}, "d");
    EXPECT_EQ(df2.data(), (cmatrix<int>{{1}, {2}, {3}}));

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    df3.insert_column(0, {7, 8});
    EXPECT_EQ(df3.data(), (cmatrix<int>{{7, 1, 2, 3}, {8, 4, 5, 6}}));

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    df4.insert_column(0, {7, 8}, "d");
    EXPECT_EQ(df4.data(), (cmatrix<int>{{7, 1, 2, 3}, {8, 4, 5, 6}}));

    // DF WITH KEYS SIZE DIFFERENT FROM DATA SIZE
    EXPECT_THROW(df4.insert_column(0, {7, 8, 9}), std::invalid_argument);
    EXPECT_THROW(df4.insert_column(0, {7, 8, 9, 10}), std::invalid_argument);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
