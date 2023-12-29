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
    for (int i = 0; i < my_graph.unvisited_trees.size(); i++)
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
    // Check the getShortestPath method
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

    std::vector<int> shortest_path = short_graph.getShortestPath(2, 5);
    CHECK(shortest_path[0] == 2);
    CHECK(shortest_path[1] == 3);
    CHECK(shortest_path[2] == 4);
    CHECK(shortest_path[3] == 5);
    CHECK(shortest_path.size() == 4);

    std::vector<int> shortest_path2 = short_graph.getShortestPath(2, 6);
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
    std::vector<int> shortest_path = hw_graph.getShortestPath(2, 10);
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
    std::vector<int> shortest_path = hwt2.getShortestPath(5, 1);
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
    std::vector<int> shortest_path = loop_graph.getShortestPath(2, 2);
    CHECK(shortest_path[0] == 2);
    CHECK(shortest_path.size() == 1);
}