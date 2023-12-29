#ifndef BFSTREE_H
#define BFSTREE_H

#include <vector>

class BFStree
{
private:
    int root_node;
    std::vector<int> children;

public:
    BFStree(int root_node, std::vector<int> children);
    int getRootNode();
    std::vector<int> getChildren();
};

#endif