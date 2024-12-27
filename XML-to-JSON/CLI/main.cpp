#include <iostream>
#include <unistd.h>
#include "Tree.h"
#include "validation.h"
#include "graph.h"

using namespace std;

bool filePath_valid(const string& filePath) {
    fstream file(filePath);

    if(!file) return false;
    else{
        file.close();
        return true;
    }
}

string file_to_string(const string& filePath){
    ifstream file(filePath);

    ostringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

bool checkXML_valid(const string &inputFile){
    Validator v(inputFile);
    v.readFile();
    if(!v.validate()){
        cerr << "Invalid XML file" << endl;
        return false;
    }
    else cout << "Valid XML file" << endl;
    return true;
}

template <typename T>
ostream& operator <<(ostream& os, const vector<T>& vec) {
    for (const auto& i: vec)
        os << i << endl;
    return os;
}

int main(int argc, char *argv[])
{
    if(argc<3) {
        cout << "Invalid command\ncommand should be in the form cli_app.exe <process> -options" << endl;
        return 0;
    }
    //  -i inputFile or --version verify
    string inputFile, outputFile, wordToSearch, topicToSearch;
    int opt;
    optind = 2;
    while((opt = getopt(argc, argv, ":i:o:w:t:")) != -1) {
        switch (opt) {
            case 'i':
                inputFile = optarg;
                cout << "Input file: " << optarg << endl;
                break;
            case 'o':
                outputFile = optarg;
                cout << "Output file: " << optarg << endl;
                break;
            case 'w':
                wordToSearch = optarg;
                cout << "Word to search: " << optarg << endl;
                break;
            case 't':
                topicToSearch = optarg;
                cout << "Topic to search: " << optarg << endl;
                break;
            case ':':
            case '?':
                cout << "Unknown option -i, -o, -w and -t  are the only available options\n";
                cout << optarg << endl;
                return 0;
            default:
                cout << "unexpected error occurred" << endl;
        }
    }


    //check input file path
    if(!filePath_valid(inputFile)) {
        cerr << "Invalid input file path" << endl;
        return 0;
    }

    //check output file path
    if(!outputFile.empty() && filePath_valid(outputFile)==0){
        cerr << "Invalid output file path" << endl;
        return 0;
    }

    /////////////////
    if(strcmp(argv[1], "verify")==0){
        Validator v(inputFile);

        if(!v.validate()) {
            vector<array<int, 2>> vec = v.get_error_places();
            cout<<"I am here"<<endl;

            for (auto i: vec)
                cout << i[0] + 1 << " " << i[1] << endl;
        }

        else cout<<"Valid XML"<<endl;
        return 0;
    }
/////////////
    //check if it's a valid XML file before proceeding
    //if not valid then stop execution
    if(checkXML_valid(inputFile) == false)
        return 0;

    //convert the xml file into a string;
    string XML = file_to_string(inputFile);

    if(strcmp(argv[1], "format")==0){
        Tree t;
        t.Read_XML(XML);
        t.prettierFunction(outputFile);
    }
    else if(strcmp(argv[1], "json")==0){
        fstream file(outputFile, ios::out);
        Tree t;
        file <<  t.to_json(inputFile);
    }

//    if(strcmp(argv[1], "mini")==0){
//
//    }

//    if(strcmp(argv[1], "compress")==0){
//    }
//
//    if(strcmp(argv[1], "decompress")==0){}

    else if(strcmp(argv[1], "search")==0){
        Tree t;
        t.Read_XML(inputFile);
        Graph* g = t.convert_to_graph();
        vector<string> posts = g->wordSearch(wordToSearch);

        if(posts.empty()) cout << "The word you are searching for is not found in any of the posts" << endl;
        else cout << posts;

    }

return 0;
}