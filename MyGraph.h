#ifndef MYGRAPH_H
#define MYGRAPH_H

#include <map>
#include <iostream>

class MyGraph
{
private:
    int num_vertices;

public:
    MyGraph(int num_vertices);
    std::map<int, std::pair<int, int>> edges;
    int getSize();
    void setEdges(std::map<int, std::pair<int,int>> edges);
};


#endif
