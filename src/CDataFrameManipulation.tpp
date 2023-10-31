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
void cdata_frame<T>::insert_row(const size_t &pos, const std::vector<T> &val, const std::string &index)
{
    if (m_index.empty())
    {
        // User want insert an index
        if (index != "")
        {
            // Check if the index doesn't already exist
            __check_unique_index(index);

            // Generate unique index and insert the new index
            m_index = __generate_uids(cmatrix<T>::height(), index);
            m_index.insert(m_index.begin() + pos, index);
        }
    }

    // User want insert empty index
    else
    {
        // Check if the index doesn't already exist
        __check_unique_index(index);

        // Insert the new index
        m_index.insert(m_index.begin() + pos, index);
    }

    cmatrix<T>::insert_row(pos, val);
}

template <class T>
void cdata_frame<T>::insert_column(const size_t &pos, const std::vector<T> &val, const std::string &key)
{
    if (m_keys.empty())
    {
        // User want insert a key
        if (key != "")
        {
            // Check if the key doesn't already exist
            __check_unique_keys(key);

            // Generate unique keys and insert the new key
            m_keys = __generate_uids(cmatrix<T>::width(), key);
            m_keys.insert(m_keys.begin() + pos, key);
        }
    }

    // User want insert empty key
    else
    {
        // Check if the key doesn't already exist
        __check_unique_keys(key);

        // Insert the new key
        m_keys.insert(m_keys.begin() + pos, key);
    }

    cmatrix<T>::insert_column(pos, val);
}

template <class T>
void cdata_frame<T>::concatenate(const cdata_frame<T> &df, const short unsigned int &axis)
{
    if (this == &df)
        throw std::invalid_argument("Cannot concatenate a data frame with itself.");

    // Axis 0: concatenate the rows
    if (axis == 0)
    {
        if (m_keys != df.m_keys)
            throw std::invalid_argument("The keys of the two data frames must be the same.");

        // Concatenate the matrix
        cmatrix<T>::concatenate(df, 0);

        // Concatenate the index
        std::vector<std::string> index_merged = df.index();
        index_merged.insert(index_merged.begin(), m_index.begin(), m_index.end());
        set_index(index_merged);
    }

    // Axis 1: concatenate the columns
    else if (axis == 1)
    {
        if (m_index != df.m_index)
            throw std::invalid_argument("The indexes of the two data frames must be the same.");

        // Concatenate the matrix
        cmatrix<T>::concatenate(df, 1);

        // Concatenate the keys
        std::vector<std::string> keys_merged = df.keys();
        keys_merged.insert(keys_merged.begin(), m_keys.begin(), m_keys.end());
        set_keys(keys_merged);
    }

    else
        throw std::invalid_argument("Invalid axis. Axis must be 0 or 1.");
}

// ==================================================
// PUSH

template <class T>
void cdata_frame<T>::push_row_front(const std::vector<T> &val, const std::string &index)
{
    insert_row(0, val, index);
}

template <class T>
void cdata_frame<T>::push_row_back(const std::vector<T> &val, const std::string &index)
{
    insert_row(cmatrix<T>::height(), val, index);
}

template <class T>
void cdata_frame<T>::push_col_front(const std::vector<T> &val, const std::string &key)
{
    insert_column(0, val, key);
}

template <class T>
void cdata_frame<T>::push_col_back(const std::vector<T> &val, const std::string &key)
{
    insert_column(cmatrix<T>::width(), val, key);
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
void cdata_frame<T>::__remove_index(const size_t &pos)
{
    if (not m_index.empty())
        m_index.erase(m_index.begin() + pos);

    else if (cmatrix<T>::is_empty())
        m_index.clear();
}

template <class T>
void cdata_frame<T>::remove_row(const std::string &index)
{
    const size_t pos = __get_index_pos(index);
    remove_row(pos);
}

template <class T>
void cdata_frame<T>::remove_row(const size_t &pos)
{
    cmatrix<T>::remove_row(pos);
    __remove_index(pos);
}

template <class T>
void cdata_frame<T>::remove_column(const std::string &key)
{
    const size_t pos = __get_key_pos(key);
    remove_column(pos);
}

template <class T>
void cdata_frame<T>::remove_column(const size_t &pos)
{
    cmatrix<T>::remove_column(pos);
    __remove_key(pos);
}
