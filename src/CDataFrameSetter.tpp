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
void CDataFrame<T>::set_keys(const std::vector<std::string> &keys)
{
    if (not m_data.isEmpty() && keys.size() != m_data.dim_h())
        throw std::invalid_argument("The number of keys must be equal to the number of columns.");

    m_keys = keys;
}