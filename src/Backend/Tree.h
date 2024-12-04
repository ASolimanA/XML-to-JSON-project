#ifndef TREE_H_
#define TREE_H_

#include <string>
#include <vector>

class Node {
private:
	std::string tagName;
	std::string tagValue;
	std::vector<Node*> branches;
public:
	Node(std::string data);
	friend class Tree;
};

class Tree {
private:
	Node* root;
public:
	Tree();
	void Read_XML(std::string path);
	void preorder_traversal(Node* node);
	Node* get_root();
};


#endif