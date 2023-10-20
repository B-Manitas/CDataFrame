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
std::vector<std::string> CDataFrame<T>::keys() const
{
    return m_keys;
}

template <class T>
std::vector<std::string> &CDataFrame<T>::keys()
{
    return m_keys;
}

template <class T>
cmatrix<T> CDataFrame<T>::data() const
{
    return m_data;
}