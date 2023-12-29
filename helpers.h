#ifndef HELPERS_H
#define HELPERS_H

#include <vector>
#include <iostream>
#include <sstream>
#include <string>

namespace line_parser {
    // get the command from a line
    std::string get_command(std::string line);
    // split a string into a vector of strings
    std::vector<std::string> split(std::string line, char separator);
}

#endif