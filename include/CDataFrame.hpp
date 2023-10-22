/**
 * @file CDataFrame.hpp
 * @brief File containing the main template class for the 'CDataFrame' library.
 *
 * @author Manitas Bahri <https://github.com/b-manitas>
 * @date 2023
 * @license MIT License
 */

#pragma once

#include <initializer_list>
#include <set>
#include <string>
#include <tuple>
#include <initializer_list>
#include <fstream>
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
    size_t __id_of_key(const std::string &key) const;

    // MANIPULATION
    /**
     * @brief Remove a key at the given position.
     *
     * @param pos The position of the key.
     *
     * @ingroup manipulation
     */
    void __remove_key(const size_t &pos);

    // General
    /**
     * @brief Generate unique keys.
     *
     * @param prefix The prefix of the keys. Default is 'key_'.
     * @return std::vector<std::string> The unique keys.
     *
     * @ingroup general
     */
    std::vector<std::string> __generate_uid_keys(const std::string &prefix = "key_") const;

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
     * @brief Check if the row is valid.
     *
     * @param val The row to check.
     * @throw std::invalid_argument If the number of columns of the row is different from the number of columns of the data.
     *
     * @ingroup check
     */
    void __check_valid_row(const std::vector<T> &val) const;

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
     * @return std::vector<std::string> The line parsed.
     *
     * @ingroup static
     */
    static std::vector<std::string> __parse_csv_line(std::string line, const char sep);

public:
    // CONSTRUCTOR
    /**
     * @brief Construct a new CDataFrame object.
     */
    cdata_frame();
    /**
     * @brief Construct a new CDataFrame object.
     *
     * @param data The cmatrix object containing the data.
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
     */
    cdata_frame(const std::vector<std::string> &keys, const cmatrix<T> &data);
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
     * @brief Get the data.
     *
     * @return cmatrix::CMatrix<T>
     *
     * @ingroup getter
     */
    cmatrix<T> data() const;
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
     *
     * @ingroup setter
     */
    void set_keys(const std::vector<std::string> &keys);
    /**
     * @brief Set the data.
     *
     * @param data
     *
     * @ingroup setter
     */
    void set_data(const cmatrix<T> &data);

    // MANIPULATION
    /**
     * @brief Insert a row at the given position.
     *
     * @param pos The position of the row.
     * @param val The row to insert.
     * @throw std::invalid_argument If the number of columns of the row is different from the number of columns of the data.
     *
     * @ingroup manipulation
     */
    void insert_row(const size_t &pos, const std::vector<T> &val);
    /**
     * @brief Insert a column at the given position.
     *
     * @param pos The position of the column.
     * @param val The column to insert.
     * @param key The key of the column.
     * @throw std::invalid_argument If the number of rows of the column is different from the number of rows of the data.
     *
     * @note If the keys are empty, the keys will be generated.
     * @ingroup manipulation
     */
    void insert_column(const size_t &pos, const std::vector<T> &val, const std::string &key = "");
    /**
     * @brief Push a row at the front of the data.
     *
     * @param val The row to push.
     * @throw std::invalid_argument If the number of columns of the row is different from the number of columns of the data.
     *
     * @ingroup manipulation
     */
    void push_row_front(const std::vector<T> &val);
    /**
     * @brief Push a row at the back of the data.
     *
     * @param val The row to push.
     * @throw std::invalid_argument If the number of columns of the row is different from the number of columns of the data.
     *
     * @ingroup manipulation
     */
    void push_row_back(const std::vector<T> &val);
    /**
     * @brief Push a column at the front of the data.
     *
     * @param val The column to push.
     * @param key The key of the column.
     * @throw std::invalid_argument If the number of rows of the column is different from the number of rows of the data.
     *
     * @ingroup manipulation
     */
    void push_col_front(const std::vector<T> &val, const std::string &key = "");
    /**
     * @brief Push a column at the back of the data.
     *
     * @param val The column to push.
     * @param key The key of the column.
     * @throw std::invalid_argument If the number of rows of the column is different from the number of rows of the data.
     *
     * @ingroup manipulation
     */
    void push_col_back(const std::vector<T> &val, const std::string &key = "");
    /**
     * @brief Remove a row at the given position.
     *
     * @param pos The position of the row.
     *
     * @ingroup manipulation
     */
    void remove_row(const size_t &pos);
    /**
     * @brief Remove a column at the given position.
     *
     * @param pos The position of the column.
     *
     * @ingroup manipulation
     */
    void remove_column(const size_t &pos);

    // STATIC
    /**
     * @brief Read a csv file.
     *
     * @param path The path of the csv file.
     * @param sep The separator of the csv file. Default is ','.
     * @param header If the csv file has a header. Default is true.
     *
     * @ingroup general
     */
    static cdata_frame<T> read_csv(const std::string &path, const char &sep = ',', const bool &header = true);
};

#include "../src/CDataFrameCheck.tpp"
#include "../src/CDataFrameConstructor.tpp"
#include "../src/CDataFrameGetter.tpp"
#include "../src/CDataFrameManipulation.tpp"
#include "../src/CDataFrameSetter.tpp"
#include "../src/CDataFrameStatic.tpp"
#include "../src/CDataFrame.tpp"
