/**
 * @file CDataFrameGetter.tpp
 * @brief File containing the implementation of getters of the 'DataFrame' class.
 *
 * @see CDataFrame.hpp
 * @defgroup getter
 */

// ==================================================
// Getter

template <class T>
std::vector<std::string> cdata_frame<T>::keys() const
{
    return m_keys;
}

template <class T>
cmatrix<T> cdata_frame<T>::data() const
{
    return cmatrix<T>::copy();
}
