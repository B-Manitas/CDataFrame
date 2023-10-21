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
void cdata_frame<T>::push_col_front(const std::vector<T> &val, const std::string &key)
{
    insert_column(0, val, key);
}

template <class T>
void cdata_frame<T>::push_col_back(const std::vector<T> &val, const std::string &key)
{
    insert_column(cmatrix<T>::dim_h(), val, key);
}

// ==================================================
// REMOVE

template <class T>
void cdata_frame<T>::__remove_key(const size_t &pos)
{
    if (not m_keys.empty())
        m_keys.erase(m_keys.begin() + pos);
    
    else if (cmatrix<T>::is_empty())
        m_keys.clear();
}

template <class T>
void cdata_frame<T>::remove_row(const size_t &pos)
{
    cmatrix<T>::remove_row(pos);
    __remove_key(pos);
}

template <class T>
void cdata_frame<T>::remove_column(const size_t &pos)
{
    cmatrix<T>::remove_column(pos);
    __remove_key(pos);
}
