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
	void preorder_traversal(Node* node);
    std::string to_json(Node* rootNode, std::string tabs, bool arr, bool obj);
public:
	Tree();
	void Read_XML(const std::string& path);
	void preorder_traversal();
    void prettierFunction(const std::string& outputPath);
    Node *getRoot();
    std::string to_json(const std::string& filePath);
};


#endif
