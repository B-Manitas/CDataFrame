/**
 * @file CDataFrameStatic.tpp
 * @brief File containing the implementation of static methods of the 'DataFrame' class.
 *
 * @see CDataFrame.hpp
 * @defgroup static
 */

// ==================================================
// FILE

template <class T>
bool cdata_frame<T>::__is_file_exist(const std::string &path)
{
    return std::ifstream(path.c_str()).good();
}

template <class T>
bool cdata_frame<T>::__has_expected_extension(const std::string &path, const std::string &extension)
{
    return path.substr(path.find_last_of(".") + 1) == extension;
}

template <class T>
std::fstream cdata_frame<T>::__open_file(const std::string &path)
{
    if (not __is_file_exist(path))
        throw std::invalid_argument("The file '" + path + "' doesn't exist.");

    std::fstream file(path);

    if (not file.is_open())
        throw std::runtime_error("Failed to open the file.");

    return file;
}

// ==================================================
// PARSE

template <class T>
std::vector<std::string> cdata_frame<T>::__parse_csv_line(std::string line, const char sep)
{
    std::istringstream line_stream(line);
    std::vector<std::string> line_tokenized;

    for (std::string word; getline(line_stream, word, sep);)
        line_tokenized.push_back(word);

    return line_tokenized;
}

template <class T>
cdata_frame<T> cdata_frame<T>::read_csv(const std::string &path, const char &sep, const bool &header)
{
    if (not __has_expected_extension(path, "csv"))
        throw std::invalid_argument("The file '" + path + "' must be a csv file.");

    std::fstream file = cdata_frame<T>::__open_file(path);
    cdata_frame<T> df;

    bool first_line = true;
    for (std::string line; getline(file, line);)
    {
        const std::vector<std::string> &line_tokenized = cdata_frame<T>::__parse_csv_line(line, sep);

        if (first_line and header)
            df.set_keys(line_tokenized);

        else
            df.push_row_back(std::vector<T>(line_tokenized.begin(), line_tokenized.end()));

        first_line = false;
    }

    return df;
}
