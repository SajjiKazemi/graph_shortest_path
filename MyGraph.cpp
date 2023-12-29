#include "MyGraph.h"
#include <vector>
#include <algorithm>

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

std::vector<int> MyGraph::getConnections(int node)
{
    std::vector<int> connections;
    for (auto const& x : this->edges)
    {
        if(x.second.first == node)
        {
            connections.push_back(x.second.second);
        }
        else if(x.second.second == node)
        {
            connections.push_back(x.second.first);
        }
    }

    return connections;
}

bool MyGraph::isConnected(int start, int end)
    {
        std::vector<int> connections = getConnections(start);    
            
        auto it = std::find(connections.begin(), connections.end(), end);
        if(it != connections.end())
            {
                return true;
            }
        else
            {
                return false;
            }
    }
    