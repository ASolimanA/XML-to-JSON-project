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
    vector<array<int,2>> vec;     // For storing error positions (line, char position)
    vector<char> error_type;     // For storing corresponding error types

    vector<string> fileContent; // new    
    vector<pair<string, int>> openings; // new
    vector<pair<string, int>> closings; // new

    public:
    Validator(const string& filePath);
    bool filePath_valid();
    bool validate ();
    void fix ();
    vector<array<int,2>> get_error_places();
    vector<char> get_error_types();
    void print_errors();
    ~Validator();
    //new
    void Validator::checkFile(const string& filePath);
    string Validator::extractTagName(const string& tag);
    bool Validator::isOpeningTag(const string& tag);
    void Validator::readFile(const string& filePath);
    void Validator::printFileContent() const;
    void Validator::writeFile(const string& outputFilePath);
};

#endif
