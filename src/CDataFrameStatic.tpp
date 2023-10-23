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
std::vector<std::string> cdata_frame<T>::__parse_csv_line(const std::string &line, const char &sep, const bool &index, std::string *index_name)
{
    // Convert the line to string stream
    std::istringstream line_stream(line);

    // Create a vector of string used to store the line tokenized
    std::vector<std::string> line_tokenized;

    // Parse the line and store the tokens in the vector
    for (std::string word; getline(line_stream, word, sep);)
        line_tokenized.push_back(word);

    // Check if the index is enabled
    if (index)
    {
        // Check if the index name is set
        if (index_name == nullptr)
            throw std::invalid_argument("The index name must be set.");

        // Set the index name
        *index_name = line_tokenized[0];

        // Remove the index from the line
        line_tokenized.erase(line_tokenized.begin());
    }

    return line_tokenized;
}

template <class T>
cdata_frame<std::string> cdata_frame<T>::read_csv(const std::string &path, const char &sep, const bool &header, const bool &index)
{
    // Check if the file has expected extension (csv)
    if (not __has_expected_extension(path, "csv"))
        throw std::invalid_argument("The file '" + path + "' must be a csv file.");

    // Open the file
    std::fstream file = cdata_frame<T>::__open_file(path);

    cdata_frame<std::string> df;
    std::vector<std::string> vec_keys;
    std::vector<std::string> vec_index;

    // Parse the file line by line
    for (std::string line; getline(file, line);)
    {
        // Create a string used to store the current index
        std::string current_index = "";

        // Parse and tokenize the line
        const std::vector<std::string> &line_tokenized = cdata_frame<T>::__parse_csv_line(line, sep, index, &current_index);

        // Check if the header is enabled
        if (vec_keys.empty() and header)
            vec_keys = line_tokenized;

        else
        {
            // Push the line in the data frame
            df.push_row_back(line_tokenized);

            // Push the index in the vector if the index is enabled
            if (index)
                vec_index.push_back(current_index);
        }
    }

    // Close the file
    file.close();

    // If the data frame is empty, index and keys can't be set
    if (not df.is_empty())
    {
        // Set the keys
        df.set_keys(vec_keys);

        // Set the index
        df.set_index(vec_index);
    }

    return df;
}
