#include <iostream>
#include "Tree.h"
#include <regex>
#include <fstream>
#include <stack>
#include<string>
#include <functional>

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

void Tree::prettierFunction(const std::string& outputPath) {
    ofstream output(outputPath);
    if (!output.is_open()) {
        cerr << "Error: Cannot open file for writing: " << outputPath << endl;
        return;
    }

    // Start recursive formatting from the root node and write formatted XML from the tree
    function<void(Node*, ofstream&, int)> formatTree = [&](Node* node, ofstream& output, int indentLevel) {
        if (node == NULL)
            return;

        string indent(indentLevel * 4, ' ');

        // the opening tag
        output << indent << "<" << node->tagName << ">" << endl;

        // node's text value, if it exists
        if (!node->tagValue.empty()) {
            output << indent << "  " << node->tagValue << endl;
        }

        // Recursively process all child nodes
        for (Node* child : node->branches) {
            formatTree(child, output, indentLevel + 1);
        }

        // Write the closing tag
        output << indent << "</" << node->tagName << ">" << endl;
    };

    //  processing the tree from the root node
    formatTree(root, output, 0);

    output.close();
    cout << "Formatted XML saved to: " << outputPath << endl;
}

std::string Tree::to_json(Node* root, std::string tabs, bool arr, bool obj) {
    if (!root) return "{}"; // Base case: return empty JSON object for null nodes

    std::string json="";
    if(root == getRoot())json = "{\n";

    if(root->branches.empty()) return tabs + '"' +  root->tagName  + '"' + " : " + '"' + root->tagValue + '"';
    else{

        //start an array
        if(!arr) {
            json += tabs + '"' + root->tagName + '"' + ":[\n";
            tabs += '\t';

            //print all array values if they have the same key
            if(!root->branches[0]->tagValue.empty()){
                for(int i=0; i < root->branches.size(); i++) {
                    json += tabs + '"' + root->branches[i]->tagValue + "\"";
                    if(i!=root->branches.size()-1) json += ",";
                    json += "\n";
                }
                json += tabs.substr(0, tabs.size() - 1) + ']';
                return json;
            }
            obj = false;
        }
        if(obj) json += tabs + "{\n";
        unsigned long long numBranches = root->branches.size();

        for(int i=0; i < numBranches; i++) {

            json += to_json(root->branches[i], tabs + "\t", !arr, !obj);
            if(i != numBranches-1) json += ",";
            json += "\n";
        }

        if(obj) json += tabs + "}";

        if(!arr) json += tabs.substr(0, tabs.size()-1) + "]";


    }

    if(root == getRoot())json += "}\n";
    return json;
}

std::string Tree::to_json(std::string filePath) {
    Read_XML(filePath);
    return to_json(root, "\t", false, true);
}