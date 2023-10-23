/**
 * @file CDataFrameGetter.tpp
 * @brief File containing the implementation of getters of the 'DataFrame' class.
 *
 * @see CDataFrame.hpp
 * @defgroup getter
 */

// ==================================================
// GETTER

template <class T>
std::vector<std::string> cdata_frame<T>::keys() const
{
    return m_keys;
}

template <class T>
std::vector<std::string> cdata_frame<T>::index() const
{
    return m_index;
}

template <class T>
cmatrix<T> cdata_frame<T>::data() const
{
    return cmatrix<T>::copy();
}

// ==================================================
// ACCESSOR

template <class T>
cmatrix<T> cdata_frame<T>::rows(const std::string &index) const
{
    return cmatrix<T>::rows(__get_index_pos(index));
}

template <class T>
cmatrix<T> cdata_frame<T>::rows(const std::initializer_list<std::string> &index) const
{
    return rows(std::vector<std::string>(index));
}

template <class T>
cmatrix<T> cdata_frame<T>::rows(const std::vector<std::string> &index) const
{
    // Store the ids of the index
    std::vector<size_t> rows;

    // For each index, get the corresponding position id
    for (const auto &idx : index)
        rows.push_back(__get_index_pos(idx));

    return cmatrix<T>::rows(rows);
}

template <class T>
cmatrix<T> cdata_frame<T>::columns(const std::string &key) const
{
    return cmatrix<T>::columns(__get_key_pos(key));
}

template <class T>
cmatrix<T> cdata_frame<T>::columns(const std::initializer_list<std::string> &keys) const
{
    return columns(std::vector<std::string>(keys));
}

template <class T>
cmatrix<T> cdata_frame<T>::columns(const std::vector<std::string> &keys) const
{
    // Store the ids of the keys
    std::vector<size_t> columns;

    // For each key, get the corresponding position id
    for (const auto &key : keys)
        columns.push_back(__get_key_pos(key));

    return cmatrix<T>::columns(columns);
}

// ==================================================
// PRIVATE

template <class T>
size_t cdata_frame<T>::__get_key_pos(const std::string &key) const
{
    // Find the id of the key
    auto it = std::find(m_keys.begin(), m_keys.end(), key);

    // If the key does not exist, throw an exception
    if (it == m_keys.end())
        throw std::invalid_argument("The key '" + key + "' does not exist.");

    // Return the id of the key
    return it - m_keys.begin();
}

template <class T>
size_t cdata_frame<T>::__get_index_pos(const std::string &index) const
{
    // Find the id of the index
    auto it = std::find(m_index.begin(), m_index.end(), index);

    // If the index does not exist, throw an exception
    if (it == m_index.end())
        throw std::invalid_argument("The index '" + index + "' does not exist.");

    // Return the id of the index
    return it - m_index.begin();
}
