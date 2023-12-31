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
    if (not keys.empty() && keys.size() != cmatrix<T>::width())
        throw std::invalid_argument("The number of keys must be equal to the number of columns. Actual: " +
                                    std::to_string(keys.size()) +
                                    ", Expected: " +
                                    std::to_string(cmatrix<T>::width()) +
                                    ".");

    // Check if the keys are unique
    __check_unique(keys, "keys");

    m_keys = keys;
}

template <class T>
void cdata_frame<T>::set_index(const std::vector<std::string> &index)
{
    // Check if the number of index is different from the number of rows
    if (not index.empty() && index.size() != cmatrix<T>::height())
        throw std::invalid_argument("The number of index must be equal to the number of rows. Actual: " +
                                    std::to_string(index.size()) +
                                    ", Expected: " +
                                    std::to_string(cmatrix<T>::height()) +
                                    ".");

    // Check if the index are unique
    __check_unique(index, "index");

    m_index = index;
}

template <class T>
void cdata_frame<T>::set_data(const cmatrix<T> &data)
{
    // Check if the number of keys is different from the number of columns
    if (not m_keys.empty() && data.width() != m_keys.size())
        throw std::invalid_argument("The number of keys must be equal to the number of columns.");

    // Check if the number of index is different from the number of rows
    if (not m_index.empty() && data.height() != m_index.size())
        throw std::invalid_argument("The number of index must be equal to the number of rows.");

    cmatrix<T>::operator=(data);
}
