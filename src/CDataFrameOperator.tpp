/**
 * @file CDataFrame.tpp
 * @brief This file contains the implementation of operators and methods of the 'CDataFrame' class.

 * @see CDataFrame.hpp
 * @defgroup check
 */

// ==================================================
// LOGICAL OPERATORS

template <class T>
bool cdata_frame<T>::operator==(const cdata_frame<T> &df) const
{
    return cmatrix<T>::operator==(df) && m_keys == df.m_keys && m_index == df.m_index;
}

template <class T>
bool cdata_frame<T>::operator!=(const cdata_frame<T> &df) const
{
    return not(*this == df);
}

// ==================================================
// FRIEND OPERATORS

template <class U>
std::ostream &operator<<(std::ostream &out, const cdata_frame<U> &df)
{
    out << df.__print(std::integral_constant < bool, std::is_fundamental<U>::value or std::is_same<U, std::string>::value > {},
                      df.height());

    return out;
}
