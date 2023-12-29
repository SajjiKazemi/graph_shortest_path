#include "helpers.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

namespace line_parser{

    std::string get_command(std::string line){

        std::regex vertice_define_pattern(R"(V (\d+))");
        std::regex edge_define_pattern(R"(E \{<\d+,\d+>(,<\d+,\d+>)*\})");
        std::regex shortest_path_pattern(R"(s (\d+) (\d+))");
        std::string command;

        if(std::regex_match(line, vertice_define_pattern)){
            command = "V";
        }
        else if(std::regex_match(line, edge_define_pattern)){
            command = "E";
        }
        else if(std::regex_match(line, shortest_path_pattern)){
            command = "s";
        }
        else{
            command = "Error";
        }
        return command;
    }    

    std::vector<std::string> split(std::string line, char separator){
        std::vector<std::string> result;
        std::istringstream input(line);
        while (!input.eof())
        {
            std::string num;
            input >> num;
            if (input.fail())
            {
                std::cerr << "Error parsing a number\n";
                break;
            }
            else
                result.push_back(num);

            if (input.eof())
                break;

            char separator;
            input >> separator;

            if (input.fail() || separator != separator)
            {
                std::cerr << "Error parsing separator\n";
                break;
            }
        }
        return result;
    }
}