/**
 * @file CDataFrameManipulation.tpp
 * @brief File containing the implementation of manipulation methods of the 'DataFrame' class.
 *
 * @see CDataFrame.hpp
 * @defgroup manipulation
 */

// ==================================================
// INSERT

template <class T>
void cdata_frame<T>::insert_row(const size_t &pos, const std::vector<T> &val)
{
    if (not m_keys.empty() and val.size() != m_keys.size())
        throw std::invalid_argument("The number of columns is different from the number of keys.");

    cmatrix<T>::insert_row(pos, val);
}

template <class T>
void cdata_frame<T>::insert_column(const size_t &pos, const std::vector<T> &val, const std::string &key)
{
    if (not m_keys.empty() and key.empty())
        throw std::invalid_argument("The key is empty.");

    if (m_keys.empty())
        m_keys = __generate_uid_keys();

    m_keys.insert(m_keys.begin() + pos, key);
    cmatrix<T>::insert_column(pos, val);
}

// ==================================================
// PUSH

template <class T>
void cdata_frame<T>::push_row_front(const std::vector<T> &val)
{
    insert_row(0, val);
}

template <class T>
void cdata_frame<T>::push_row_back(const std::vector<T> &val)
{
    insert_row(cmatrix<T>::dim_v(), val);
}

template <class T>
void cdata_frame<T>::push_column_front(const std::vector<T> &val, const std::string &key)
{
    insert_column(0, val, key);
}

template <class T>
void cdata_frame<T>::push_column_back(const std::vector<T> &val, const std::string &key)
{
    insert_column(cmatrix<T>::dim_h(), val, key);
}