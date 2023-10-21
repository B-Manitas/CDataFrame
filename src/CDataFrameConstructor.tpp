/**
 * @file CDataFrameConstructor.tpp
 * @brief File containing the constructor and destructor of the 'DataFrame' class.
 *
 * @see CDataFrame.hpp
 * @defgroup constructor
 */

// ==================================================
// Constructors

template <class T>
cdata_frame<T>::cdata_frame() {}

template <class T>
cdata_frame<T>::cdata_frame(const cmatrix<T> &data) : cmatrix<T>(data) {}

template <class T>
cdata_frame<T>::cdata_frame(const std::vector<std::string> &keys) : m_keys(keys) {}

template <class T>
cdata_frame<T>::cdata_frame(const std::vector<std::string> &keys, const cmatrix<T> &data) : cmatrix<T>(data)
{
    if (keys.size() != data.dim_h())
        throw std::invalid_argument("The number of keys must be equal to the number of columns of the data.");

    m_keys = keys;
}

// ==================================================
// Destructor
template <class T>
cdata_frame<T>::~cdata_frame() {}
