#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Function to verify the validity of XML tags
bool verifyXML(const string& xmlContent) {
    stack<string> tagStack; // Stack to store the opened tags
    string tag;
    bool insideTag = false;

    for (size_t i = 0; i < xmlContent.length(); ++i) {
        if (xmlContent[i] == '<') {
            insideTag = true;
            tag.clear(); // Clear the tag variable before storing a new tag
        } else if (xmlContent[i] == '>') {
            insideTag = false;
            if (!tag.empty()) {
                if (tag[0] == '/') { // If it's a closing tag
                    tag = tag.substr(1); // Remove the "/" at the beginning of the tag
                    if (tagStack.empty() || tagStack.top() != tag) {
                        cout << "Error: Closing tag </" << tag << "> doesn't match any opening tag!" << endl;
                        return false; // Return false if there's a mismatch
                    }
                    tagStack.pop(); // Remove the matching opening tag from the stack
                } else { // If it's an opening tag
                    tagStack.push(tag); // Add the opening tag to the stack
                }
            }
        } else if (insideTag) {
            tag += xmlContent[i]; // Append characters to the tag while inside the tag
        }
    }

    // If the stack is not empty, it means there are unclosed tags
    if (!tagStack.empty()) {
        cout << "Error: Opening tag <" << tagStack.top() << "> has no matching closing tag!" << endl;
        return false; // Return false if there are unclosed tags
    }

    return true; // If no errors, return true indicating the XML is valid
}

int main() {
    // Sample XML content for testing
    string xmlContent = "<root><tag1><tag2></tag2></tag1></root>";

    if (verifyXML(xmlContent)) {
        cout << "The XML is valid!" << endl; // Print if the XML is valid
    }

    return 0;
}
