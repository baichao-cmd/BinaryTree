#include <iostream>
#include <string>
#include "BinaryTree.h"

using namespace std;

int main() 
{
	BinaryTree<string> binarytree;
	BTNode<string> *root;
	root = new BTNode<string>("A");
	root->LChild = new BTNode<string>("B");
	root->RChild = new BTNode<string>("C");
	root->LChild->LChild = new BTNode<string>("D");
	root->LChild->RChild = new BTNode<string>("E");
	root->RChild->LChild = new BTNode<string>("F");
	root->RChild->RChild = new BTNode<string>("G");
	binarytree.PreOrder(root);
	return 0;
}