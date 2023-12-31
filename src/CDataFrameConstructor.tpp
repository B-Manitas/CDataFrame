/**
 * @file CDataFrameConstructor.tpp
 * @brief File containing the constructor and destructor of the 'DataFrame' class.
 *
 * @see CDataFrame.hpp
 * @defgroup constructor
 */

// ==================================================
// CONSTRUCTOR

template <class T>
cdata_frame<T>::cdata_frame() {}

template <class T>
cdata_frame<T>::cdata_frame(const cmatrix<T> &data)
{
    set_data(data);
}

template <class T>
cdata_frame<T>::cdata_frame(const std::vector<std::string> &keys, const cmatrix<T> &data)
{
    set_data(data);
    set_keys(keys);
}

template <class T>
cdata_frame<T>::cdata_frame(const cmatrix<T> &data, const std::vector<std::string> &index)
{
    set_data(data);
    set_index(index);
}

template <class T>
cdata_frame<T>::cdata_frame(const std::vector<std::string> &keys, const cmatrix<T> &data, const std::vector<std::string> &index)
{
    set_data(data);
    set_keys(keys);
    set_index(index);
}

// ==================================================
// Destructor
template <class T>
cdata_frame<T>::~cdata_frame() {}
