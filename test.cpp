/**
 * An example unit test using doctest. See documentation at
 * https://github.com/onqtam/doctest/blob/master/doc/markdown/tutorial.md
 */
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "helpers.h"
#include "MyGraph.h"
#include "BFStree.h"
#include <iostream>
#include <algorithm>
#include <vector>

TEST_CASE("Test line_parser::get_command") {
    MyGraph test_graph;
    std::string line = "V 15";
    std::string command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    CHECK(command == "V");
    std::string line2 = "E {<1,2>,<2,3>,<3,4>}";
    std::string command2 = line_parser::get_command(line2, test_graph);
    line_parser::analyze_command(command2, line2, test_graph);
    CHECK(command2 == "E");
    std::string line3 = "s 1 2";
    std::string command3 = line_parser::get_command(line3, test_graph);
    CHECK(command3 == "s");
}

TEST_CASE("Test default constructor of MyGraph class")
{
    MyGraph test_graph;
    CHECK(test_graph.getSize() == 0);
    test_graph.setNoVertices(5);
    CHECK(test_graph.getSize() == 5);
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

    // Check the createRootTree method
    edges[4] = std::make_pair(1, 5);
    edges[5] = std::make_pair(1, 2);
    edges[6] = std::make_pair(1, 3);
    test_graph.setEdges(edges);
    test_graph.createRootTree(1);
    CHECK(test_graph.unvisited_trees[0].getRootNode() == 1);
    CHECK(std::find(test_graph.unvisited_trees[0].getChildren().begin(), 
        test_graph.unvisited_trees[0].getChildren().end(), 2) != test_graph.unvisited_trees[0].getChildren().end());
    CHECK(std::find(test_graph.unvisited_trees[0].getChildren().begin(), 
        test_graph.unvisited_trees[0].getChildren().end(), 3) != test_graph.unvisited_trees[0].getChildren().end());
        CHECK(std::find(test_graph.unvisited_trees[0].getChildren().begin(), 
        test_graph.unvisited_trees[0].getChildren().end(), 4) != test_graph.unvisited_trees[0].getChildren().end());
        CHECK(std::find(test_graph.unvisited_trees[0].getChildren().begin(), 
        test_graph.unvisited_trees[0].getChildren().end(), 5) != test_graph.unvisited_trees[0].getChildren().end());
    CHECK(test_graph.unvisited_trees[0].getAncestors().size() == 0);


    // Check the checkTree method
    CHECK(test_graph.checkTree(test_graph.unvisited_trees[0], 2) == true);
    CHECK(test_graph.checkTree(test_graph.unvisited_trees[0], 3) == true);
    CHECK(test_graph.visited_nodes.size() == 0);
    CHECK(test_graph.checkTree(test_graph.unvisited_trees[0], 4) == false);
    CHECK(test_graph.visited_nodes.size() == 1);
    CHECK(test_graph.visited_nodes[0] == 1);
    CHECK(test_graph.checkTree(test_graph.unvisited_trees[0], 5) == true);
    CHECK(test_graph.checkTree(test_graph.unvisited_trees[0], 6) == false);
    CHECK(test_graph.checkTree(test_graph.unvisited_trees[0], 1) == false);
}

TEST_CASE("More tests on MyGraph class")
{
    // Check the addUnvisitedTrees method
    MyGraph my_graph(10);
    std::map<int, std::pair<int,int>> edges;
    edges[1] = std::make_pair(2, 3);
    edges[2] = std::make_pair(3, 4);
    edges[3] = std::make_pair(4, 5);
    edges[4] = std::make_pair(2, 1);
    edges[5] = std::make_pair(2, 7);
    edges[6] = std::make_pair(3, 8);
    edges[7] = std::make_pair(3, 7);
    edges[8] = std::make_pair(7, 9);
    edges[9] = std::make_pair(7, 6);
    edges[10] = std::make_pair(7, 8);
    edges[11] = std::make_pair(7, 2);
    edges[12] = std::make_pair(1, 2);
    edges[13] = std::make_pair(2, 2);
    my_graph.setEdges(edges);
    my_graph.createRootTree(2);
    my_graph.checkTree(my_graph.unvisited_trees[0], 5);
    CHECK(my_graph.unvisited_trees.size() == 1);
    CHECK(my_graph.visited_nodes.size() == 1);
    my_graph.getUnvisitedTrees();
    CHECK(my_graph.unvisited_trees.size() == 3);
    std::vector<int> nodes;
    for (std::vector<int>::size_type i = 0; i < my_graph.unvisited_trees.size(); i++)
    {
        nodes.push_back(my_graph.unvisited_trees[i].getRootNode());
    }
    CHECK(std::find(nodes.begin(), nodes.end(), 3) != nodes.end());
    CHECK(std::find(nodes.begin(), nodes.end(), 7) != nodes.end());
    CHECK(std::find(nodes.begin(), nodes.end(), 1) != nodes.end());
    CHECK(std::find(nodes.begin(), nodes.end(), 2) == nodes.end());
}

TEST_CASE("Test on finding the shortest path")
{
    // Check the findShortestPath method
    MyGraph short_graph(10);
    std::map<int, std::pair<int,int>> edges;
    edges[1] = std::make_pair(2, 3);
    edges[2] = std::make_pair(3, 4);
    edges[3] = std::make_pair(4, 5);
    edges[4] = std::make_pair(2, 1);
    edges[5] = std::make_pair(2, 7);
    edges[6] = std::make_pair(3, 8);
    edges[7] = std::make_pair(3, 7);
    edges[8] = std::make_pair(7, 9);
    edges[9] = std::make_pair(7, 6);
    edges[10] = std::make_pair(7, 8);
    edges[11] = std::make_pair(7, 2);
    edges[12] = std::make_pair(1, 2);
    edges[13] = std::make_pair(2, 2);
    short_graph.setEdges(edges);

    std::vector<int> shortest_path = short_graph.findShortestPath(2, 5);
    CHECK(shortest_path[0] == 2);
    CHECK(shortest_path[1] == 3);
    CHECK(shortest_path[2] == 4);
    CHECK(shortest_path[3] == 5);
    CHECK(shortest_path.size() == 4);

    std::vector<int> shortest_path2 = short_graph.findShortestPath(2, 6);
    CHECK(shortest_path2[0] == 2);
    CHECK(shortest_path2[1] == 7);
    CHECK(shortest_path2[2] == 6);
    CHECK(shortest_path2.size() == 3);
}

TEST_CASE("Test the BFStree class")
{
    // Test the BFsearch class
    std::vector<int> children;
    children.push_back(2);
    children.push_back(3);
    children.push_back(4);
    BFStree test_tree(1, children);
    CHECK(test_tree.getRootNode() == 1);
    CHECK(test_tree.getChildren()[0] == 2);
    CHECK(test_tree.getChildren()[1] == 3);
    CHECK(test_tree.getChildren()[2] == 4);
    CHECK(test_tree.getAncestors().size() == 0);

    // Test the isIncluded method
    CHECK(test_tree.isIncluded(2) == true);
    CHECK(test_tree.isIncluded(3) == true);
    CHECK(test_tree.isIncluded(4) == true);
    CHECK(test_tree.isIncluded(5) == false);
    CHECK(test_tree.isIncluded(1) == false);

    // Test adding ancestors
    std::vector<int> children2;
    children2.push_back(5);
    children2.push_back(6);
    children2.push_back(7);
    BFStree test_tree2(test_tree.getChildren()[0], children2, test_tree);
    CHECK(test_tree2.getAncestors()[0] == 1);
    CHECK(test_tree2.getAncestors().size() == 1);
    CHECK(test_tree2.getAncestors()[1] != 2);

    BFStree test_tree3(test_tree2.getChildren()[0], children, test_tree2);
    CHECK(test_tree3.getAncestors()[0] == 1);
    CHECK(test_tree3.getAncestors()[1] == 2);
    CHECK(test_tree3.getAncestors().size() == 2);
    CHECK(test_tree3.getAncestors()[2] != 3);

}

TEST_CASE("Trying HW's test case 1")
{
    MyGraph hw_graph(15);
    std::map<int, std::pair<int,int>> edges;
    edges[1] = std::make_pair(2, 6);
    edges[2] = std::make_pair(2, 8);
    edges[3] = std::make_pair(2, 5);
    edges[4] = std::make_pair(6, 5);
    edges[5] = std::make_pair(5, 8);
    edges[6] = std::make_pair(6, 10);
    edges[7] = std::make_pair(10, 8);
    hw_graph.setEdges(edges);
    std::vector<int> shortest_path = hw_graph.findShortestPath(2, 10);
    CHECK(shortest_path[0] == 2);
    bool condition = (shortest_path[1] == 6 || shortest_path[1] == 8);
    CHECK(condition == true);
    CHECK(shortest_path[2] == 10);
    CHECK(shortest_path.size() == 3);
}

TEST_CASE("Trying HW's test case 2")
{
    MyGraph hwt2(5);
    std::map<int, std::pair<int,int>> edges;
    edges[1] = std::make_pair(1, 3);
    edges[2] = std::make_pair(3, 2);
    edges[3] = std::make_pair(3, 4);
    edges[4] = std::make_pair(4, 5);
    edges[5] = std::make_pair(5, 2);
    hwt2.setEdges(edges);
    std::vector<int> shortest_path = hwt2.findShortestPath(5, 1);
    CHECK(shortest_path[0] == 5);
    CHECK(shortest_path[1] == 2);
    CHECK(shortest_path[2] == 3);
    CHECK(shortest_path[3] == 1);
    CHECK(shortest_path.size() == 4);
}

TEST_CASE("If loop happens")
{
    MyGraph loop_graph(5);
    std::map<int, std::pair<int,int>> edges;
    edges[1] = std::make_pair(2, 3);
    edges[2] = std::make_pair(3, 4);
    edges[3] = std::make_pair(4, 5);
    edges[4] = std::make_pair(5, 2);
    loop_graph.setEdges(edges);
    std::vector<int> shortest_path = loop_graph.findShortestPath(2, 2);
    CHECK(shortest_path[0] == 2);
    CHECK(shortest_path.size() == 1);
}

TEST_CASE("Test the line parses for E")
{
    MyGraph test_graph;
    std::string line = "V 15";
    std::string command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    command = line_parser::get_command(line, test_graph);
    CHECK(command == "E");
    line_parser::analyze_command(command, line, test_graph);
    CHECK(test_graph.edges[1].first == 2);
    CHECK(test_graph.edges[1].second == 6);
    CHECK(test_graph.edges[2].first == 2);
    CHECK(test_graph.edges[2].second == 8);
    CHECK(test_graph.edges[3].first == 2);
    CHECK(test_graph.edges[3].second == 5);
    CHECK(test_graph.edges[4].first == 6);
    CHECK(test_graph.edges[4].second == 5);
    CHECK(test_graph.edges[5].first == 5);
    CHECK(test_graph.edges[5].second == 8);
    CHECK(test_graph.edges[6].first == 6);
    CHECK(test_graph.edges[6].second == 10);
    CHECK(test_graph.edges[7].first == 10);
    CHECK(test_graph.edges[7].second == 8);
}

TEST_CASE("Test the line parser for V")
{
    MyGraph test_graph;
    std::string line = "V 15";
    std::string command = line_parser::get_command(line, test_graph);
    CHECK(command == "V");
    line_parser::analyze_command(command, line, test_graph);
    CHECK(test_graph.getSize() == 15);
}

TEST_CASE("Test the line parser for all")
{
    MyGraph test_graph;
    std::string line = "V 15";
    std::string command = line_parser::get_command(line, test_graph);
    CHECK(command == "V");
    line_parser::analyze_command(command, line, test_graph);
    CHECK(test_graph.getSize() == 15);
    std::string line2 = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    std::string command2 = line_parser::get_command(line2, test_graph);
    CHECK(command2 == "E");
    line_parser::analyze_command(command2, line2, test_graph);

    std::string line3 = "s 2 10";
    std::string command3 = line_parser::get_command(line3, test_graph);
    CHECK(command3 == "s");
    line_parser::analyze_command(command3, line3, test_graph);
    CHECK(test_graph.shortest_path[0] == 2);
    bool condition = (test_graph.shortest_path[1] == 6 || test_graph.shortest_path[1] == 8);
    CHECK(condition == true);
    CHECK(test_graph.shortest_path[2] == 10);
    CHECK(test_graph.shortest_path.size() == 3);   
}

TEST_CASE("Check the standard output")
{
    MyGraph test_graph;
    std::string line = "V 15";
    std::string command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    std::string line2 = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    std::string command2 = line_parser::get_command(line2, test_graph);
    line_parser::analyze_command(command2, line2, test_graph);
    std::string line3 = "s 2 10";
    std::string command3 = line_parser::get_command(line3, test_graph);
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    line_parser::analyze_command(command3, line3, test_graph);
    std::cout.rdbuf(oldCout);
    CHECK(output.str() == "2-6-10\n");    
}

TEST_CASE("Check VE....s")
{
    MyGraph test_graph;
    std::string line = "V 15";
    std::string command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "E ";
    command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "E (argg)";
    command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "s 2 10";
    command = line_parser::get_command(line, test_graph);
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    line_parser::analyze_command(command, line, test_graph);
    std::cout.rdbuf(oldCout);
    CHECK(output.str() == "2-6-10\n");
}

TEST_CASE("Check VEE and VEEs")
{
    MyGraph test_graph;
    std::string line = "V 15";
    std::string command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "E {<3,7>,<3,9>,<3,11>,<7,9>,<7,11>,<9,11>}";
    command = line_parser::get_command(line, test_graph);
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    line_parser::analyze_command(command, line, test_graph);
    std::cout.rdbuf(oldCout);
    CHECK(output.str() == "");
    line = "s 2 10";
    command = line_parser::get_command(line, test_graph);
    oldCout = std::cout.rdbuf(output.rdbuf());
    line_parser::analyze_command(command, line, test_graph);
    std::cout.rdbuf(oldCout);
    CHECK(output.str() == "2-6-10\n");
}

TEST_CASE("Check VEE with the error in first E")
{
    MyGraph test_graph;
    std::string line = "V 15";
    std::string command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>";
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    command = line_parser::get_command(line, test_graph);
    std::cout.rdbuf(oldCout);
    CHECK(output.str() == "Error: invalid command\n");
    line_parser::analyze_command(command, line, test_graph);
    line = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    command = line_parser::get_command(line, test_graph);
    output.str("");
    oldCout = std::cout.rdbuf(output.rdbuf());
    line_parser::analyze_command(command, line, test_graph);
    std::cout.rdbuf(oldCout);
    CHECK(output.str() == "");
    line = "s 2 10";
    oldCout = std::cout.rdbuf(output.rdbuf());
    command = line_parser::get_command(line, test_graph);
    std::cout.rdbuf(oldCout);
    line_parser::analyze_command(command, line, test_graph);
    CHECK(output.str() == "Error: no edges defined\n");
    output.str("");
    line = "s 8 6";
    oldCout = std::cout.rdbuf(output.rdbuf());
    command = line_parser::get_command(line, test_graph);
    std::cout.rdbuf(oldCout);
    line_parser::analyze_command(command, line, test_graph);
    CHECK(output.str() == "Error: no edges defined\n"); 
}

TEST_CASE("VEEEs if 1st E is invalid even if the next Es are valid and the s command will be also invalid")
{
    MyGraph test_graph;
    std::string line = "V 15";
    std::string command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>";
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    command = line_parser::get_command(line, test_graph);
    std::cout.rdbuf(oldCout);
    CHECK(output.str() == "Error: invalid command\n");
    output.str("");
    line_parser::analyze_command(command, line, test_graph);
    CHECK(test_graph.triedToSetEdges == true);
    line = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}"; // This is the 2nd E
    command = line_parser::get_command(line, test_graph);
    oldCout = std::cout.rdbuf(output.rdbuf());
    line_parser::analyze_command(command, line, test_graph);
    std::cout.rdbuf(oldCout);
    CHECK(output.str() == "");
    output.str("");
    line = "E {<3,7>,<3,9>,<3,11>,<7,9>,<7,11>,<9,11>}"; // This is the 3rd E
    oldCout = std::cout.rdbuf(output.rdbuf());
    command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    std::cout.rdbuf(oldCout);
    CHECK(output.str() == "");
    output.str("");
    line = "s 2 10"; // This is the s command
    oldCout = std::cout.rdbuf(output.rdbuf());
    command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    std::cout.rdbuf(oldCout);
    CHECK(output.str() == "Error: no edges defined\n");
}

TEST_CASE("Test VEVEs")
{
    MyGraph test_graph;
    std::string line = "V 15";
    std::string command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "E {<-2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    command = line_parser::get_command(line, test_graph);
    std::cout.rdbuf(oldCout);
    CHECK(output.str() == "Error: invalid command\n");
    line_parser::analyze_command(command, line, test_graph);
    CHECK(test_graph.triedToSetEdges == true);
    line = "V 16";
    output.str("");
    command = line_parser::get_command(line, test_graph);
    oldCout = std::cout.rdbuf(output.rdbuf());
    line_parser::analyze_command(command, line, test_graph);
    CHECK(test_graph.triedToSetEdges == false);
    std::cout.rdbuf(oldCout);
    CHECK(output.str() == "");
    line = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    command = line_parser::get_command(line, test_graph);
    output.str("");
    oldCout = std::cout.rdbuf(output.rdbuf());
    line_parser::analyze_command(command, line, test_graph);
    std::cout.rdbuf(oldCout);
    CHECK(output.str() == "");
    line = "s 2 10";
    command = line_parser::get_command(line, test_graph);
    output.str("");
    oldCout = std::cout.rdbuf(output.rdbuf());
    line_parser::analyze_command(command, line, test_graph);
    std::cout.rdbuf(oldCout);
    CHECK(output.str() == "2-6-10\n");
}

TEST_CASE("If any vertice's id is higher than the number of vertices")
{
    MyGraph test_graph;
    std::string line = "V 15";
    std::string command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "E {<2,16>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    std::cout.rdbuf(oldCout);
    CHECK(output.str() == "Error: edge is not valid\n");
}

TEST_CASE("When there is no path to desired node")
{
    MyGraph test_graph;
    std::string line = "V 15";
    std::string command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "s 2 7";
    command = line_parser::get_command(line, test_graph);
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    line_parser::analyze_command(command, line, test_graph);
    std::cout.rdbuf(oldCout);
    CHECK(output.str() == "Error: no path exists\n");
}

TEST_CASE("Loop for a node that is not in edges")
{
    MyGraph test_graph;
    std::string line = "V 15";
    std::string command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "s 1 1";
    command = line_parser::get_command(line, test_graph);
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    line_parser::analyze_command(command, line, test_graph);
    std::cout.rdbuf(oldCout);
    CHECK(output.str() == "Error: no path exists\n");
}

TEST_CASE("Loop for a node that exists in edges")
{
    MyGraph test_graph;
    std::string line = "V 15";
    std::string command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "s 2 2";
    command = line_parser::get_command(line, test_graph);
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    line_parser::analyze_command(command, line, test_graph);
    std::cout.rdbuf(oldCout);
    CHECK(output.str() == "2\n");
}

TEST_CASE("HW test case with 2 to 5")
{
    MyGraph test_graph;
    std::string line = "V 15";
    std::string command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "s 2 10";
    command = line_parser::get_command(line, test_graph);
    std::ostringstream output1;
    std::streambuf* oldCout1 = std::cout.rdbuf(output1.rdbuf());
    line_parser::analyze_command(command, line, test_graph);
    std::cout.rdbuf(oldCout1);
    CHECK(output1.str() == "2-6-10\n");

    line = "s 2 5";
    command = line_parser::get_command(line, test_graph);
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    line_parser::analyze_command(command, line, test_graph);
    std::cout.rdbuf(oldCout);
    CHECK(output.str() == "2-5\n");
}

TEST_CASE("HW's test case exactly")
{
    MyGraph test_graph;
    std::string line = "V 15";
    std::string command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    std::ostringstream output1;
    std::streambuf* oldCout1 = std::cout.rdbuf(output1.rdbuf());
    line = "s 2 10";
    command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    std::cout.rdbuf(oldCout1);
    CHECK(output1.str() == "2-6-10\n");

    line = "V 5";
    command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    line = "E {<1,3>,<3,2>,<3,4>,<4,5>,<5,2>}";
    command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    std::ostringstream output2;
    std::streambuf* oldCout2 = std::cout.rdbuf(output2.rdbuf());
    line = "s 5 1";
    command = line_parser::get_command(line, test_graph);
    line_parser::analyze_command(command, line, test_graph);
    std::cout.rdbuf(oldCout2);
    CHECK(output2.str() == "5-2-3-1\n");
    
}