/**
 * An example unit test using doctest. See documentation at
 * https://github.com/onqtam/doctest/blob/master/doc/markdown/tutorial.md
 */
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "helpers.h"
#include "MyGraph.h"

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

TEST_CASE("Test the MyGraph class")
{
    // Check the getSize() function
    MyGraph test_graph(5);
    CHECK(test_graph.getSize() == 5);

    // Check the setEdges() function
    std::map<int, std::pair<int,int>> edges;
    edges[1] = std::make_pair(2, 3);
    edges[2] = std::make_pair(3, 4);
    edges[3] = std::make_pair(4, 5);
    test_graph.setEdges(edges);
    CHECK(test_graph.edges[1].first == 2);
    CHECK(test_graph.edges[1].second == 3);
    CHECK(test_graph.edges[2].first == 3);
    CHECK(test_graph.edges[2].second == 4);
    CHECK(test_graph.edges[3].first == 4);
    CHECK(test_graph.edges[3].second == 5);

    // Check the getConnections() function
    std::vector<int> connections = test_graph.getConnections(3);
    CHECK(connections[0] == 2);
    CHECK(connections[1] == 4);
    CHECK(connections[2] != 5);
    CHECK(connections.size() == 2);

    // Check the isConnected method
    CHECK(test_graph.isConnected(2, 3) == true);
    CHECK(test_graph.isConnected(2, 5) == false);
    CHECK(test_graph.isConnected(3, 2) == true);
    CHECK(test_graph.isConnected(3, 4) == true);
    CHECK(test_graph.isConnected(3, 5) == false);
}