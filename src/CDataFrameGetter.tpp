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
cmatrix<T> cdata_frame<T>::data() const
{
    return cmatrix<T>::copy();
}

// ==================================================
// ACCESSOR

template <class T>
cmatrix<T> cdata_frame<T>::columns(const std::string &key) const
{
    return cmatrix<T>::columns(__id_of_key(key));
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
        columns.push_back(__id_of_key(key));

    return cmatrix<T>::columns(columns);
}

// ==================================================
// PRIVATE

template <class T>
size_t cdata_frame<T>::__id_of_key(const std::string &key) const
{
    // Find the id of the key
    auto it = std::find(m_keys.begin(), m_keys.end(), key);

    // If the key does not exist, throw an exception
    if (it == m_keys.end())
        throw std::invalid_argument("The key '" + key + "' does not exist.");

    // Return the id of the key
    return it - m_keys.begin();
}
