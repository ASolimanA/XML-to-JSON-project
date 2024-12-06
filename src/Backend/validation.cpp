#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <array>
using namespace std;

/*
   We need to check for the following:
    * Does the XML have 1 root (under a single tag).
    * Does every opening tag has its corresponding closing tag.
    * Does every closing tag has its corresponding opening tag.
    * Is leaves closed properly (when there is text after an opening tag).
*/
typedef enum {beginning, leaf, nleaf} Phase; 

class Validator
{
    private:
    string filePath;
    vector<array<int,2>> vec;     // For storing error positions (line, char position)
    vector<char> error_type; // For storing corresponding error types

    public:
    Validator(const string& filePath) {
        this->filePath = filePath;
    }

    bool filePath_vaild() {
        fstream file;
        file.open(filePath);
        if(!file) {
            file.close();
            return false;
        }
        file.close();
        return true;
    }

    bool validate (){
        stack<string> tagStack; // Stack to store the opened tags
        fstream file;
        string tag;
        char phase = 'b';
        string line;
        bool validation = true;

        if (!filePath_vaild()) return false;

        int line_no = 1;

        while(getline(file,line)){
            for (size_t i = 0; i < line.length(); ++i) {
                if (line[i] == '<') {
                    opening = false;   // declare a new tag
                    if (insideTag) {
                        cout << "Error: No closing bracket" << endl;
                        validation = false;
                        tag.clear();
                        continue;
                    }
                    insideTag = true;
                    tag.clear(); // Clear the tag variable before storing a new tag
                } else if (line[i] == '>') {
                    if(!insideTag) {
                        validation = false;
                        cout << "Error: No opening bracket for a closing bracket" << endl;
                        continue;
                    }
                    insideTag = false;
                    if (!tag.empty()) {
                        if (tag[0] == '/') { // If it's a closing tag
                            leaf = false;
                            tag = tag.substr(1); // Remove the "/" at the beginning of the tag
                            if (tagStack.empty() || tagStack.top() != tag) {
                                validation = false;
                                stack<string> temp;
                                while(!tagStack.empty() && tag != tagStack.top()) {
                                    temp.push(tagStack.top());
                                    tagStack.pop();
                                }
                                if(!tagStack.empty()) {
                                    tagStack.pop();
                                    while(!temp.empty()) {

                                        cout << "Error: opening tag <" << temp.top() << "> doesn't match a closing tag!" << endl;
                                        temp.pop();
                                    }
                                }
                                else { // If closing not found in the whole stack
                                    cout << "Error: closing tag </" << tag << "> doesn't match an opening tag!" << endl;
                                    while(!temp.empty()) {
                                        tagStack.push(temp.top());
                                        temp.pop();
                                    }
                                }
                            }
                            else{
                                tagStack.pop(); // Remove the matching opening tag from the stack
                            }
                        } else { // If it's an opening tag
                            if (leaf) {
                                cout << "Error: No Closing tag for <" << tagStack.top() << ">" << endl;
                                validation = false;
                                tagStack.pop();
                                leaf = false;
                            }
                            if (!beginning && tagStack.empty()) {
                                cout << "There is more than 1 root for this file" << endl;
                                validation = false;
                            }
                            tagStack.push(tag); // Add the opening tag to the stack
                            opening = true;
                            beginning = false;
                        }
                    }
                }
                else if (insideTag) {
                    tag += line[i]; // Append characters to the tag while inside the tag
                }
                else if (opening && line[i] != '<' && line[i] != ' ') {
                    leaf = true;
                }
            }
            if (insideTag) {
                cout << "Reached the end of the line without a closing bracket" << endl;
                validation = false;
                insideTag = false;
            }
            line_no++;
        }

        while (!tagStack.empty()) {
            cout << "Error: Opening tag <" << tagStack.top() << "> has no matching closing tag!" << endl;
            validation = false;
            tagStack.pop();
        }

        file.close();
        return validation;
    }
};



int main(){
    Validator v("sample.xml");
    // Test filePath="sample.xml"
    if (v.validate() == true ) cout << " Valid "; 
    else cout << " Not Valid " ;
}


// class Validator
// {
//     private:
//     ifstream file; // the XML file
    
//     vector<int[2]> vec;     // For storing error positions (line, char position)
//     vector<char> error_type; // For storing corresponding error types

//     public:
//     Validator(const string& filePath) {
//         file.open(filePath);
//         if(!file){
//             cerr << "Couldn't open the file";   // File not valid Error
//             delete this;
//         }
//     }
    
//     bool validate (){
//         stack<string> tagStack; // Stack to store the opened tags

//         string tag;
//         bool insideTag = false;
//         string line;
//         bool validation = true;
//         bool leaf= false;
//         bool opening = false;
//         bool beginning = true;
//         int line_no = 1;
//         while(getline(file,line)){
//             for (size_t i = 0; i < line.length(); ++i) {
//                 if (line[i] == '<') {
//                     opening = false;   // declare a new tag
//                     if (insideTag) {
//                         cout << "Error: No closing bracket" << endl;
//                         validation = false;
//                         tag.clear();
//                         continue;
//                     }
//                     insideTag = true;
//                     tag.clear(); // Clear the tag variable before storing a new tag
//                 } else if (line[i] == '>') {
//                     if(!insideTag) {
//                         validation = false;
//                         cout << "Error: No opening bracket for a closing bracket" << endl;
//                         continue;
//                     }
//                     insideTag = false;
//                     if (!tag.empty()) {
//                         if (tag[0] == '/') { // If it's a closing tag
//                             leaf = false;
//                             tag = tag.substr(1); // Remove the "/" at the beginning of the tag
//                             if (tagStack.empty() || tagStack.top() != tag) {
//                                 validation = false;
//                                 stack<string> temp;
//                                 while(!tagStack.empty() && tag != tagStack.top()) {
//                                     temp.push(tagStack.top());
//                                     tagStack.pop();
//                                 }
//                                 if(!tagStack.empty()) {
//                                     tagStack.pop();
//                                     while(!temp.empty()) {

//                                         cout << "Error: opening tag <" << temp.top() << "> doesn't match a closing tag!" << endl;
//                                         temp.pop();
//                                     }
//                                 }
//                                 else { // If closing not found in the whole stack
//                                     cout << "Error: closing tag </" << tag << "> doesn't match an opening tag!" << endl;
//                                     while(!temp.empty()) {
//                                         tagStack.push(temp.top());
//                                         temp.pop();
//                                     }
//                                 }
//                             }
//                             else{
//                                 tagStack.pop(); // Remove the matching opening tag from the stack
//                             }
//                         } else { // If it's an opening tag
//                             if (leaf) {
//                                 cout << "Error: No Closing tag for <" << tagStack.top() << ">" << endl;
//                                 validation = false;
//                                 tagStack.pop();
//                                 leaf = false;
//                             }
//                             if (!beginning && tagStack.empty()) {
//                                 cout << "There is more than 1 root for this file" << endl;
//                                 validation = false;
//                             }
//                             tagStack.push(tag); // Add the opening tag to the stack
//                             opening = true;
//                             beginning = false;
//                         }
//                     }
//                 }
//                 else if (insideTag) {
//                     tag += line[i]; // Append characters to the tag while inside the tag
//                 }
//                 else if (opening && line[i] != '<' && line[i] != ' ') {
//                     leaf = true;
//                 }
//             }
//             if (insideTag) {
//                 cout << "Reached the end of the line without a closing bracket" << endl;
//                 validation = false;
//                 insideTag = false;
//             }
//             line_no++;
//         }

//         while (!tagStack.empty()) {
//             cout << "Error: Opening tag <" << tagStack.top() << "> has no matching closing tag!" << endl;
//             validation = false;
//             tagStack.pop();
//         }

//         file.close();
//         return validation;
//     }
// };