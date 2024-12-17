#include "validation.h"
#include <string>
/*
   We need to check for the following:
    * Does the XML have 1 root (under a single tag).
    * Does every opening tag has its corresponding closing tag.
    * Does every closing tag has its corresponding opening tag.
    * Is leaves closed properly (when there is text after an opening tag).
*/

Validator::Validator(const string& filePath) {
        this->filePath = filePath;
        if(!filePath_valid()){
            throw invalid_argument("Error: No such file exists!\n");
        }
}

bool Validator::filePath_valid() {
    fstream file;
    file.open(filePath);
    if(!file) {
        file.close();
        return false;
    }
    file.close();
    return true;
}

bool Validator::validate (){
    stack<string> tagStack; // Stack to store the opened tags
    fstream file(filePath);
    string tag;
    Phase phase = beginning;
    array<int,2> last_tag_pos;
    string line;
    bool validation = true;
    bool insideTag = false;

    if (!filePath_valid()) return false;

    int line_no = 0;

    while(getline(file,line)){
        for (int i = 0; i < line.length(); ++i) {
            if (line[i] == '<') {
                insideTag = true;
                tag.clear(); // Clear the tag variable before storing a new tag
            } else if (line[i] == '>') {
                if (!tag.empty()) {
                    if (tag[0] == '/') { // If it's a closing tag
                        insideTag = false;
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
                                    validation = false;
                                    vec.push_back(last_tag_pos);
                                    error_type.push_back('o');
                                    last_tag_pos = {line_no, i};
                                    //cout << "Error: opening tag <" << temp.top() << "> doesn't match a closing tag!" << endl;
                                    temp.pop();
                                }
                            }
                            else { // If closing not found in the whole stack
                                validation = false;
                                vec.push_back(last_tag_pos);
                                error_type.push_back('o');
                                last_tag_pos = {line_no, i};
                                //cout << "Error: closing tag </" << tag << "> doesn't match an opening tag!" << endl;
                                while(!temp.empty()) {
                                    tagStack.push(temp.top());
                                    temp.pop();
                                }
                            }
                        }
                        else{
                            tagStack.pop(); // Remove the matching opening tag from the stack
                        }
                        phase = actag;
                    } else { // If it's an opening tag
                        if (phase == leaf) {
                            vec.push_back(last_tag_pos);
                            error_type.push_back('c');
                            //cout << "Error: No Closing tag for leaf tag <" << tagStack.top() << ">" << endl;
                            validation = false;
                            tagStack.pop();
                        }
                        if (phase != beginning && tagStack.empty()) {
                            vec.insert(vec.begin(), {0,0});
                            error_type.insert(error_type.begin(),'r');
                            //cout << "There is more than 1 root for this file" << endl;
                            validation = false;
                        }
                        tagStack.push(tag); // Add the opening tag to the stack
                        insideTag = false;
                        phase = aotag;
                        last_tag_pos = {line_no, i};
                    }
                }
            }
            else if (insideTag) {
                tag += line[i]; // Append characters to the tag while inside the tag
            }
            else if (phase == aotag && line[i] != ' ') {
                phase = leaf;
            }
        }
        line_no++;
    }

    while (!tagStack.empty()) {
        vec.push_back(last_tag_pos);
        error_type.push_back('c');
        //cout << "Error: Opening tag <" << tagStack.top() << "> has no matching closing tag!" << endl;
        validation = false;
        tagStack.pop();
    }

    file.close();
    return validation;
}

void Validator::write_at_line(const string& newText, int lineNumber) {
    filePath_valid();
    ifstream file(filePath);
    vector<string> lines_f;   // Store all lines of the file lines_f ==> lines for function
    
    string line;
    while (getline(file, line)) {
        lines_f.push_back(line);
    }
    file.close(); // Close the input file

    if (lineNumber <= lines_f.size()) {
        lines_f.insert(lines_f.begin() + lineNumber  , newText);//insert new line
    } else if (lineNumber == lines_f.size() ) {
        lines_f.push_back(newText);// If the line number is beyond the end, add it as a new line
    } else {
        std::cerr << "Error: Line number out of range.\n";
        return;
    }

    ofstream outputFile(filePath); // Open the file for writing
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing.\n";
        return;
    }

    for (int i = 0 ; i<lines_f.size();i++) {
        cout << "in printing the data" << endl;
        outputFile << lines_f[i] << "\n"; // Write each line back to the file
    }
    outputFile.close(); // Close the output file
}
void Validator::fix (){
    filePath_valid();
    fstream file(filePath);
    file.open(filePath);
    string line;
    file.close();
}
Validator::~Validator() {    
}
// For debugging purposes
vector<array<int,2>> Validator::get_error_places() {
    return vec;
}
vector<char> Validator::get_error_types() {
    return error_type;
}







// int main(){
//    Validator v("D:\\Faculty\\Fall 24\\Data Structure and Algorithms\\Project\\XML-to-JSON-project\\XML-to-JSON\\sample.xml");
//    v.validate();
//    v.write_at_line("hi hisham hatem", 10);

// }