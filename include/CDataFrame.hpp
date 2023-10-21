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
     */
    cdata_frame(const std::vector<std::string> &keys);
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
     * @ingroup manipulation
     */
    void insert_column(const size_t &pos, const std::vector<T> &val, const std::string &key = "");
};

#include "../src/CDataFrameConstructor.tpp"
#include "../src/CDataFrameGetter.tpp"
#include "../src/CDataFrameManipulation.tpp"
#include "../src/CDataFrameSetter.tpp"
#include "../src/CDataFrame.tpp"
