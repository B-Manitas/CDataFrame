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
    if (not cmatrix<T>::is_empty() && keys.size() != cmatrix<T>::dim_h())
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
void cdata_frame<T>::set_data(const cmatrix<T> &data)
{
    // Check if the number of keys is different from the number of columns
    if (not m_keys.empty() && data.dim_h() != m_keys.size())
        throw std::invalid_argument("The number of keys must be equal to the number of columns.");

    cmatrix<T>::operator=(data);
}
