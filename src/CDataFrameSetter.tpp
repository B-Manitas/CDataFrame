/**
 * @file CDataFrameSetter.tpp
 * @brief File containing the implementation of setters of the 'DataFrame' class.
 *
 * @see CDataFrame.hpp
 * @defgroup setter
 */

// ==================================================
// Setter

template <class T>
void cdata_frame<T>::set_keys(const std::vector<std::string> &keys)
{
    if (not cmatrix<T>::is_empty() && keys.size() != cmatrix<T>::dim_h())
        throw std::invalid_argument("The number of keys must be equal to the number of columns.");

    if (std::set<std::string>(keys.begin(), keys.end()).size() != keys.size())
        throw std::invalid_argument("The keys must be unique.");

    m_keys = keys;
}

template <class T>
void cdata_frame<T>::set_data(const cmatrix<T> &data)
{
    if (not m_keys.empty() && data.dim_h() != m_keys.size())
        throw std::invalid_argument("The number of keys must be equal to the number of columns.");

    cmatrix<T>::operator=(data);
}
