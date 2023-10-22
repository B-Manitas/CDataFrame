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

TEST(TestConstructor, Constructor)
{
    // DF EMPTY
    cdata_frame<int> df;
    EXPECT_EQ(df.keys().size(), 0);
    EXPECT_EQ(df.index().size(), 0);
    EXPECT_EQ(df.data().dim_h(), 0);
    EXPECT_EQ(df.data().dim_v(), 0);

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
}

// ==================================================
// SETTER

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

TEST(TestManipulation, insert_row)
{
    // DF EMPTY
    cdata_frame<int> df;
    df.insert_row(0, {1, 2, 3});
    EXPECT_EQ(df.data(), (cmatrix<int>{{1, 2, 3}}));

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
    EXPECT_THROW(df4.insert_column(0, {7, 8, 9}), std::invalid_argument);
    EXPECT_THROW(df4.insert_column(0, {7, 8, 9, 10}), std::runtime_error);

    // DF WITH KEYS NOT UNIQUE
    EXPECT_THROW(df4.insert_column(0, {7, 8}, "a"), std::runtime_error);
}

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
}

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
    df4.remove_column(1);
    EXPECT_EQ(df4.data(), (cmatrix<int>{{2}, {5}}));
    df4.remove_column(0);
    EXPECT_TRUE(df4.data().is_empty());
}

// ==================================================
// STATIC

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
    cdata_frame<std::string> df3 = cdata_frame<std::string>::read_csv("test/input/valid.csv", ',', false);
    cmatrix<std::string> data({{"Doe", "John", "30", "New York", "50000"},
                               {"Smith", "Jane", "25", "Los Angeles", "60000"},
                               {"Johnson", "Michael", "35", "Chicago", "75000"}});
    EXPECT_TRUE(df3.keys().empty());
    EXPECT_EQ(df3.data(), data);

    cdata_frame<std::string> df3_2 = cdata_frame<std::string>::read_csv("test/input/valid_2.csv", ',', false);
    cmatrix<std::string> data2({{"Lorem ipsum dolor sit ame"}});
    EXPECT_TRUE(df3_2.keys().empty());
    EXPECT_EQ(df3_2.data(), data2);

    // DF WITH KEYS AND DATA
    cdata_frame<std::string> df4 = cdata_frame<std::string>::read_csv("test/input/valid_with_header.csv");
    std::vector<std::string> header({"Nom", "Prénom", "Âge", "Ville", "Salaire"});
    EXPECT_EQ(df4.keys(), header);
    EXPECT_EQ(df4.data(), data);

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
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
