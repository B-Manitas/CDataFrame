# CDataFrame: A C++ DataFrame library for Data Science and Machine Learning projects.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Status](https://img.shields.io/badge/Status-Active-green.svg)](https://github.com/B-Manitas/CMatrix)

CDataFrame is a C++ library for Data Science and Machine Learning projects. It is designed to be fast and easy to use. It is based on the [CMatrix](htpps://github.com/B-Manitas/CMatrix) library.

This library works with C++11 or higher.

## Table of Contents

1. [Installation](#installation)
2. [Hierarchical Structure](#hierarchical-structure)
3. [Documentation](#documentation)
4. [See Also](#see-also)
5. [License](#license)

## Installation

To install the library, follow these steps:

1. Clone the repository using the following command:

```bash
git clone https://github.com/B-Manitas/CDataFrame.git
```

2. Include the [`CDataFrame.hpp`](include/CDataFrame.hpp) file in your project.

## Hierarchical Structure

CMatrix is structured as follows:

| Class                                                              | Description                                                                                     |
| ------------------------------------------------------------------ | ----------------------------------------------------------------------------------------------- |
| include                                                            |                                                                                                 |
| [`CDataFrame.hpp`](include/CDataFrame.hpp)                         | The main template class that can work with any data type except bool.                           |
| src                                                                |                                                                                                 |
| [`CDataFrame.tpp`](include/CDataFrame.tpp)                         | General methods of the class.                                                                   |
| [`CDataFrameConstructors.hpp`](include/CDataFrameConstructors.tpp) | Implementation of class constructors.                                                           |
| [`CDataFrameGetter.hpp`](include/CDataFrameGetter.tpp)             | Methods to retrieve information about the data frame and access its elements.                   |
| [`CDataFrameSetter.hpp`](include/CDataFrameSetter.tpp)             | Methods to set data in the data frame.                                                          |
| [`CDataFrameCheck.tpp`](include/CDataFrameCheck.tpp)               | Methods to verify data frame conditions and perform checks before operations to prevent errors. |
| [`CDataFrameManipulation.hpp`](include/CDataFrameManipulation.tpp) | Methods to find elements in the data frame and transform it.                                    |
| [`CDataFrameOperator.hpp`](include/CDataFrameOperator.tpp)         | Implementation of various operators.                                                            |
| [`CDataFrameStatic.hpp`](include/CDataFrameStatic.tpp)             | Implementation of static methods of the class.                                                  |
| test                                                               |                                                                                                 |
| [`CDataFrameTest.hpp`](test/CDataFrameTest.tpp)                    | Contains the tests for the class.                                                               |

## Documentation

For detailed information on how to use CMatrix, consult the [documentation](cdataframe.pdf).

## See Also

- [CMatrix](https://github.com/B-Manitas/CMatrix): A C++ library for matrix operations.

## License

This project is licensed under the MIT License, ensuring its free and open availability to the community.