#include <iostream>
#include "Tree.h"
#include <regex>
#include <fstream>
#include <stack>

using namespace std;

Node::Node(string data) {
	this->data = data;
}

Tree::Tree() {
	root = NULL;
}

Node* Tree::get_root() {
	return root;
}

void Tree::preorder_traversal(Node* node) {
	if (node == NULL)
		return;
	cout << node->data << endl;
	for (int i = 0; i < node->branches.size(); i++)
		preorder_traversal(node->branches[i]);
}

void Tree::Read_XML(string path) {
	string text, temp;
	ifstream myFile(path);
	regex regexSet("\\<([^>]+)\\>");
	smatch matches;
	stack<Node*> st;
	while (getline(myFile, text)) {
		string::const_iterator it(text.cbegin());
		while (regex_search(it, text.cend(), matches, regexSet)) {
			temp = matches[1];
			if (temp[0] != '/') {
				Node* attr = new Node(matches[1]);
				if (root == NULL) {
					root = attr;
				}
				else if (!st.empty()) {
					st.top()->branches.push_back(attr);
				}
				st.push(attr);
			}
			else if (!st.empty()) {
				if (st.top()->data == temp.substr(1))
					st.pop();
			}
			it = matches.suffix().first;
		}
	}
	myFile.close();
}
