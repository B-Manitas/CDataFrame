/**
 * @file CDataFrameSetter.tpp
 * @brief File containing the implementation of setters of the 'DataFrame' class.
 *
 * @see CDataFrame.hpp
 * @defgroup setter
 */

// ==================================================
// SETTER

template <class T>
void cdata_frame<T>::set_keys(const std::vector<std::string> &keys)
{
    // Check if the number of keys is different from the number of columns
    if (not keys.empty() && keys.size() != cmatrix<T>::dim_h())
        throw std::invalid_argument("The number of keys must be equal to the number of columns. Actual: " +
                                    std::to_string(keys.size()) +
                                    ", Expected: " +
                                    std::to_string(cmatrix<T>::dim_h()) +
                                    ".");

    // Check if the keys are unique
    if (std::set<std::string>(keys.begin(), keys.end()).size() != keys.size())
        throw std::invalid_argument("The keys must be unique.");

    m_keys = keys;
}

template <class T>
void cdata_frame<T>::set_index(const std::vector<std::string> &index)
{
    // Check if the number of index is different from the number of rows
    if (not index.empty() && index.size() != cmatrix<T>::dim_v())
        throw std::invalid_argument("The number of index must be equal to the number of rows. Actual: " +
                                    std::to_string(index.size()) +
                                    ", Expected: " +
                                    std::to_string(cmatrix<T>::dim_v()) +
                                    ".");

    // Check if the index are unique
    if (std::set<std::string>(index.begin(), index.end()).size() != index.size())
        throw std::invalid_argument("The index must be unique.");

    m_index = index;
}

template <class T>
void cdata_frame<T>::set_data(const cmatrix<T> &data)
{
    // Check if the number of keys is different from the number of columns
    if (not m_keys.empty() && data.dim_h() != m_keys.size())
        throw std::invalid_argument("The number of keys must be equal to the number of columns.");

    // Check if the number of index is different from the number of rows
    if (not m_index.empty() && data.dim_v() != m_index.size())
        throw std::invalid_argument("The number of index must be equal to the number of rows.");

    cmatrix<T>::operator=(data);
}
