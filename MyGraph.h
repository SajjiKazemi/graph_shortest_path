#ifndef MYGRAPH_H
#define MYGRAPH_H

#include <map>
#include <iostream>
#include <vector>
#include "BFStree.h"

class MyGraph
{
private:
    int num_vertices;

public:
    MyGraph(int num_vertices);
    std::map<int, std::pair<int, int>> edges;
    std::vector<BFStree> unvisited_trees;
    std::vector<int> visited_nodes;
    std::vector<int> unvisited_nodes;
    int getSize();
    void setEdges(std::map<int, std::pair<int,int>> edges);
    std::vector<int> getConnections(int node);
    bool isConnected(int start, int end);
    void createRootTree(int start);
    bool checkTree(BFStree tree, int end);
    std::vector<int> getShortestPath(int start, int end);
    void getUnvisitedTrees();
    void clearEverything();
};


#endif
