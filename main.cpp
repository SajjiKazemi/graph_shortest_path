#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "helpers.h"

int main(int argc, char** argv) {

    // read from stdin until EOF
    while (!std::cin.eof()) {
        // print a promt
        std::cout << "Enter numbers separated by comma: ";

        // read a line of input until EOL and store in a string
        std::string line;
        std::getline(std::cin, line);

        // get the command from the line
        std::string command = line_parser::get_command(line);
        line_parser::analyze_command(command, line);
    }
}