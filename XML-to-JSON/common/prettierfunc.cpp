#include "Tree.h"
#include <fstream>
#include <iostream>
#include <string>
#include <functional>


using namespace std;

void Tree::prettierFunction(const string& outputPath) {
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

/*
int main() {
    Tree tree;
    tree.Read_XML("sample.xml");
    tree.prettierFunction("sample.xml");
}
 */
