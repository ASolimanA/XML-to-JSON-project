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

    //if (!filePath_valid()) return false;

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

void Validator::fix (){
    //filePath_valid();
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

void Validator::print_errors() {
    vector<array<int, 2>> error_places = this->get_error_places();
    vector<char> error_types = this->get_error_types();

    cout << "Error Places:" << endl;
    for (const auto& place : error_places) {
        cout << "[" << place[0] << ", " << place[1] << "]" << endl;
    }

    cout << "Error Types:" << endl;
    for (const auto& type : error_types) {
        cout << type << endl;
    }
}
//new
void Validator::checkFile(const string& filePath) {
    ifstream file(filePath);
    if (!file) {
        cerr << "Error: File does not exist." << endl;
        exit(1);
    }
    file.close();
}

string Validator::extractTagName(const string& tag) {
    int start = tag.find('<') + 1;
    int end = tag.find('>');
    return (start != -1 && end != -1) ? tag.substr(start, end - start) : "";
}

// Helper function to determine if a tag is opening or closing
bool Validator::isOpeningTag(const string& tag) {
    return !tag.empty() && tag[0] != '/';
}
// Read the input file and store the content
void Validator::readFile(const string& filePath) {
    checkFile(filePath);
    ifstream file(filePath);
    string line;
    int lineIndex = 0;
    while (getline(file, line)) {
        fileContent.push_back(line);
        // Parse the line for tags
        int pos = 0;
        while ((pos = line.find('<', pos)) != -1) {
            int endPos = line.find('>', pos);
            if (endPos != -1) {
                string tag = line.substr(pos, endPos - pos + 1);
                string tagName = extractTagName(tag);
                if (isOpeningTag(tagName)) {
                    openings.emplace_back(tagName, lineIndex);
                } else {
                    closings.emplace_back(tagName.substr(1), lineIndex); // Remove '/' from closing tag
                }
                pos = endPos + 1;
            } else {
                break;
            }
        }
        ++lineIndex;
    }
    file.close();
}
void Validator::printFileContent() const {//for debugging
    for (const auto& line : fileContent) {
        cout << line << endl;
    }
}
void Validator::writeFile(const string& outputFilePath) {
        checkFile(outputFilePath);
        ofstream outFile(outputFilePath);
        if (!outFile) {
            cerr << "Error: Could not create or write to the file." << endl;
            exit(1);
        }

        for (const auto& line : fileContent) {
            outFile << line << endl;
        }

        outFile.close();
        cout << "File successfully written to " << outputFilePath << endl;
    }




// int main(){
//    Validator v("D:\\Faculty\\Fall 24\\Data Structure and Algorithms\\Project\\XML-to-JSON-project\\XML-to-JSON\\sample.xml");
//    v.validate();
//    v.write_at_line("hi hisham hatem", 10);

// }