#include "node.hpp"

int Node::label = 0;

Node::Node() : index(Node::label++)
{
}