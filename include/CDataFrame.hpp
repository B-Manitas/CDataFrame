/**
 * @file CDataFrame.hpp
 * @brief File containing the main template class for the 'CDataFrame' library.
 * 
 * @author Manitas Bahri <https://github.com/b-manitas>
 * @date 2023
 * @license MIT License
 */

#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <initializer_list>

#include "../lib/CMatrix/include/CMatrix.hpp"

/**
 * @brief Main template class for the 'CDataFrame' library.
 * 
 * @tparam T The type of the data.
 */
template <typename T>
class cdata_frame
{
private:
    std::vector<std::string> m_keys = std::vector<std::string>();
    cmatrix<T> m_data = cmatrix<T>();

public:
    // Constructors
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

    // Getters
    /**
     * @brief Get the keys.
     * 
     * @return std::vector<std::string>
     * 
     * @ingroup getter
     */
    std::vector<std::string> keys() const;
    /**
     * @brief Get a reference to the keys.
     * 
     * @return std::vector<std::string>&
     * 
     * @ingroup getter
     */
    std::vector<std::string> &keys();
    /**
     * @brief Get the data.
     * 
     * @return cmatrix::CMatrix<T>
     * 
     * @ingroup getter
     */
    cmatrix<T> data() const;

    // Setters
    /**
     * @brief Set the keys.
     * 
     * @param keys 
     * 
     * @ingroup setter
     */
    void set_keys(const std::vector<std::string> &keys);
};

#include "../src/CDataFrame.tpp"
#include "../src/CDataFrameConstructor.tpp"
#include "../src/CDataFrameGetter.tpp"
#include "../src/CDataFrameSetter.tpp"
