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

#include "../lib/CMatrix/include/CMatrix.hpp"

/**
 * @brief Main template class for the 'CDataFrame' library.
 * 
 * @tparam T The type of the data.
 */
template <typename T>
class CDataFrame
{
private:
    std::vector<std::string> m_keys;
    cmatrix<T> m_data;

public:
    // Constructors
    /**
     * @brief Construct a new CDataFrame object.
     */
    CDataFrame();
    /**
     * @brief Destroy the CDataFrame object.
     */
    ~CDataFrame();

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
