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

template <class T>
CDataFrame<T>::CDataFrame(const cmatrix<T> &data) : m_data(data) {}

template <class T>
CDataFrame<T>::CDataFrame(const std::vector<std::string> &keys) : m_keys(keys) {}

template <class T>
CDataFrame<T>::CDataFrame(const std::vector<std::string> &keys, const cmatrix<T> &data)
{
    if (keys.size() != data.dim_h())
        throw std::invalid_argument("The number of keys must be equal to the number of columns of the data.");

    m_keys = keys;
    m_data = data;
}

// ==================================================
// Destructor
template <class T>
CDataFrame<T>::~CDataFrame() {}
