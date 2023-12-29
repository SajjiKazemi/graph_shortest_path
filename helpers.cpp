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

    std::vector<std::string> analyze_command(std::string command, std::string line)
    {
        std::vector<std::string> result;
        if(command == "V")
        {
            std::istringstream input(line);
            std::string prefix;
            int number;

            input >> prefix >> number;
            result.push_back(std::to_string(number));            
            return result;
        }
        else if (command == "E")
        {
            std::regex pattern(R"(<(\d+),(\d+)>)");
            std::sregex_token_iterator iter(line.begin(), line.end(), pattern, {1,2});
            std::sregex_token_iterator end;
            while (iter != end) 
            {
                std::ostringstream oss;
                oss << "(" << *iter++ << ", " << *iter++ << ")";
                std::string pair = oss.str();
                result.push_back(pair);
            }
            std::cout << result[0] << result[1] << result[2] << std::endl;
            return result;
        }
        else if (command == "s")
        {
            std::istringstream input(line);
            std::string prefix;
            int start;
            int end;

            input >> prefix >> start >> end;
            result.push_back(std::to_string(start));
            result.push_back(std::to_string(end));
            std::cout << result[0] << result[1] << std::endl;
            return result;
        }
        

        
    }

}