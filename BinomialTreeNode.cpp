#include"BinomialTreeNode.h"

//Basic node class which implements the Binary node -> (Data and Parent)
BinomialTreeNode::BinomialTreeNode(const double& e)
{
	data = e;
	Parent = 0;
}

BinomialTreeNode::BinomialTreeNode(const double& e, BinomialTreeNode *parent)
{
	data = e;
	Parent = parent;
}

