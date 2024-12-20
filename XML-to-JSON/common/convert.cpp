#include <iostream>
#include "Tree.h"
#include<string>

std::string Tree::to_json(Node* root, std::string tabs) {
    if (!root) return "{}"; // Base case: return empty JSON object for null nodes

    std::string json="";
    if(root == getRoot())json = "{\n";

    if(root->branches.empty()) return tabs + '"' +  root->tagName  + '"' + " : " + '"' + root->tagValue + '"' + "\n";
    else{
        json += tabs + '"' + root->tagName + '"' + ":[\n";
        tabs += '\t';
        unsigned long long numBranches = root->branches.size();
        for(int i=0; i < numBranches; i++) {
            json += tabs;
            json += "{\n";
            json += to_json(root->branches[i], tabs + "\t");
            json += tabs;
            if(i != numBranches-1) json += "},\n";
            else json += "}\n";
        }
        tabs = tabs.substr(0, tabs.size()-1);
        json += tabs + "]\n";
    }



    if(root == getRoot())json += "}\n";
    return json;
}
std::string Tree::to_json(std::string filePath) {
    Read_XML(filePath);
     return to_json(root, "\t");
}