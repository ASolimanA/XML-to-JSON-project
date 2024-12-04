#include <iostream>
#include "Tree.h"
#include <regex>
#include <fstream>
#include <stack>

using namespace std;

Node::Node(string data) {
    tagName = data;
    tagValue = "";
}

std::string trim(const std::string& source) {
    std::string s(source);
    s.erase(0, s.find_first_not_of(" \n\r\t"));
    s.erase(s.find_last_not_of(" \n\r\t") + 1);
    return s;
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
    cout << node->tagName << ' ' << node->tagValue << endl;
    for (int i = 0; i < node->branches.size(); i++)
        preorder_traversal(node->branches[i]);
}

void Tree::Read_XML(string path) {
    string text, temp1, temp2;
    ifstream myFile(path);
    regex regexSet("\\<([^>]+)\\>|[^<]+");
    smatch matches;
    stack<Node*> st;
    while (getline(myFile, text)) {
        string::const_iterator it(text.cbegin());
        while (regex_search(it, text.cend(), matches, regexSet)){
            temp1 = trim(matches[0]);
            temp2 = matches[1];
            if(!temp1.empty() && temp1[0] != '<'){
                st.top()->tagValue = temp1;
            }
            else if (temp2[0] != '/') {
                cout << "test" << endl;
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
                if (st.top()->tagName == temp2.substr(1))
                    st.pop();
            }
            it = matches.suffix().first;

        }
    }
    myFile.close();
}