#include <iostream>
#include <unistd.h>
#include "Tree.h"
#include "validation.h"
#include "graph.h"
//#include "compress-decompress.cpp"

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
    //  -i inputFilePath or --version verify
    string inputFilePath, outputFilePath, wordToSearch, topicToSearch;
    int opt;
    optind = 2;
    while((opt = getopt(argc, argv, ":i:o:w:t:")) != -1) {
        switch (opt) {
            case 'i':
                inputFilePath = optarg;
                cout << "Input file: " << optarg << endl;
                break;
            case 'o':
                outputFilePath = optarg;
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
    if(!filePath_valid(inputFilePath)) {
        cerr << "Invalid input file path" << endl;
        return 0;
    }

    /////////////////  waiting to be changed
    if(strcmp(argv[1], "verify")==0){
        Validator v(inputFilePath);
        v.readFile();

        if(!v.validate()) {
            vector<array<int, 2>> vec = v.get_error_places();

            for (auto i: vec)
                cout << i[0] + 1 << " " << i[1] << endl;
        }

        else cout<<"Valid XML"<<endl;
        return 0;
    }
/////////////

    //check if it's a valid XML file before proceeding
    //if not valid then stop execution
    if(checkXML_valid(inputFilePath) == false)
        return 0;

    //convert the xml file into a string;
    string XML = file_to_string(inputFilePath);

    if(strcmp(argv[1], "format")==0){
        Tree t;
        t.Read_XML(XML);

        ofstream outputFile(outputFilePath);
        outputFile <<  t.prettierFunction();
        outputFile.close();
    }
    else if(strcmp(argv[1], "json")==0){
        ofstream outputFile(outputFilePath);
        Tree t;
        outputFile <<  t.to_json(inputFilePath);
        outputFile.close();
    }

//    if(strcmp(argv[1], "mini")==0){
//
//    }

//    if(strcmp(argv[1], "compress")==0){
//        ofstream outputFile(outputFilePath, std::ios::binary);
//        outputFile <<  compress(XML);
//        outputFile.close();
//    }
//
//    if(strcmp(argv[1], "decompress")==0){}

    else if(strcmp(argv[1], "search")==0){
        Tree t;
        t.Read_XML(XML);
        Graph* g = t.convert_to_graph();
        vector<string> posts = g->wordSearch(wordToSearch);

        if(posts.empty()) cout << "The word you are searching for is not found in any of the posts" << endl;
        else cout << posts;
    }
        
    else if(strcmp(argv[1], "most_active")==0){
        Tree t;
        t.Read_XML(XML);
        Graph* g = t.convert_to_graph();
               int mostActiveId;
           string mostActiveName;
           int followerCount;
        g->mostActive(mostActiveId, mostActiveName, followerCount);
    
    if (mostActiveId != -1) {
        cout << "The most active user:" << endl;
        cout << "ID: " << mostActiveId << endl;
        cout << "Name: " << mostActiveName << endl;
        cout << "Number of Followers: " << followerCount << endl;
    } else {
        cout << "No active users found." << endl;
    }
        
    }

       
    return 0;
}
