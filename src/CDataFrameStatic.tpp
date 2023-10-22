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
    // Check if the file exists
    if (not __is_file_exist(path))
        throw std::invalid_argument("The file '" + path + "' doesn't exist.");

    // Open the file
    std::fstream file(path);

    // Check if the file is opened
    if (not file.is_open())
        throw std::runtime_error("Failed to open the file.");

    return file;
}

// ==================================================
// PARSE

template <class T>
std::vector<std::string> cdata_frame<T>::__parse_csv_line(std::string line, const char sep)
{
    // Convert the line to string stream
    std::istringstream line_stream(line);

    // Create a vector of string used to store the line tokenized
    std::vector<std::string> line_tokenized;

    // Parse the line and store the tokens in the vector
    for (std::string word; getline(line_stream, word, sep);)
        line_tokenized.push_back(word);

    return line_tokenized;
}

template <class T>
cdata_frame<T> cdata_frame<T>::read_csv(const std::string &path, const char &sep, const bool &header)
{
    // Check if the file has expected extension (csv)
    if (not __has_expected_extension(path, "csv"))
        throw std::invalid_argument("The file '" + path + "' must be a csv file.");

    // Open the file
    std::fstream file = cdata_frame<T>::__open_file(path);

    cdata_frame<T> df;
    bool first_line = true;

    // Parse the file line by line
    for (std::string line; getline(file, line);)
    {
        // Parse and tokenize the line
        const std::vector<std::string> &line_tokenized = cdata_frame<T>::__parse_csv_line(line, sep);

        // Check if the header is enabled
        if (first_line and header)
            df.set_keys(line_tokenized);

        // Push the line in the data frame
        else
            df.push_row_back(std::vector<T>(line_tokenized.begin(), line_tokenized.end()));

        first_line = false;
    }

    return df;
}
