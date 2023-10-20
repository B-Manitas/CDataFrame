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
CDataFrame<T>::CDataFrame()
{
    m_keys = std::vector<std::string>();
    m_data = cmatrix<T>();
}

// ==================================================
// Destructor
template <class T>
CDataFrame<T>::~CDataFrame() {}
