/**
 * An example unit test using doctest. See documentation at
 * https://github.com/onqtam/doctest/blob/master/doc/markdown/tutorial.md
 */
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "helpers.h"

TEST_CASE("Test line_parser::get_command") {
    std::string line = "V 15";
    std::string command = line_parser::get_command(line);
    CHECK(command == "V");
    std::string line2 = "E {<1,2>,<2,3>,<3,4>}";
    std::string command2 = line_parser::get_command(line2);
    CHECK(command2 == "E");
    std::string line3 = "s 1 2";
    std::string command3 = line_parser::get_command(line3);
    CHECK(command3 == "s");
}