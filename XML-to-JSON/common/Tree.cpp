#include <iostream>
#include "Tree.h"
#include <regex>
#include <fstream>
#include <stack>

using namespace std;

string trim(const std::string& source) {
    std::string s(source);
    s.erase(0, s.find_first_not_of(" \n\r\t"));
    s.erase(s.find_last_not_of(" \n\r\t") + 1);
    return s;
}

Node::Node(string data) {
    tagName = data;
    tagValue = "";
}

Tree::Tree() {
    root = NULL;
}

Node *Tree::getRoot() {
    return root;
}

void Tree::preorder_traversal(Node* node) {
    if (node == NULL)
        return;
    cout << node->tagName << ' ' << node->tagValue << endl;
    for (int i = 0; i < node->branches.size(); i++)
        preorder_traversal(node->branches[i]);
}

void Tree::preorder_traversal() {
    preorder_traversal(root);
}

void Tree::Read_XML(string path) {
    string text, temp1, temp2;
    ifstream myFile(path);
    // regex to find tag or a tag value
    regex regexSet("\\<([^>]+)\\>|[^<]+");
    smatch matches;
    stack<Node*> st;
    while (getline(myFile, text)) {
        string::const_iterator it(text.cbegin());
        while (regex_search(it, text.cend(), matches, regexSet)){
            // inc. iterator to index after the finded regex
            it = matches.suffix().first;
            // temp1 contains founded tag name with brackets "< and >"
            // if founded value is a tag's value: temp1 will contain the value and temp2 will be false
            temp1 = trim(matches[0]);
            // temp1 contains founded tag name without brackets
            temp2 = matches[1];
            // if the string is empty -> skip
            if (temp1.empty())
                continue;
            // if not a tag(value) => assign that value to the tag in the top of the stack
            else if(temp1[0] != '<'){
                st.top()->tagValue = temp1;
            }
            // if it's an open tag => push it to the stack
            else if (temp2[0] != '/') {
                Node* attr = new Node(matches[1]);
                if (root == NULL) {
                    root = attr;
                }
                // before pushing to the stack => assign that tag as a children to the tag in the stack's top
                else if (!st.empty()) {
                    st.top()->branches.push_back(attr);
                }
                st.push(attr);
            }
            // if it's a closing tag => pop the tag from the stack
            else if (!st.empty()) {
                if (st.top()->tagName == temp2.substr(1))
                    st.pop();
            }
        }
    }
    myFile.close();
}