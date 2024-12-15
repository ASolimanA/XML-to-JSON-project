#include <iostream>
#include "Tree.h"
#include<string>

std::string Tree::to_json(Node* node) {
    if (!node) return "{}"; // Base case: return empty JSON object for null nodes

    std::string json = "{";

    // Add tagName
    json += "\"tagName\": \"" + node->tagName + "\"";

    // Add tagValue if it exists
    if (!node->tagValue.empty()) {
        json += ", \"tagValue\": \"" + node->tagValue + "\"";
    }

    // Add children
    if (!node->branches.empty()) {
        json += ", \"children\": [";
        for (size_t i = 0; i < node->branches.size(); ++i) {
            json += to_json(node->branches[i]); // Recursive call
            if (i < node->branches.size() - 1) {
                json += ", "; // Add comma between sibling JSON objects
            }
        }
        json += "]";
    }

    json += "}";

    return json;
}
std::string Tree::to_json(std::string filePath) {
    Read_XML(filePath);
     return to_json(root);
}