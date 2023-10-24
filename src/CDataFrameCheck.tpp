/**
 * @file CDataFrameCheck.tpp
 *
 * @brief File containing the implementation of check methods of the 'DataFrame' class.
 *
 * @see CDataFrame.hpp
 * @defgroup check
 */

// ==================================================
// CHECK

template <class T>
void cdata_frame<T>::__check_unique_keys(const std::string &key) const
{
    // Check if the key doesn't already exist
    if (not m_keys.empty() && std::find(m_keys.begin(), m_keys.end(), key) != m_keys.end())
        throw std::runtime_error("The key '" + key + "' already exists.");
}

template <class T>
void cdata_frame<T>::__check_unique_index(const std::string &index) const
{
    // Check if the index doesn't already exist
    if (not m_index.empty() && std::find(m_index.begin(), m_index.end(), index) != m_index.end())
        throw std::runtime_error("The index '" + index + "' already exists.");
}

template <class T>
void cdata_frame<T>::__check_valid_row(const std::vector<T> &val) const
{
    // Check if the number of columns is different from the number of keys
    if (not m_keys.empty() && val.size() != m_keys.size())
        throw std::invalid_argument("The number of columns is different from the number of keys. Actual: " +
                                    std::to_string(val.size()) +
                                    ", Expected: " +
                                    std::to_string(m_keys.size()) +
                                    ".");
}

template <class T>
bool cdata_frame<T>::has_keys() const
{
    return not m_keys.empty();
}

template <class T>
bool cdata_frame<T>::has_index() const
{
    return not m_index.empty();
}