/**
 * @file CDataFrame.tpp
 * @brief File containing the general methods of the 'DataFrame' class.
 *
 * @see CDataFrame.hpp
 * @defgroup general
 */

// ==================================================
// GENERAL

template <class T>
std::vector<std::string> cdata_frame<T>::__generate_uid_keys(const std::string &prefix) const
{
    // Create string vector with the size of the number of columns
    std::vector<std::string> uid_keys(cmatrix<T>::dim_h(), "");

    // Fill the vector with the prefix and the uid
    for (size_t i = 0; i < cmatrix<T>::dim_h(); i++)
        uid_keys[i] = prefix + std::to_string(i);

    return uid_keys;
}
