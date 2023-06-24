/**
 * @mainpage Simple Json Parser
 *
 * @section intro Introduction
 *
 *  This program provides various useful classes for parsing and working with JSON files. \n
 *  JSON (JavaScript Object Notation) is a lightweight data-interchange format.
 *  It is easy for humans to read and write. (source: https://www.json.org/json-en.html).
 *
 * @section features Key Features
 *
 * - Detailed interface for common operations, including: \n
 *      -Opening new files. \n
 *      -Saving your data to new files. \n
 *      -Printing and formatting the JSON file. \n
 *      -Searching for specific keys. \n
 *      -Checking if the JSON file contains a specific value. \n
 *      -Changing a key's current value. \n
 *      -Creating new key-value pairs. \n
 *      -Deleting and moving elements. \n
 *
 * - Polymorphic factory for all JSON types.
 *
 * - Handles linefeeds, carriage returns, horizontal tabs and any sort or whitespace in JSON strings.
 *
 *
 * @section getting_started Getting Started
 *
 * - To build and compile this project: \n
 *      -Install cmake and clone the repository. \n
 *      -Create a build directory. \n
 *      -Generate the build files using Cmake. \n
 *      -BUild the project. \n
 *      -After a successful build, run the generated executable (named 'Json' by default). \n
 *
 */
#include "Interface.hpp"
int main(int argc, char *argv[])
{
    String file = INVALID_FILENAME;
    if (argc > 1)
        file = argv[1];

    Interface i(file);
    i.run();

    std::cout << std::endl;
    return 0;
}