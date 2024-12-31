#ifndef TREE_H_
#define TREE_H_

#include <string>
#include <vector>
#include "graph.h"

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
	void Read_XML(const std::string& xml);
	void preorder_traversal();
    std::string prettierFunction();
    Node *getRoot();
    std::string to_json();
	// Functions to convert to graph
	Graph* convert_to_graph();
	User* convert_user(Node* user_node, Graph* current_graph);
	void add_posts(User* current_user, Node* posts_node);
	void add_topics(Post* current_post, Node* topics_node);
	void add_followers(User* current_user, Node* followers_node, Graph* current_graph);
	static std::string fileToString(const std::string& filePath);
	bool isParent(Node* node);
	std::string minifyNode(Node* current);
	std::string minify();
};


#endif
