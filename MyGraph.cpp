#include "MyGraph.h"

// Constructor definition
MyGraph::MyGraph(int num_vertices)
{
    this->num_vertices = num_vertices;
}

// Method definition
int MyGraph::getSize()
{
    return this->num_vertices;
}

void MyGraph::setEdges(std::map<int, std::pair<int,int>> edges)
{
    this->edges = edges;
}