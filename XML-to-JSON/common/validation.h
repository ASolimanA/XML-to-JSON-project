#ifndef VALIDATION_H_
#define VALIDATION_H_

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <array>
#include <sstream>

using namespace std;

typedef enum {beginning ,leaf, aotag, actag} Phase;

class Validator {
    private:
    string filePath;
    // vector<char> error_type;     // For storing corresponding error types
    vector<pair<string, array<int,2>>> error_list; // For storing Missing tag and its predicted correct position
    vector<string> fileContent; 

    public:
    Validator();
    Validator(const string& filePath);
    bool validate();
    void fix();
    vector<pair<string, array<int,2>>> get_error_list();
    vector<array<int,2>> get_error_places();
    //vector<char> get_error_types();
    void print_errors();
    ~Validator();
    void setFileContent(const vector<string>& fileContent);
    vector<string> getFileContent();
    bool checkFile();
    string extractTagName(const string& tag);
    bool isOpeningTag(const string& tag);
    void readFile();
    void printFileContent() const;
    void writeFile(const string& outputFilePath);
};

#endif
