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
std::vector<std::string> cdata_frame<T>::__generate_uids(const size_t len, const std::string &not_in) const
{
    // Create string vector with the size of the number of columns
    std::vector<std::string> uid_keys(len, "");

    // Fill the vector with the prefix and the uid
    for (size_t i = 0; i < len; i++)
    {
        std::string uid = std::to_string(i);

        if (uid == not_in)
            uid = not_in + uid;

        uid_keys[i] = uid;
    }

    return uid_keys;
}

template <class T>
cdata_frame<T> cdata_frame<T>::copy() const
{
    return cdata_frame<T>(m_keys, cmatrix<T>::copy(), m_index);
}

template <class T>
void cdata_frame<T>::clear()
{
    m_keys.clear();
    m_index.clear();
    cmatrix<T>::clear();
}

// ==================================================
// PRINT

template <class T>
template <class U>
short unsigned int cdata_frame<T>::__stream_width(const std::vector<U> data, const int &initial) const
{
    // The maximum size initialised with the initial value in case of having headers
    short unsigned int max_length = initial;

    // Iterate over the rows to get the maximum size of each column
    for (size_t i = 0; i < data.size(); i++)
    {
        // Get the size of the data
        const short unsigned int &data_length = cdata_frame<T>::__count_characters(data[i]);

        // Get the maximum size
        max_length = std::max(max_length, data_length);
    }

    // Add 2 for the space between the data and the border
    max_length += 2;

    return max_length;
}

template <class T>
std::vector<short unsigned int> cdata_frame<T>::__stream_widths_vec() const
{
    // The size of the vector is the number of columns + 1 (for the index at the position 0)
    const size_t size = cmatrix<T>::width() + 1;
    std::vector<short unsigned int> widths(size, 0);

    // Add the width of the index
    if (has_index())
        widths[0] = __stream_width(m_index);

    // Iterate over the columns to get the maximum size of each column
    for (size_t c = 1; c < size; c++)
    {
        // If hasn't keys, the key size is 0
        const size_t key_size = has_keys() ? m_keys[c - 1].size() : 0;

        // Assign the maximum size of the column
        widths[c] = __stream_width(cmatrix<T>::columns_vec(c - 1), key_size);
    }

    return widths;
}

template <class T>
std::string cdata_frame<T>::__print_border(const std::vector<short unsigned int> &widths, const std::string &start, const std::string &middle, const std::string &end, const std::string &line, const std::string &index) const
{
    std::ostringstream os;

    // Print the start of the border (┌, ├ or └)
    os << start;

    // Iterate over the widths to print the middle of the border (┬, ┼ or ┴)
    for (size_t i = 0; i < widths.size(); i++)
    {
        // If the width is 0, don't print the middle (useful when doesn't have index)
        if (widths[i] == 0)
            continue;

        // Print the middle
        for (size_t j = 0; j < widths[i]; j++)
            os << line;

        // Print the index border (╥, ╫ or ╨)
        if (i == 0 and not index.empty() && has_index())
            os << index;

        // Print the middle of the border (┬, ┼ or ┴)
        else if (i != widths.size() - 1)
            os << middle;
    }

    // Print the end of the border (┐, ┤ or ┘)
    os << end << std::endl;

    return os.str();
}

template <class T>
std::string cdata_frame<T>::__print_border_top(const std::vector<short unsigned int> &widths) const
{
    return __print_border(widths, "┌", "┬", "┐", "─", "╥");
}

template <class T>
std::string cdata_frame<T>::__print_border_middle(const std::vector<short unsigned int> &widths) const
{
    return __print_border(widths, "├", "┼", "┤", "─", "╫");
}

template <class T>
std::string cdata_frame<T>::__print_border_bottom(const std::vector<short unsigned int> &widths) const
{
    return __print_border(widths, "└", "┴", "┘", "─", "╨");
}

template <class T>
template <class U>
std::string cdata_frame<T>::__print_row(const std::vector<short unsigned int> &widths, const std::vector<U> &data, const std::string &index) const
{
    std::ostringstream os;

    // Handle the print of the first column, depending on if has index, keys or not
    // When the row is the header, the index is empty (display: '| |')
    if (has_index() and index == "")
    {
        std::string space = std::string(widths[0] - 2, ' ');
        os << "│ " << space << " ║ ";
    }

    // If not the header, print the index (display: '| index |')
    else if (has_index())
    {
        std::string space = std::string(widths[0] - 2 - index.size(), ' ');
        os << "│ " << index << space << " ║ ";
    }

    // If hasn't index, print the '| ' for the right border of the column (display: '| ')
    else
        os << "│ ";

    // Handle the print of the rest of the columns
    for (size_t i = 0; i < data.size(); i++)
    {
        // width[i + 1] because the first column is the index
        std::string space = std::string(widths[i + 1] - cdata_frame<T>::__count_characters(data[i]) - 2, ' ');

        // Print the element of the row
        os << data[i] << space;

        // Print the '|' except for the last column
        if (i < data.size())
            os << " │ ";
    }

    os << std::endl;

    return os.str();
}

template <class T>
std::string cdata_frame<T>::__print(std::true_type, const unsigned int &n) const
{
    std::ostringstream os;

    // Compute the widths for each column
    std::vector<short unsigned int> columns_widths = __stream_widths_vec();

    // Print the top border
    os << __print_border_top(columns_widths);

    // Print header
    if (has_keys())
    {
        // Index is empty because the header doesn't have index
        os << __print_row(columns_widths, m_keys, "");

        os << __print_border(columns_widths, "╞", "╪", "╡", "═", "╬");
    }

    // Print data
    const size_t n_rows = std::min((size_t)n, cmatrix<T>::height());

    for (size_t i = 0; i < n_rows; i++)
    {
        // If has index, get the index of the row
        const std::string index = has_index() ? m_index[i] : "";

        // Print the row
        os << __print_row(columns_widths, cmatrix<T>::rows_vec(i), index);

        // Print the middle line except for the last row
        if (i != n_rows - 1)
            os << __print_border_middle(columns_widths);
    }

    // Print the bottom border
    os << __print_border_bottom(columns_widths);

    return os.str();
}

template <class T>
std::string cdata_frame<T>::__print(std::false_type, const unsigned int &n) const
{
    std::ostringstream os;

    // Print the header
    os << "Keys  : ";

    for (const std::string key : m_keys)
        os << key << " | ";

    os << std::endl;

    // Print the index
    os << "Index : ";

    for (const std::string index : m_index)
        os << index << " | ";

    os << std::endl;

    // Print the data
    const size_t n_rows = std::min((size_t)n, cmatrix<T>::height());
    os << "Data  : [";

    for (size_t i = 0; i < n_rows; i++)
    {
        os << "[ ";

        for (size_t j = 0; j < cmatrix<T>::width(); j++)
        {
            os << cmatrix<T>::cell(i, j);

            if (j != cmatrix<T>::width() - 1)
                os << ", ";
        }

        os << " ]";

        if (i != n_rows - 1)
            os << ", ";
    }

    os << "]" << std::endl;

    return os.str();
}

template <class T>
void cdata_frame<T>::print(const unsigned int &n) const
{
    std::ostringstream os;
    os << __print(std::integral_constant < bool, std::is_fundamental<T>::value or std::is_same<T, std::string>::value > {}, n);
    std::cout << os.str();
}

template <class T>
void cdata_frame<T>::info() const 
{
    std::cout << "type of data: " << typeid(T).name() << std::endl;
    std::cout << "number of keys: " << m_keys.size() << std::endl;
    std::cout << "number of index: " << m_index.size() << std::endl;
    std::cout << "number of rows: " << cmatrix<T>::height() << std::endl;
    std::cout << "number of columns: " << cmatrix<T>::width() << std::endl;
}