/**
 * @file CDataFrameManipulation.tpp
 * @brief File containing the implementation of manipulation methods of the 'DataFrame' class.
 *
 * @see CDataFrame.hpp
 * @defgroup manipulation
 */

// ==================================================
// Insert

template <class T>
void cdata_frame<T>::insert_row(const size_t &pos, const std::vector<T> &val)
{
    if (not m_keys.empty() and val.size() != m_keys.size())
        throw std::invalid_argument("The number of columns is different from the number of keys.");
    
    cmatrix<T>::insert_row(pos, val);
}
