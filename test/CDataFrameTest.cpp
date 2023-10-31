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
// CONSTRUCTOR

/** @brief Test the constructor of the 'DataFrame' class. */
TEST(TestConstructor, Constructor)
{
    // DF EMPTY
    cdata_frame<int> df;
    EXPECT_EQ(df.keys().size(), 0);
    EXPECT_EQ(df.index().size(), 0);
    EXPECT_EQ(df.data().width(), 0);
    EXPECT_EQ(df.data().height(), 0);

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    EXPECT_EQ(df3.keys().size(), 0);
    EXPECT_EQ(df3.index().size(), 0);
    EXPECT_EQ(df3.data(), data);

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    EXPECT_EQ(df4.keys().size(), 3);
    EXPECT_EQ(df4.index().size(), 0);
    EXPECT_EQ(df4.data(), data);

    // DF WITH INDEX AND DATA
    cdata_frame<int> df5(data, {"a", "b"});
    EXPECT_EQ(df5.keys().size(), 0);
    EXPECT_EQ(df5.index(), (std::vector<std::string>{"a", "b"}));
    EXPECT_EQ(df5.data(), data);

    // DF WITH KEYS, INDEX AND DATA
    cdata_frame<int> df6({"a", "b", "c"}, data, {"a", "b"});
    EXPECT_EQ(df6.keys().size(), 3);
    EXPECT_EQ(df6.index(), (std::vector<std::string>{"a", "b"}));
    EXPECT_EQ(df6.data(), data);

    // DF WITH KEYS SIZE DIFFERENT FROM DATA SIZE
    EXPECT_THROW(cdata_frame<int>({"a", "b", "c"}, cmatrix<int>(3, 2)), std::invalid_argument);

    // DF WITH KEYS NOT UNIQUE
    EXPECT_THROW(cdata_frame<int>({"a", "b", "b"}, cmatrix<int>(3, 3)), std::invalid_argument);

    // DF WITH INDEX SIZE DIFFERENT FROM DATA SIZE
    EXPECT_THROW(cdata_frame<int>(cmatrix<int>(3, 2), {"a", "b", "c", "d"}), std::invalid_argument);

    // DF WITH INDEX NOT UNIQUE
    EXPECT_THROW(cdata_frame<int>(cmatrix<int>(3, 3), {"a", "b", "b"}), std::invalid_argument);
}

// ==================================================
// GETTER

/** @brief Test the 'keys' method of the 'DataFrame' class. */
TEST(TestGetter, keys)
{
    // DF EMPTY
    cdata_frame<int> df;
    EXPECT_TRUE(df.keys().empty());

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    EXPECT_TRUE(df3.keys().empty());

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    EXPECT_EQ(df4.keys(), (std::vector<std::string>{"a", "b", "c"}));

    // DF WITH INDEX AND DATA
    cdata_frame<int> df5(data, {"a", "b"});
    EXPECT_TRUE(df5.keys().empty());

    // DF WITH KEYS, INDEX AND DATA
    cdata_frame<int> df6({"a", "b", "c"}, data, {"a", "b"});
    EXPECT_EQ(df6.keys(), (std::vector<std::string>{"a", "b", "c"}));
}

/** @brief Test the 'index' method of the 'DataFrame' class. */
TEST(TestGetter, index)
{
    // DF EMPTY
    cdata_frame<int> df;
    EXPECT_TRUE(df.index().empty());

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    EXPECT_TRUE(df3.index().empty());

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    EXPECT_TRUE(df4.index().empty());

    // DF WITH INDEX AND DATA
    cdata_frame<int> df5(data, {"a", "b"});
    EXPECT_EQ(df5.index(), (std::vector<std::string>{"a", "b"}));

    // DF WITH KEYS, INDEX AND DATA
    cdata_frame<int> df6({"a", "b", "c"}, data, {"a", "b"});
    EXPECT_EQ(df6.index(), (std::vector<std::string>{"a", "b"}));
}

/** @brief Test the 'data' method of the 'DataFrame' class. */
TEST(TestGetter, data)
{
    // DF EMPTY
    cdata_frame<int> df;
    EXPECT_TRUE(df.data().is_empty());

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    EXPECT_EQ(df3.data(), data);

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    EXPECT_EQ(df4.data(), data);
}

/** @brief Test the 'rows' method of the 'DataFrame' class. */
TEST(TestGetter, rows)
{
    // DF EMPTY
    cdata_frame<int> df;
    EXPECT_THROW(df.rows("a"), std::invalid_argument);

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    EXPECT_THROW(df3.rows("a"), std::invalid_argument);

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    EXPECT_THROW(df4.rows("d"), std::invalid_argument);
    EXPECT_THROW(df4.rows({"a", "e"}), std::invalid_argument);

    // DF WITH INDEX AND DATA
    cdata_frame<int> df5(data, {"a", "b"});
    EXPECT_EQ(df5.rows("a"), cmatrix<int>({{1, 2, 3}}));
    EXPECT_EQ(df5.rows({"b", "a", "b"}), cmatrix<int>({{4, 5, 6}, {1, 2, 3}, {4, 5, 6}}));
    EXPECT_THROW(df5.rows("c"), std::invalid_argument);
    EXPECT_THROW(df5.rows({"a", "c"}), std::invalid_argument);

    // DF WITH KEYS, INDEX AND DATA
    cdata_frame<int> df6({"a", "b", "c"}, data, {"a", "b"});
    EXPECT_EQ(df6.rows("a"), cmatrix<int>({{1, 2, 3}}));
    EXPECT_EQ(df6.rows({"b", "a", "b"}), cmatrix<int>({{4, 5, 6}, {1, 2, 3}, {4, 5, 6}}));
    EXPECT_THROW(df6.rows("c"), std::invalid_argument);
    EXPECT_THROW(df6.rows({"a", "c"}), std::invalid_argument);
}

/** @brief Test the 'row' method of the 'DataFrame' class. */
TEST(TestGetter, columns)
{
    // DF EMPTY
    cdata_frame<int> df;
    EXPECT_THROW(df.columns("a"), std::invalid_argument);

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    EXPECT_THROW(df3.columns("a"), std::invalid_argument);

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    EXPECT_EQ(df4.columns("a"), cmatrix<int>({{1}, {4}}));
    EXPECT_EQ(df4.columns({"b", "c", "b"}), cmatrix<int>({{2, 3, 2}, {5, 6, 5}}));
    EXPECT_THROW(df4.columns("d"), std::invalid_argument);
    EXPECT_THROW(df4.columns({"a", "e"}), std::invalid_argument);

    // DF WITH INDEX AND DATA
    cdata_frame<int> df5(data, {"a", "b"});
    EXPECT_THROW(df5.columns("c"), std::invalid_argument);
    EXPECT_THROW(df5.columns({"a", "c"}), std::invalid_argument);

    // DF WITH KEYS, INDEX AND DATA
    cdata_frame<int> df6({"a", "b", "c"}, data, {"a", "b"});
    EXPECT_EQ(df6.columns("a"), cmatrix<int>({{1}, {4}}));
    EXPECT_EQ(df6.columns({"b", "a", "b"}), cmatrix<int>({{2, 1, 2}, {5, 4, 5}}));
}

// ==================================================
// SETTER

/** @brief Test the 'set_keys' method of the 'DataFrame' class. */
TEST(TestSetter, set_keys)
{
    // DF EMPTY
    cdata_frame<int> df;
    EXPECT_THROW(df.set_keys({"a", "b", "c"}), std::invalid_argument);

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    df3.set_keys({"a", "b", "c"});
    EXPECT_EQ(df3.keys(), (std::vector<std::string>{"a", "b", "c"}));

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    df4.set_keys({"d", "e", "f"});
    EXPECT_EQ(df4.keys(), (std::vector<std::string>{"d", "e", "f"}));
    df4.set_keys({});
    EXPECT_TRUE(df4.keys().empty());

    // DF WITH KEYS SIZE DIFFERENT FROM DATA SIZE
    EXPECT_THROW(df4.set_keys({"a", "b", "c", "d"}), std::invalid_argument);

    // DF WITH KEYS NOT UNIQUE
    EXPECT_THROW(df4.set_keys({"a", "b", "b"}), std::invalid_argument);
}

/** @brief Test the 'set_index' method of the 'DataFrame' class. */
TEST(TestSetter, set_index)
{
    // DF EMPTY
    cdata_frame<int> df;
    EXPECT_THROW(df.set_index({"a", "b", "c"}), std::invalid_argument);

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    df3.set_index({"a", "b"});
    EXPECT_EQ(df3.index(), (std::vector<std::string>{"a", "b"}));

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    df4.set_index({"d", "e"});
    EXPECT_EQ(df4.index(), (std::vector<std::string>{"d", "e"}));

    // DF WITH INDEX AND DATA
    cdata_frame<int> df5(data, {"a", "b"});
    df5.set_index({"d", "e"});
    EXPECT_EQ(df5.index(), (std::vector<std::string>{"d", "e"}));
    df5.set_index({});
    EXPECT_TRUE(df5.index().empty());

    // DF WITH INDEX SIZE DIFFERENT FROM DATA SIZE
    EXPECT_THROW(df4.set_index({"a", "b", "c"}), std::invalid_argument);

    // DF WITH INDEX NOT UNIQUE
    EXPECT_THROW(df4.set_index({"a", "a"}), std::invalid_argument);
}

/** @brief Test the 'set_data' method of the 'DataFrame' class. */
TEST(TestSetter, set_data)
{
    // DF EMPTY
    cdata_frame<int> df;
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    df.set_data(data);
    EXPECT_EQ(df.data(), data);

    // DF WITH DATA
    cmatrix<int> data2({{7, 8, 9}, {10, 11, 12}});
    cdata_frame<int> df3(data);
    df3.set_data(data2);
    EXPECT_EQ(df3.data(), data2);

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    df4.set_data(data2);
    EXPECT_EQ(df4.data(), data2);

    // DF WITH INDEX AND DATA
    cdata_frame<int> df5(data, {"a", "b"});
    df5.set_data(data2);
    EXPECT_EQ(df5.data(), data2);

    // DF WITH KEYS, INDEX AND DATA
    cdata_frame<int> df6({"a", "b", "c"}, data, {"a", "b"});
    df6.set_data(data2);
    EXPECT_EQ(df6.data(), data2);

    // DF WITH KEYS SIZE DIFFERENT FROM DATA SIZE
    EXPECT_THROW(df4.set_data(cmatrix<int>(3, 2)), std::invalid_argument);

    // DF WITH INDEX SIZE DIFFERENT FROM DATA SIZE
    EXPECT_THROW(df4.set_data(cmatrix<int>(3, 2)), std::invalid_argument);
}

// ==================================================
// MANIPULATION

/** @brief Test the 'insert_row' method of the 'DataFrame' class. */
TEST(TestManipulation, insert_row)
{
    // DF EMPTY
    cdata_frame<int> df;
    df.insert_row(0, {1, 2, 3}, "a");
    EXPECT_EQ(df.data(), (cmatrix<int>{{1, 2, 3}}));
    EXPECT_EQ(df.index().at(0), "a");

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    df3.insert_row(0, {7, 8, 9}, "a");
    EXPECT_EQ(df3.data(), (cmatrix<int>{{7, 8, 9}, {1, 2, 3}, {4, 5, 6}}));
    EXPECT_EQ(df3.index().at(0), "a");

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    df4.insert_row(0, {7, 8, 9}, "d");
    EXPECT_EQ(df4.data(), (cmatrix<int>{{7, 8, 9}, {1, 2, 3}, {4, 5, 6}}));
    EXPECT_EQ(df4.index().at(0), "d");

    // DF WITH KEYS SIZE DIFFERENT FROM DATA SIZE
    EXPECT_THROW(df3.insert_row(0, {7, 8, 9, 10}), std::invalid_argument);
    EXPECT_THROW(df4.insert_row(0, {7, 8}), std::invalid_argument);

    // DF WITH KEYS NOT UNIQUE
    EXPECT_THROW(df4.insert_row(0, {7, 8, 9}, "d"), std::runtime_error);
}

/** @brief Test the 'insert_column' method of the 'DataFrame' class. */
TEST(TestManipulation, insert_column)
{
    // DF EMPTY
    cdata_frame<int> df;
    df.insert_column(0, {1, 2, 3});
    EXPECT_EQ(df.data(), (cmatrix<int>{{1}, {2}, {3}}));
    df.insert_column(0, {4, 5, 6}, "d");
    EXPECT_EQ(df.data(), (cmatrix<int>{{4, 1}, {5, 2}, {6, 3}}));
    EXPECT_EQ(df.keys().at(0), "d");

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    df3.insert_column(0, {7, 8});
    EXPECT_EQ(df3.data(), (cmatrix<int>{{7, 1, 2, 3}, {8, 4, 5, 6}}));
    EXPECT_TRUE(df3.keys().empty());

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    df4.insert_column(0, {7, 8}, "d");
    EXPECT_EQ(df4.data(), (cmatrix<int>{{7, 1, 2, 3}, {8, 4, 5, 6}}));
    EXPECT_EQ(df4.keys().at(0), "d");

    // DF WITH KEYS SIZE DIFFERENT FROM DATA SIZE
    EXPECT_THROW(df3.insert_column(0, {7, 8, 9, 10}), std::invalid_argument);
    EXPECT_THROW(df4.insert_column(0, {7, 8, 9}), std::invalid_argument);

    // DF WITH KEYS NOT UNIQUE
    EXPECT_THROW(df4.insert_column(0, {7, 8}, "a"), std::runtime_error);
}

/** @brief Test the 'push_row_front' method of the 'DataFrame' class. */
TEST(TestManipulation, push_row_front)
{
    // DF EMPTY
    cdata_frame<int> df;
    df.push_row_front({1, 2, 3});
    EXPECT_EQ(df.data(), (cmatrix<int>{{1, 2, 3}}));

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    df3.push_row_front({7, 8, 9});
    EXPECT_EQ(df3.data(), (cmatrix<int>{{7, 8, 9}, {1, 2, 3}, {4, 5, 6}}));

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    df4.push_row_front({7, 8, 9});
    EXPECT_EQ(df4.data(), (cmatrix<int>{{7, 8, 9}, {1, 2, 3}, {4, 5, 6}}));

    // DF WITH KEYS SIZE DIFFERENT FROM DATA SIZE
    EXPECT_THROW(df4.push_row_front({7, 8}), std::invalid_argument);
    EXPECT_THROW(df4.push_row_front({7, 8, 9, 10}), std::invalid_argument);
}

/** @brief Test the 'push_row_back' method of the 'DataFrame' class. */
TEST(TestManipulation, push_row_back)
{
    // DF EMPTY
    cdata_frame<int> df;
    df.push_row_back({1, 2, 3});
    EXPECT_EQ(df.data(), (cmatrix<int>{{1, 2, 3}}));

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    df3.push_row_back({7, 8, 9});
    EXPECT_EQ(df3.data(), (cmatrix<int>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    df4.push_row_back({7, 8, 9});
    EXPECT_EQ(df4.data(), (cmatrix<int>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));

    // DF WITH KEYS SIZE DIFFERENT FROM DATA SIZE
    EXPECT_THROW(df4.push_row_back({7, 8}), std::invalid_argument);
    EXPECT_THROW(df4.push_row_back({7, 8, 9, 10}), std::invalid_argument);
}

/** @brief Test the 'push_col_front' method of the 'DataFrame' class. */
TEST(TestManipulation, push_col_front)
{
    // DF EMPTY
    cdata_frame<int> df;
    df.push_col_front({1, 2, 3});
    EXPECT_EQ(df.data(), (cmatrix<int>{{1}, {2}, {3}}));

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    df3.push_col_front({7, 8});
    EXPECT_EQ(df3.data(), (cmatrix<int>{{7, 1, 2, 3}, {8, 4, 5, 6}}));

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    df4.push_col_front({7, 8}, "d");
    EXPECT_EQ(df4.data(), (cmatrix<int>{{7, 1, 2, 3}, {8, 4, 5, 6}}));

    // DF WITH KEYS SIZE DIFFERENT FROM DATA SIZE
    EXPECT_THROW(df4.push_col_front({7, 8, 9}), std::invalid_argument);
    EXPECT_THROW(df4.push_col_front({7, 8, 9, 10}), std::runtime_error);
}

/** @brief Test the 'push_col_back' method of the 'DataFrame' class. */
TEST(TestManipulation, push_col_back)
{
    // DF EMPTY
    cdata_frame<int> df;
    df.push_col_back({1, 2, 3});
    EXPECT_EQ(df.data(), (cmatrix<int>{{1}, {2}, {3}}));

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    df3.push_col_back({7, 8});
    EXPECT_EQ(df3.data(), (cmatrix<int>{{1, 2, 3, 7}, {4, 5, 6, 8}}));

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    df4.push_col_back({7, 8}, "d");
    EXPECT_EQ(df4.data(), (cmatrix<int>{{1, 2, 3, 7}, {4, 5, 6, 8}}));

    // DF WITH KEYS SIZE DIFFERENT FROM DATA SIZE
    EXPECT_THROW(df4.push_col_back({7, 8, 9}), std::invalid_argument);
    EXPECT_THROW(df4.push_col_back({7, 8, 9, 10}), std::runtime_error);
}

/** @brief Test the 'remove_row' method of the 'DataFrame' class. */
TEST(TestManipulation, remove_row)
{
    // DF EMPTY
    cdata_frame<int> df;
    EXPECT_THROW(df.remove_row(0), std::out_of_range);

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    df3.remove_row(1);
    EXPECT_EQ(df3.data(), (cmatrix<int>{{1, 2, 3}}));
    df3.remove_row(0);
    EXPECT_TRUE(df3.data().is_empty());

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    df4.remove_row(0);
    EXPECT_EQ(df4.data(), (cmatrix<int>{{4, 5, 6}}));
    df4.remove_row(0);
    EXPECT_TRUE(df4.data().is_empty());

    // DF WITH INDEX AND DATA
    cdata_frame<int> df5(data, {"a", "b"});
    df5.remove_row(0);
    EXPECT_EQ(df5.data(), (cmatrix<int>{{4, 5, 6}}));
    df5.remove_row("b");
    EXPECT_TRUE(df5.data().is_empty());

    // DF WITH KEYS, INDEX AND DATA
    cdata_frame<int> df6({"a", "b", "c"}, data, {"a", "b"});
    df6.remove_row(0);
    EXPECT_EQ(df6.data(), (cmatrix<int>{{4, 5, 6}}));
    df6.remove_row("b");
    EXPECT_TRUE(df6.data().is_empty());
}

/** @brief Test the 'remove_column' method of the 'DataFrame' class. */
TEST(TestManipulation, remove_column)
{
    // DF EMPTY
    cdata_frame<int> df;
    EXPECT_THROW(df.remove_column(0), std::out_of_range);

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    df3.remove_column(1);
    EXPECT_EQ(df3.data(), (cmatrix<int>{{1, 3}, {4, 6}}));
    df3.remove_column(0);
    EXPECT_EQ(df3.data(), (cmatrix<int>{{3}, {6}}));
    df3.remove_column(0);
    EXPECT_TRUE(df3.data().is_empty());

    // DF WITH KEYS AND DATA
    cdata_frame<int> df4({"a", "b", "c"}, data);
    df4.remove_column(0);
    EXPECT_EQ(df4.data(), (cmatrix<int>{{2, 3}, {5, 6}}));
    df4.remove_column("c");
    EXPECT_EQ(df4.data(), (cmatrix<int>{{2}, {5}}));
    df4.remove_column(0);
    EXPECT_TRUE(df4.data().is_empty());

    // DF WITH INDEX AND DATA
    cdata_frame<int> df5(data, {"a", "b"});
    df5.remove_column(0);
    EXPECT_EQ(df5.data(), (cmatrix<int>{{2, 3}, {5, 6}}));
    df5.remove_column(1);
    EXPECT_EQ(df5.data(), (cmatrix<int>{{2}, {5}}));
    df5.remove_column(0);
    EXPECT_TRUE(df5.data().is_empty());

    // DF WITH KEYS, INDEX AND DATA
    cdata_frame<int> df6({"a", "b", "c"}, data, {"a", "b"});
    df6.remove_column(0);
    EXPECT_EQ(df6.data(), (cmatrix<int>{{2, 3}, {5, 6}}));
    df6.remove_column("c");
    EXPECT_EQ(df6.data(), (cmatrix<int>{{2}, {5}}));
    df6.remove_column(0);
    EXPECT_TRUE(df6.data().is_empty());
}

/** @brief Test the 'concatenate' method of the 'DataFrame' class. */
TEST(TestManipulation, concatenate)
{
    // DF EMPTY
    // CONCATENATE ROWS
    cdata_frame<int> df;
    cdata_frame<int> df2;
    df.concatenate(df2, 0);
    EXPECT_TRUE(df.data().is_empty());

    // CONCATENATE COLUMNS
    df.concatenate(df2, 1);
    EXPECT_TRUE(df.data().is_empty());

    // DF WITH DATA
    // CONCATENATE ROWS
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cmatrix<int> data2({{7, 8, 9}, {10, 11, 12}});
    cdata_frame<int> df3(data);
    cdata_frame<int> df4(data2);
    df3.concatenate(df4, 0);
    cmatrix<int> data3({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}});
    EXPECT_EQ(df3.data(), data3);

    // CONCATENATE COLUMNS
    df3 = cdata_frame<int>(data);
    df3.concatenate(df4, 1);
    cmatrix<int> data4({{1, 2, 3, 7, 8, 9}, {4, 5, 6, 10, 11, 12}});
    EXPECT_EQ(df3.data(), data4);

    // DF WITH KEYS AND DATA
    // CONCATENATE ROWS
    cdata_frame<int> df5({"a", "b", "c"}, data);
    cdata_frame<int> df6({"d", "e", "f"}, data2);
    EXPECT_THROW(df5.concatenate(df6, 0), std::invalid_argument);

    // CONCATENATE COLUMNS
    df5.concatenate(df6, 1);
    cdata_frame<int> df8({"a", "b", "c", "d", "e", "f"}, data4);
    EXPECT_EQ(df5.data(), df8.data());
    EXPECT_EQ(df5.keys(), df8.keys());

    // DF WITH INDEX AND DATA
    // CONCATENATE ROWS
    cdata_frame<int> df9(data, {"a", "b"});
    cdata_frame<int> df10(data2, {"c", "d"});
    df9.concatenate(df10, 0);
    cdata_frame<int> df11(data3, {"a", "b", "c", "d"});
    EXPECT_EQ(df9.data(), df11.data());
    EXPECT_EQ(df9.index(), df11.index());

    // CONCATENATE COLUMNS
    EXPECT_THROW(df9.concatenate(df10, 1), std::invalid_argument);

    // DF WITH KEYS, INDEX AND DATA WITH DIFFERENT KEYS AND INDEX
    // CONCATENATE ROWS
    cdata_frame<int> df13({"a", "b", "c"}, data, {"a", "b"});
    cdata_frame<int> df14({"d", "e", "f"}, data2, {"c", "d"});
    EXPECT_THROW(df13.concatenate(df14, 0), std::invalid_argument);

    // CONCATENATE COLUMNS
    EXPECT_THROW(df13.concatenate(df14, 1), std::invalid_argument);

    // DF WITH KEYS, INDEX AND DATA WITH SAME KEYS
    // CONCATENATE ROWS
    cdata_frame<int> df15({"a", "b", "c"}, data, {"a", "b"});
    cdata_frame<int> df16({"a", "b", "c"}, data2, {"c", "d"});
    df15.concatenate(df16, 0);
    cdata_frame<int> df17({"a", "b", "c"}, data3, {"a", "b", "c", "d"});
    EXPECT_EQ(df15.data(), df17.data());
    EXPECT_EQ(df15.keys(), df17.keys());
    EXPECT_EQ(df15.index(), df17.index());

    // DF WITH KEYS, INDEX AND DATA WITH SAME INDEX
    // CONCATENATE COLUMNS
    df15 = cdata_frame<int>({"a", "b", "c"}, data, {"a", "b"});
    df16 = cdata_frame<int>({"d", "e", "f"}, data2, {"a", "b"});
    df15.concatenate(df16, 1);
    cdata_frame<int> df18({"a", "b", "c", "d", "e", "f"}, data4, {"a", "b"});
    EXPECT_EQ(df15.data(), df18.data());
    EXPECT_EQ(df15.keys(), df18.keys());
    EXPECT_EQ(df15.index(), df18.index());

    // INVALID AXIS
    EXPECT_THROW(df13.concatenate(df14, 2), std::invalid_argument);

    // INVALID KEYS
    cdata_frame<int> df23({"a", "b", "c"}, data);
    cdata_frame<int> df24({"a", "b", "c"}, data2);
    EXPECT_THROW(df23.concatenate(df24, 1), std::invalid_argument);

    // INVALID INDEX
    cdata_frame<int> df25(data, {"a", "b"});
    cdata_frame<int> df26(data2, {"a", "b"});
    EXPECT_THROW(df25.concatenate(df26, 0), std::invalid_argument);

    // SELF CONCATENATE
    EXPECT_THROW(df25.concatenate(df25, 0), std::invalid_argument);
}

// ==================================================
// STATIC

/** @brief Test the 'read_csv' method of the 'DataFrame' class. */
TEST(TestStatic, read_csv)
{
    // DF EMPTY
    cdata_frame<std::string> df = cdata_frame<std::string>::read_csv("test/input/empty.csv");
    EXPECT_TRUE(df.keys().empty());
    EXPECT_TRUE(df.data().is_empty());

    // DF WITH KEYS
    cdata_frame<std::string> df2 = cdata_frame<std::string>::read_csv("test/input/header.csv");
    EXPECT_TRUE(df2.keys().empty());
    EXPECT_TRUE(df2.data().is_empty());

    // DF WITH DATA
    cdata_frame<std::string> df3 = cdata_frame<std::string>::read_csv("test/input/valid.csv", false);
    cmatrix<std::string> data({{"Doe", "John", "30", "New York", "50000"},
                               {"Smith", "Jane", "25", "Los Angeles", "60000"},
                               {"Johnson", "Michael", "35", "Chicago", "75000"}});
    EXPECT_TRUE(df3.keys().empty());
    EXPECT_EQ(df3.data(), data);

    cdata_frame<std::string> df3_2 = cdata_frame<std::string>::read_csv("test/input/valid_2.csv", false);
    cmatrix<std::string> data2({{"Lorem ipsum dolor sit ame"}});
    EXPECT_TRUE(df3_2.keys().empty());
    EXPECT_EQ(df3_2.data(), data2);

    // DF WITH KEYS AND DATA
    cdata_frame<std::string> df4 = cdata_frame<std::string>::read_csv("test/input/valid_with_header.csv");
    std::vector<std::string> header({"Nom", "Prénom", "Âge", "Ville", "Salaire"});
    EXPECT_EQ(df4.keys(), header);
    EXPECT_EQ(df4.data(), data);

    // DF WITH INDEX AND DATA
    cdata_frame<std::string> df5 = cdata_frame<std::string>::read_csv("test/input/valid_with_index.csv", false, true);
    cmatrix<std::string> data_2({{"42", "54", "36"},
                                 {"23", "65", "78"},
                                 {"12", "98", "45"},
                                 {"87", "23", "67"}});
    std::vector<std::string> index({"1", "2", "3", "4"});
    EXPECT_TRUE(df5.keys().empty());
    EXPECT_EQ(df5.index(), index);
    EXPECT_EQ(df5.data(), data_2);

    // DF WITH KEYS, INDEX AND DATA
    cdata_frame<std::string> df6 = cdata_frame<std::string>::read_csv("test/input/valid_header_index.csv", true, true);
    std::vector<std::string> header_2({"Nom", "Prénom", "Âge"});
    std::vector<std::string> index_2({"1", "2", "3", "4"});
    EXPECT_EQ(df6.keys(), header_2);
    EXPECT_EQ(df6.index(), index_2);
    EXPECT_EQ(df6.data(), data_2);

    // DELIMITER
    cdata_frame<std::string> df7 = cdata_frame<std::string>::read_csv("test/input/valid_delimiter.csv", false, false, ';');
    EXPECT_EQ(df7.data(), data);

    // INVALID PATH
    EXPECT_THROW(cdata_frame<std::string>::read_csv("test/input/no_path.csv"), std::invalid_argument);

    // INVALID EXTENSION
    EXPECT_THROW(cdata_frame<std::string>::read_csv("test/input/file.txt"), std::invalid_argument);

    // INVVALID DATA
    EXPECT_THROW(cdata_frame<std::string>::read_csv("test/input/invalid_data.csv"), std::invalid_argument);

    // INVALID HEADER
    EXPECT_THROW(cdata_frame<std::string>::read_csv("test/input/invalid_header.csv"), std::invalid_argument);

    // KEYS NOT UNIQUE
    EXPECT_THROW(cdata_frame<std::string>::read_csv("test/input/invalid_header_2.csv"), std::invalid_argument);

    // INVALID INDEX
    EXPECT_THROW(cdata_frame<std::string>::read_csv("test/input/invalid_index.csv", false, true), std::invalid_argument);

    // INDEX NOT UNIQUE
    EXPECT_THROW(cdata_frame<std::string>::read_csv("test/input/invalid_index_2.csv", false, true), std::invalid_argument);

    // INVALID KEYS, INDEX AND DATA
    EXPECT_THROW(cdata_frame<std::string>::read_csv("test/input/invalid_header_and_index.csv", false, true), std::invalid_argument);
}

/** @brief Test the 'merge' method of the 'DataFrame' class. */
TEST(TestStatic, merge)
{
    // DF EMPTY
    cdata_frame<int> df;
    cdata_frame<int> df2;
    cdata_frame<int> df3 = cdata_frame<int>::merge(df, df2);
    EXPECT_TRUE(df3.data().is_empty());

    // DF WITH DATA
    // CONCATENATE ROWS
    cdata_frame<int> df5({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df6({{7, 8, 9}, {10, 11, 12}});
    cdata_frame<int> df7 = cdata_frame<int>::merge(df5, df6, 0);
    cdata_frame<int> expected_df({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}});
    EXPECT_EQ(df7.data(), expected_df.data());

    // CONCATENATE COLUMNS
    df7 = cdata_frame<int>::merge(df5, df6, 1);
    cdata_frame<int> expected_df2({{1, 2, 3, 7, 8, 9}, {4, 5, 6, 10, 11, 12}});
    EXPECT_EQ(df7.data(), expected_df2.data());
    EXPECT_TRUE(df7.keys().empty());
    EXPECT_TRUE(df7.index().empty());

    // DF WITH KEYS AND DATA
    // CONCATENATE ROWS
    cdata_frame<int> df8({"a", "b", "c"}, {{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df9({"d", "e", "f"}, {{7, 8, 9}, {10, 11, 12}});
    EXPECT_THROW(cdata_frame<int>::merge(df8, df9, 0), std::invalid_argument);

    // CONCATENATE COLUMNS
    df7 = cdata_frame<int>::merge(df8, df9, 1);
    cdata_frame<int> expected_df3({"a", "b", "c", "d", "e", "f"}, {{1, 2, 3, 7, 8, 9}, {4, 5, 6, 10, 11, 12}});
    EXPECT_EQ(df7.data(), expected_df3.data());
    EXPECT_EQ(df7.keys(), expected_df3.keys());
    EXPECT_TRUE(df7.index().empty());

    // DF WITH INDEX AND DATA
    // CONCATENATE ROWS
    cdata_frame<int> df10({{1, 2, 3}, {4, 5, 6}}, {"a", "b"});
    cdata_frame<int> df11({{7, 8, 9}, {10, 11, 12}}, {"c", "d"});
    df7 = cdata_frame<int>::merge(df10, df11, 0);
    cdata_frame<int> expected_df4({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}}, {"a", "b", "c", "d"});
    EXPECT_EQ(df7.data(), expected_df4.data());
    EXPECT_TRUE(df7.keys().empty());
    EXPECT_EQ(df7.index(), expected_df4.index());

    // CONCATENATE COLUMNS
    EXPECT_THROW(cdata_frame<int>::merge(df10, df11, 1), std::invalid_argument);

    // DF WITH KEYS, INDEX AND DATA WITH DIFFERENT KEYS AND INDEX
    // CONCATENATE ROWS
    cdata_frame<int> df12({"a", "b", "c"}, {{1, 2, 3}, {4, 5, 6}}, {"a", "b"});
    cdata_frame<int> df13({"d", "e", "f"}, {{7, 8, 9}, {10, 11, 12}}, {"c", "d"});
    EXPECT_THROW(cdata_frame<int>::merge(df12, df13, 0), std::invalid_argument);

    // CONCATENATE COLUMNS
    EXPECT_THROW(cdata_frame<int>::merge(df12, df13, 1), std::invalid_argument);

    // DF WITH KEYS, INDEX AND DATA WITH SAME KEYS
    // CONCATENATE ROWS
    cdata_frame<int> df14({"a", "b", "c"}, {{1, 2, 3}, {4, 5, 6}}, {"a", "b"});
    cdata_frame<int> df15({"a", "b", "c"}, {{7, 8, 9}, {10, 11, 12}}, {"c", "d"});
    df7 = cdata_frame<int>::merge(df14, df15, 0);
    cdata_frame<int> expected_df5({"a", "b", "c"}, {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}}, {"a", "b", "c", "d"});
    EXPECT_EQ(df7.data(), expected_df5.data());
    EXPECT_EQ(df7.keys(), expected_df5.keys());
    EXPECT_EQ(df7.index(), expected_df5.index());

    // DF WITH KEYS, INDEX AND DATA WITH SAME INDEX
    // CONCATENATE COLUMNS
    cdata_frame<int> df16({"a", "b", "c"}, {{1, 2, 3}, {4, 5, 6}}, {"a", "b"});
    cdata_frame<int> df17({"d", "e", "f"}, {{7, 8, 9}, {10, 11, 12}}, {"a", "b"});
    df7 = cdata_frame<int>::merge(df16, df17, 1);
    cdata_frame<int> expected_df6({"a", "b", "c", "d", "e", "f"}, {{1, 2, 3, 7, 8, 9}, {4, 5, 6, 10, 11, 12}}, {"a", "b"});
    EXPECT_EQ(df7.data(), expected_df6.data());
    EXPECT_EQ(df7.keys(), expected_df6.keys());
    EXPECT_EQ(df7.index(), expected_df6.index());
}

// ==================================================
// GENERAL

/** @brief Test the 'copy' method of the 'DataFrame' class. */
TEST(TestGeneral, copy)
{
    // DF EMPTY
    cdata_frame<int> df;
    cdata_frame<int> df2 = df.copy();
    EXPECT_TRUE(df2.data().is_empty());

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    cdata_frame<int> df4 = df3.copy();
    EXPECT_EQ(df4.data(), data);

    // DF WITH KEYS AND DATA
    cdata_frame<int> df5({"a", "b", "c"}, data);
    cdata_frame<int> df6 = df5.copy();
    EXPECT_EQ(df6.data(), data);
    EXPECT_EQ(df6.keys(), df5.keys());

    // DF WITH INDEX AND DATA
    cdata_frame<int> df7(data, {"a", "b"});
    cdata_frame<int> df8 = df7.copy();
    EXPECT_EQ(df8.data(), data);
    EXPECT_EQ(df8.index(), df7.index());

    // DF WITH KEYS, INDEX AND DATA
    cdata_frame<int> df9({"a", "b", "c"}, data, {"a", "b"});
    cdata_frame<int> df10 = df9.copy();
    EXPECT_EQ(df10.data(), data);
    EXPECT_EQ(df10.keys(), df9.keys());
    EXPECT_EQ(df10.index(), df9.index());
}

TEST(TestGeneral, clear)
{
    // DF EMPTY
    cdata_frame<int> df;
    df.clear();
    EXPECT_TRUE(df.data().is_empty());
    EXPECT_TRUE(df.index().empty());
    EXPECT_TRUE(df.keys().empty());

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df2 = cdata_frame<int>(data);
    df2.clear();
    EXPECT_TRUE(df2.data().is_empty());
    EXPECT_TRUE(df2.index().empty());
    EXPECT_TRUE(df2.keys().empty());

    // DF WITH KEYS AND DATA
    cdata_frame<int> df3({"a", "b", "c"}, data);
    df3.clear();
    EXPECT_TRUE(df3.data().is_empty());
    EXPECT_TRUE(df3.index().empty());
    EXPECT_TRUE(df3.keys().empty());

    // DF WITH INDEX AND DATA
    cdata_frame<int> df4(data, {"a", "b"});
    df4.clear();
    EXPECT_TRUE(df4.data().is_empty());
    EXPECT_TRUE(df4.index().empty());
    EXPECT_TRUE(df4.keys().empty());

    // DF WITH KEYS, INDEX AND DATA
    cdata_frame<int> df5({"a", "b", "c"}, data, {"a", "b"});
    df5.clear();
    EXPECT_TRUE(df5.data().is_empty());
    EXPECT_TRUE(df5.index().empty());
    EXPECT_TRUE(df5.keys().empty());
}

// ==================================================
// OPERATORS

/** @brief Test the 'operator==' method of the 'DataFrame' class. */
TEST(TestOperators, operator_equal)
{
    // DF EMPTY
    cdata_frame<int> df;
    cdata_frame<int> df2;
    EXPECT_TRUE(df == df2);

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    cdata_frame<int> df4(data);
    EXPECT_TRUE(df3 == df4);

    // DF WITH KEYS AND DATA
    cdata_frame<int> df5({"a", "b", "c"}, data);
    cdata_frame<int> df6({"a", "b", "c"}, data);
    EXPECT_TRUE(df5 == df6);

    // DF WITH INDEX AND DATA
    cdata_frame<int> df7(data, {"a", "b"});
    cdata_frame<int> df8(data, {"a", "b"});
    EXPECT_TRUE(df7 == df8);

    // DF WITH KEYS, INDEX AND DATA
    cdata_frame<int> df9({"a", "b", "c"}, data, {"a", "b"});
    cdata_frame<int> df10({"a", "b", "c"}, data, {"a", "b"});
    EXPECT_TRUE(df9 == df10);

    // DF WITH KEYS, INDEX AND DATA WITH DIFFERENT KEYS AND INDEX
    cdata_frame<int> df11({"a", "b", "c"}, data, {"a", "b"});
    cdata_frame<int> df12({"d", "e", "f"}, data, {"c", "d"});
    EXPECT_FALSE(df11 == df12);

    // DF WITH KEYS, INDEX AND DATA WITH SAME KEYS
    cdata_frame<int> df13({"a", "b", "c"}, data, {"a", "b"});
    cdata_frame<int> df14({"a", "b", "c"}, data, {"c", "d"});
    EXPECT_FALSE(df13 == df14);
}

/** @brief Test the 'operator!=' method of the 'DataFrame' class. */
TEST(TestOperators, operator_not_equal)
{
    // DF EMPTY
    cdata_frame<int> df;
    cdata_frame<int> df2;
    EXPECT_FALSE(df != df2);

    // DF WITH DATA
    cmatrix<int> data({{1, 2, 3}, {4, 5, 6}});
    cdata_frame<int> df3(data);
    cdata_frame<int> df4(data);
    EXPECT_FALSE(df3 != df4);

    // DF WITH KEYS AND DATA
    cdata_frame<int> df5({"a", "b", "c"}, data);
    cdata_frame<int> df6({"a", "b", "c"}, data);
    EXPECT_FALSE(df5 != df6);

    // DF WITH INDEX AND DATA
    cdata_frame<int> df7(data, {"a", "b"});
    cdata_frame<int> df8(data, {"a", "b"});
    EXPECT_FALSE(df7 != df8);

    // DF WITH KEYS, INDEX AND DATA
    cdata_frame<int> df9({"a", "b", "c"}, data, {"a", "b"});
    cdata_frame<int> df10({"a", "b", "c"}, data, {"a", "b"});
    EXPECT_FALSE(df9 != df10);

    // DF WITH KEYS, INDEX AND DATA WITH DIFFERENT KEYS AND INDEX
    cdata_frame<int> df11({"a", "b", "c"}, data, {"a", "b"});
    cdata_frame<int> df12({"d", "e", "f"}, data, {"c", "d"});
    EXPECT_TRUE(df11 != df12);

    // DF WITH KEYS, INDEX AND DATA WITH SAME KEYS
    cdata_frame<int> df13({"a", "b", "c"}, data, {"a", "b"});
    cdata_frame<int> df14({"a", "b", "c"}, data, {"c", "d"});
    EXPECT_TRUE(df13 != df14);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
