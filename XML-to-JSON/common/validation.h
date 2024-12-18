#ifndef VALIDATION_H_
#define VALIDATION_H_

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <array>

using namespace std;

typedef enum {beginning ,leaf, aotag, actag} Phase;

class Validator {
    private:
    string filePath;
    vector<array<int,2>> vec;     // For storing error positions (line, char position)
    vector<char> error_type;     // For storing corresponding error types
    public:
    Validator(const string& filePath);
    bool filePath_valid();
    bool validate ();
    void write_at_line(const string& newText, int lineNumber);
    void fix ();
    vector<array<int,2>> get_error_places();
    vector<char> get_error_types();
    ~Validator();
};

#endif
