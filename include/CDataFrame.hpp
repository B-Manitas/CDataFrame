/**
 * @file CDataFrame.hpp
 * @brief File containing the main template class for the 'CDataFrame' library.
 *
 * @author Manitas Bahri <https://github.com/b-manitas>
 * @date 2023
 * @license MIT License
 */

#pragma once

#include <fstream>
#include <initializer_list>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "../lib/CMatrix/include/CMatrix.hpp"

/**
 * @brief Main template class for the 'CDataFrame' library.
 *
 * @tparam T The type of the data.
 */
template <typename T>
class cdata_frame : public cmatrix<T>
{
private:
    std::vector<std::string> m_keys = std::vector<std::string>();
    std::vector<std::string> m_index = std::vector<std::string>();

    // GETTER
    /**
     * @brief Get the position id of the key.
     *
     * @param key The key to get the index.
     * @return size_t The position id of the key.
     * @throw std::invalid_argument If the key doesn't exist.
     *
     * @ingroup getter
     */
    size_t __get_key_pos(const std::string &key) const;
    /**
     * @brief Get the position id of the index.
     *
     * @param index The index to get the index.
     * @return size_t The position id of the index.
     * @throw std::invalid_argument If the index doesn't exist.
     *
     * @ingroup getter
     */
    size_t __get_index_pos(const std::string &index) const;

    // MANIPULATION
    /**
     * @brief Remove a key at the given position.
     *
     * @param pos The position of the key.
     *
     * @ingroup manipulation
     */
    void __remove_key(const size_t &pos);
    /**
     * @brief Remove a key at the given key.
     *
     * @param key The key of the key.
     * @throw std::invalid_argument If the key doesn't exist.
     *
     * @ingroup manipulation
     */
    void __remove_index(const size_t &pos);

    // General
    /**
     * @brief Generate unique index.
     *
     * @param len The length of the vector to generate.
     * @param not_in The index to not generate. Default is "".
     * @return std::vector<std::string> The unique keys.
     *
     * @ingroup general
     */
    std::vector<std::string> __generate_uids(const size_t len, const std::string &not_in = "") const;
    /**
     * @brief Compute the maximum length of the stream for a vector of data.
     *
     * @param data The data to compute the maximum length of the stream.
     * @param initial The initial value of the maximum length. Default is 0.
     * @return short unsigned int The maximum length of the stream of the data.
     *
     * @ingroup general
     */
    template <class U>
    short unsigned int __stream_width(const std::vector<U> data, const int &initial = 0) const;
    /**
     * @brief Compute the maximum length of the stream of the data.
     *
     * @return std::vector<short unsigned int> The maximum length of the stream of the data.
     *
     * @ingroup general
     */
    std::vector<short unsigned int> __stream_widths_vec() const;
    /**
     * @brief Print the border of the data frame.
     *
     * @param widths The widths of the data frame.
     * @param left The left border of the data frame.
     * @param middle The middle border of the data frame.
     * @param right The right border of the data frame.
     * @param line The line of the data frame. Default is "─".
     * @param index The right border of the index. Default is "".
     *
     * @ingroup general
     */
    void __print_border(const std::vector<short unsigned int> &widths, const std::string &left, const std::string &middle, const std::string &right, const std::string &line = "─", const std::string &index = "") const;
    /**
     * @brief Print the top border of the data frame.
     *
     * @param widths The widths of the data frame.
     *
     * @ingroup general
     */
    void __print_border_top(const std::vector<short unsigned int> &widths) const;
    /**
     * @brief Print the middle border of the data frame.
     *
     * @param widths The widths of the data frame.
     *
     * @ingroup general
     */
    void __print_border_middle(const std::vector<short unsigned int> &widths) const;
    /**
     * @brief Print the bottom border of the data frame.
     *
     * @param widths The widths of the data frame.
     *
     * @ingroup general
     */
    void __print_border_bottom(const std::vector<short unsigned int> &widths) const;
    /**
     * @brief Print a row of the data frame.
     *
     * @param widths The widths stream for each element of the row.
     * @param data The data of the row.
     * @param index The index of the row.
     *
     * @ingroup general
     */
    template <class U>
    void __print_row(const std::vector<short unsigned int> &widths, const std::vector<U> &data, const std::string &index = "") const;
    /**
     * @brief Print the data frame.
     *
     * @param n The number of rows to print.
     * @param true_type The type T is a primitive type.
     *
     * @ingroup general
     */
    void __print(const unsigned int &n, std::true_type) const;
    /**
     * @brief Print the data frame.
     *
     * @param n The number of rows to print.
     * @param false_type The type T is not a primitive type.
     *
     * @ingroup general
     */
    void __print(const unsigned int &n, std::false_type) const;

    // CHECK
    /**
     * @brief Check if the keys are unique.
     *
     * @throw std::runtime_error If the keys are not unique.
     *
     * @ingroup check
     */
    void __check_unique_keys(const std::string &key) const;
    /**
     * @brief Check if the index are unique.
     *
     * @throw std::runtime_error If the index are not unique.
     *
     * @ingroup check
     */
    void __check_unique_index(const std::string &index) const;
    /**
     * @brief Check if the row is valid.
     *
     * @param val The row to check.
     * @throw std::invalid_argument If the number of columns of the row is different from the number of columns of the data.
     *
     * @ingroup check
     */
    void __check_valid_row(const std::vector<T> &val) const;
    /**
     * @brief Check if a vector of data is unique.
     *
     * @param vec The vector of data to check.
     * @param label The label of the vector of data for the error message.
     * @throw std::runtime_error If the vector of data is not unique.
     *
     * @ingroup check
     */
    void __check_unique(const std::vector<std::string> &vec, const std::string &label) const;

    // STATIC
    /**
     * @brief Check if a file exists.
     *
     * @param path The path of the file.
     * @return true If the file exists.
     * @return false If the file doesn't exist.
     *
     * @ingroup static
     */
    static bool __is_file_exist(const std::string &path);
    /**
     * @brief Check if a file has expected extension.
     *
     * @param path The path of the file.
     * @param extension The expected extension.
     *
     * @return true If the file has expected extension.
     * @return false If the file doesn't have expected extension.
     *
     * @ingroup static
     */
    static bool __has_expected_extension(const std::string &path, const std::string &extension);
    /**
     * @brief Open a file.
     *
     * @param path The path of the file.
     * @return std::fstream& The file opened.
     * @throw std::invalid_argument If the file doesn't exist.
     * @throw std::runtime_error If the file can't be opened.
     *
     * @ingroup static
     */
    static std::fstream __open_file(const std::string &path);
    /**
     * @brief Parse a line of a csv file.
     *
     * @param line The line to parse.
     * @param sep The separator of the csv file.
     * @param index If the csv file has an index.
     * @param index_name The name of the index. Default is nullptr.
     * @return std::vector<std::string> The line parsed.
     *
     * @ingroup static
     */
    static std::vector<std::string> __parse_csv_line(const std::string &line, const char &sep, const bool &index, std::string *index_name = nullptr);
    /**
     * @brief Count the number of characters of a input.
     *
     * @param input The input to count the number of characters.
     * @return short unsigned int The number of characters of the input.
     *
     * @ingroup static
     */
    template <class U>
    static short unsigned int __count_characters(const U &input);

public:
    // CONSTRUCTOR
    /**
     * @brief Construct a new CDataFrame object.
     *
     * @note The data, keys and index are empty.
     * @example
     * cdata_frame<int> df = cdata_frame<int>();
     */
    cdata_frame();
    /**
     * @brief Construct a new CDataFrame object.
     *
     * @param data The cmatrix object containing the data.
     *
     * @note The keys and index are empty.
     * @example
     * cdata_frame<int> df = cdata_frame<int>(cmatrix<int>({{1, 2}, {3, 4}}));
     */
    cdata_frame(const cmatrix<T> &data);
    /**
     * @brief Construct a new CDataFrame object.
     *
     * @param keys The keys of the data.
     * @param data The cmatrix object containing the data.
     * @throw std::invalid_argument If the number of keys is different from the number of columns of the data.
     *
     * @note The number of keys must be equal to the number of columns of the data.
     * @note The index are empty.
     * @example
     * cdata_frame<int> df = cdata_frame<int>({"key1", "key2"}, cmatrix<int>({{1, 2}, {3, 4}}));
     */
    cdata_frame(const std::vector<std::string> &keys, const cmatrix<T> &data);
    /**
     * @brief Construct a new CDataFrame object.
     *
     * @param index The index of the data.
     * @param data The cmatrix object containing the data.
     * @throw std::invalid_argument If the number of index is different from the number of rows of the data.
     *
     * @note The number of index must be equal to the number of rows of the data.
     * @note The keys are empty.
     * @example
     * cdata_frame<int> df = cdata_frame<int>(cmatrix<int>({{1, 2}, {3, 4}}), {"index1", "index2"});
     */
    cdata_frame(const cmatrix<T> &data, const std::vector<std::string> &index);
    /**
     * @brief Construct a new CDataFrame object.
     *
     * @param keys The keys of the data.
     * @param index The index of the data.
     * @param data The cmatrix object containing the data.
     * @throw std::invalid_argument If the number of keys is different from the number of columns of the data.
     * @throw std::invalid_argument If the number of index is different from the number of rows of the data.
     *
     * @note The number of keys must be equal to the number of columns of the data.
     * @note The number of index must be equal to the number of rows of the data.
     * @example
     * cdata_frame<int> df = cdata_frame<int>({"key1", "key2"}, cmatrix<int>({{1, 2}, {3, 4}}), {"index1", "index2"});
     */
    cdata_frame(const std::vector<std::string> &keys, const cmatrix<T> &data, const std::vector<std::string> &index);
    /**
     * @brief Destroy the CDataFrame object.
     */
    ~cdata_frame();

    // GETTER
    /**
     * @brief Get the keys.
     *
     * @return std::vector<std::string>
     *
     * @ingroup getter
     */
    std::vector<std::string> keys() const;
    /**
     * @brief Get the index.
     *
     * @return std::vector<std::string>
     *
     * @ingroup getter
     */
    std::vector<std::string> index() const;
    /**
     * @brief Get the data.
     *
     * @return cmatrix::CMatrix<T>
     *
     * @ingroup getter
     */
    cmatrix<T> data() const;
    /**
     * @brief Get the row corresponding to the given index.
     *
     * @param index The index of the row to get.
     * @return std::matrix<T> The row corresponding to the given index.
     *
     * @ingroup getter
     */
    cmatrix<T> rows(const std::string &index) const;
    /**
     * @brief Get the column corresponding to the given index.
     *
     * @param index The index of the column to get.
     * @return std::matrix<T> The column corresponding to the given index.
     *
     * @ingroup getter
     */
    cmatrix<T> rows(const std::initializer_list<std::string> &index) const;
    /**
     * @brief Get the column corresponding to the given index.
     *
     * @param index The index of the column to get.
     * @return std::matrix<T> The column corresponding to the given index.
     *
     * @ingroup getter
     */
    cmatrix<T> rows(const std::vector<std::string> &index) const;
    /**
     * @brief Get the columns corresponding to the given keys.
     *
     * @param keys The keys of the columns to get.
     * @return cmatrix<T> The columns corresponding to the given keys.
     *
     * @ingroup getter
     */
    cmatrix<T> columns(const std::string &key) const;
    /**
     * @brief Get the columns corresponding to the given keys.
     *
     * @param keys The keys of the columns to get.
     * @return cmatrix<T> The columns corresponding to the given keys.
     *
     * @ingroup getter
     */
    cmatrix<T> columns(const std::initializer_list<std::string> &keys) const;
    /**
     * @brief Get the columns corresponding to the given keys.
     *
     * @param keys The keys of the columns to get.
     * @return cmatrix<T> The columns corresponding to the given keys.
     *
     * @ingroup getter
     */
    cmatrix<T> columns(const std::vector<std::string> &keys) const;

    // SETTER
    /**
     * @brief Set the keys.
     *
     * @param keys
     * @throw std::invalid_argument If the number of keys is different from the number of columns of the data.
     * @throw std::invalid_argument If the keys are not unique.
     *
     * @note If data is empty, the keys are empty.
     * @ingroup setter
     * @example
     * cdata_frame<int> df = cdata_frame<int>();
     * df.set_keys({"key1", "key2"});
     */
    void set_keys(const std::vector<std::string> &keys);
    /**
     * @brief Set the index.
     *
     * @param index
     * @throw std::invalid_argument If the number of index is different from the number of rows of the data.
     * @throw std::invalid_argument If the index are not unique.
     *
     * @note If data is empty, the index are empty.
     * @ingroup setter
     * @example
     * cdata_frame<int> df = cdata_frame<int>();
     * df.set_index({"index1", "index2"});
     */
    void set_index(const std::vector<std::string> &index);
    /**
     * @brief Set the data.
     *
     * @param data
     *
     * @ingroup setter
     * @example
     * cdata_frame<int> df = cdata_frame<int>();
     * df.set_data(cmatrix<int>({{1, 2}, {3, 4}}));
     */
    void set_data(const cmatrix<T> &data);

    // MANIPULATION
    /**
     * @brief Insert a row at the given position.
     *
     * @param pos The position of the row.
     * @param val The row to insert.
     * @param index The index of the row. Default is "".
     * @throw std::invalid_argument If the number of columns of the row is different from the number of columns of the data.
     *
     * @note If the index are empty, the index will be generated.
     * @ingroup manipulation
     * @example
     * cdata_frame<int> df = cdata_frame<int>();
     * df.insert_row(0, {1, 2}, "index1");
     */
    void insert_row(const size_t &pos, const std::vector<T> &val, const std::string &index = "");
    /**
     * @brief Insert a column at the given position.
     *
     * @param pos The position of the column.
     * @param val The column to insert.
     * @param key The key of the column. Default is "".
     * @throw std::invalid_argument If the number of rows of the column is different from the number of rows of the data.
     *
     * @note If the keys are empty, the keys will be generated.
     * @ingroup manipulation
     * @example
     * cdata_frame<int> df = cdata_frame<int>();
     * df.insert_column(0, {1, 2}, "key1");
     */
    void insert_column(const size_t &pos, const std::vector<T> &val, const std::string &key = "");
    /**
     * @brief Concatenate two data frames.
     *
     * @param df The data frame to concatenate.
     * @param axis The axis to concatenate. 0 for rows and 1 for columns. Default is 0.
     * @throw std::invalid_argument If the data frame is concatenated with itself.
     * @throw std::invalid_argument If the keys of the two data frames are not the same (axis 0).
     * @throw std::invalid_argument If the index of the two data frames are not the same (axis 1).
     * @throw std::invalid_argument If the axis is not 0 or 1.
     * @throw std::runtime_error If index are not unique (axis 0).
     * @throw std::runtime_error If keys are not unique (axis 1).
     *
     * @ingroup manipulation
     * @example
     * cdata_frame<int> df1 = cdata_frame<int>({"key1", "key2"}, cmatrix<int>({{1, 2}, {3, 4}}), {"index1", "index2"});
     * cdata_frame<int> df2 = cdata_frame<int>({"key1", "key2"}, cmatrix<int>({{5, 6}, {7, 8}}), {"index3", "index4"});
     * df1.concatenate(df2);
     */
    void concatenate(const cdata_frame<T> &df, const short unsigned int &axis = 0);
    /**
     * @brief Push a row at the front of the data.
     *
     * @param val The row to push.
     * @param index The index of the row. Default is "".
     * @throw std::invalid_argument If the number of columns of the row is different from the number of columns of the data.
     *
     * @ingroup manipulation
     * @example
     * cdata_frame<int> df = cdata_frame<int>();
     * df.push_row_front({1, 2}, "index1");
     */
    void push_row_front(const std::vector<T> &val, const std::string &index = "");
    /**
     * @brief Push a row at the back of the data.
     *
     * @param val The row to push.
     * @param index The index of the row. Default is "".
     * @throw std::invalid_argument If the number of columns of the row is different from the number of columns of the data.
     *
     * @ingroup manipulation
     * @example
     * cdata_frame<int> df = cdata_frame<int>();
     * df.push_row_back({1, 2}, "index1");
     */
    void push_row_back(const std::vector<T> &val, const std::string &index = "");
    /**
     * @brief Push a column at the front of the data.
     *
     * @param val The column to push.
     * @param key The key of the column. Default is "".
     * @throw std::invalid_argument If the number of rows of the column is different from the number of rows of the data.
     *
     * @ingroup manipulation
     * @example
     * cdata_frame<int> df = cdata_frame<int>();
     * df.push_col_front({1, 2}, "key1");
     */
    void push_col_front(const std::vector<T> &val, const std::string &key = "");
    /**
     * @brief Push a column at the back of the data.
     *
     * @param val The column to push.
     * @param key The key of the column. Default is "".
     * @throw std::invalid_argument If the number of rows of the column is different from the number of rows of the data.
     *
     * @ingroup manipulation
     * @example
     * cdata_frame<int> df = cdata_frame<int>();
     * df.push_col_back({1, 2}, "key1");
     */
    void push_col_back(const std::vector<T> &val, const std::string &key = "");
    /**
     * @brief Remove a row at the given position.
     *
     * @param pos The position of the row.
     *
     * @ingroup manipulation
     * @example
     * cdata_frame<int> df = cdata_frame<int>(cmatrix<int>({{1, 2}, {3, 4}}), {"index1", "index2"});
     * df.remove_row(0);
     */
    void remove_row(const size_t &pos);
    /**
     * @brief Remove a row at the given index.
     *
     * @param index The index of the row.
     * @throw std::invalid_argument If the index doesn't exist.
     *
     * @ingroup manipulation
     * @example
     * cdata_frame<int> df = cdata_frame<int>(cmatrix<int>({{1, 2}, {3, 4}}), {"index1", "index2"});
     * df.remove_row("index1");
     */
    void remove_row(const std::string &index);
    /**
     * @brief Remove a column at the given position.
     *
     * @param pos The position of the column.
     *
     * @ingroup manipulation
     * @example
     * cdata_frame<int> df = cdata_frame<int>({"key1", "key2"}, cmatrix<int>({{1, 2}, {3, 4}}));
     * df.remove_column(0);
     */
    void remove_column(const size_t &pos);
    /**
     * @brief Remove a column at the given key.
     *
     * @param key The key of the column.
     * @throw std::invalid_argument If the key doesn't exist.
     *
     * @ingroup manipulation
     * @example
     * cdata_frame<int> df = cdata_frame<int>({"key1", "key2"}, cmatrix<int>({{1, 2}, {3, 4}}));
     * df.remove_column("key1");
     */
    void remove_column(const std::string &key);

    // CHECK
    /**
     * @brief Check if the keys are empty.
     *
     * @return true If the keys are empty.
     * @return false If the keys are not empty.
     *
     * @ingroup check
     */
    bool has_keys() const;
    /**
     * @brief Check if the indexes are empty.
     *
     * @return true If the indexes are empty.
     * @return false If the indexes are not empty.
     *
     * @ingroup check
     */
    bool has_index() const;

    // STATIC
    /**
     * @brief Read a csv file.
     *
     * @param path The path of the csv file.
     * @param header If the csv file has a header. Default is true.
     * @param index If the csv file has an index. Default is false.
     * @param sep The separator of the csv file. Default is ','.
     * @return cdata_frame<std::string> The data frame read.
     *
     * @note If the header is enabled, the first line of the csv file will be used as keys.
     * @note If the data frame is empty, keys and index are empty.
     * @ingroup general
     * @example
     * cdata_frame<std::string> df = cdata_frame<std::string>::read_csv("data.csv", true, false, ',');
     */
    static cdata_frame<std::string> read_csv(const std::string &path, const bool &header = true, const bool &index = false, const char &sep = ',');
    /**
     * @brief Merge two data frames.
     *
     * @param df1 The first data frame to merge.
     * @param df2 The second data frame to merge.
     * @param axis The axis to merge. 0 for rows and 1 for columns. Default is 0.
     * @return cdata_frame<T> The data frame merged.
     * @throw std::invalid_argument If the data frame is concatenated with itself.
     * @throw std::invalid_argument If the keys of the two data frames are not the same (axis 0).
     * @throw std::invalid_argument If the index of the two data frames are not the same (axis 1).
     * @throw std::invalid_argument If the axis is not 0 or 1.
     * @throw std::runtime_error If index are not unique (axis 0).
     * @throw std::runtime_error If keys are not unique (axis 1).
     *
     * @ingroup static
     * @example
     * cdata_frame<int> df1 = cdata_frame<int>({"key1", "key2"}, cmatrix<int>({{1, 2}, {3, 4}}), {"index1", "index2"});
     * cdata_frame<int> df2 = cdata_frame<int>({"key1", "key2"}, cmatrix<int>({{5, 6}, {7, 8}}), {"index3", "index4"});
     * cdata_frame<int> df3 = cdata_frame<int>::merge(df1, df2);
     */
    static cdata_frame<T> merge(const cdata_frame<T> &df1, const cdata_frame<T> &df2, const unsigned int &axis = 0);

    // GENERAL
    /**
     * @brief Print the data frame.
     *
     * @param n The number of rows to print. Default is 5.
     *
     * @ingroup general
     */
    void print(const unsigned int &n = 5) const;
    /**
     * @brief Copy the data frame.
     *
     * @return cdata_frame<T> The copy of the data frame.
     *
     * @ingroup general
     */
    cdata_frame<T> copy() const;
    /**
     * @brief Cleat the data frame.
     *
     * @ingroup general
     */
    void clear();

    // OPERATOR
    /**
     * @brief The equality operator.
     *
     * @param df The data frame to compare.
     * @return true If the data frames are equal.
     * @return false If the data frames are not equal.
     *
     * @ingroup operator
     */
    bool operator==(const cdata_frame<T> &df) const;
    /**
     * @brief The inequality operator.
     *
     * @param df The data frame to compare.
     * @return true If the data frames are not equal.
     * @return false If the data frames are equal.
     *
     * @ingroup operator
     */
    bool operator!=(const cdata_frame<T> &df) const;
};

#include "../src/CDataFrameCheck.tpp"
#include "../src/CDataFrameConstructor.tpp"
#include "../src/CDataFrameGetter.tpp"
#include "../src/CDataFrameManipulation.tpp"
#include "../src/CDataFrameOperator.tpp"
#include "../src/CDataFrameSetter.tpp"
#include "../src/CDataFrameStatic.tpp"
#include "../src/CDataFrame.tpp"
