#include "BFStree.h"
#include <vector>

BFStree::BFStree(int root_node, std::vector<int> children)
{
    this->root_node = root_node;
    this->children = children;
}

int BFStree::getRootNode()
{
    return this->root_node;
}

std::vector<int> BFStree::getChildren()
{
    return this->children;
}