#include "Tree.h"
#include "validation.h"
#include <iostream>
#include <unistd.h>
using namespace std;

bool filePath_valid(const string& filePath) {
    fstream file;
    file.open(filePath);
    if(!file) {
        file.close();
        return false;
    }
    file.close();
    return true;
}

int main(int argc, char *argv[])
{
    if(argc<3) {
        cout << "Invalid command\ncommand should be in the form cli_app.exe <process> -options" << endl;
        return 0;
    }
    //  -i inputFile or --version verify
    string inputFile, outputFile;
    int opt;
    optind = 2;
    while((opt = getopt(argc, argv, ":i:o:")) != -1) {
        switch (opt) {
            case 'i':
                inputFile = optarg;
                cout << "Input file: " << optarg << endl;
                break;
            case 'o':
                outputFile = optarg;
                cout << "Output file: " << optarg << endl;
                break;
            case ':':
            case '?':
                cout << "Unknown option -i and -o  are the only available options\n";
                cout << optarg << endl;
                return 0;
            default:
                cout << "unexpected error occurred" << endl;
        }
    }


    if(!filePath_valid(inputFile)) {
        cerr << "Invalid input file path" << endl;
        return 0;
    }

    if(strcmp(argv[1], "verify")==0){
        Validator v(inputFile);

        if(!v.validate()) {
            vector<array<int, 2>> vec = v.get_error_places();
            cout<<"I am here"<<endl;

            for (auto i: vec)
                cout << i[0] + 1 << " " << i[1] << endl;
        }

        else cout<<"Valid XML"<<endl;
    }
    if(strcmp(argv[1], "format")==0){
        Tree t;
        t.Read_XML(inputFile);
        t.prettierFunction(outputFile);
    }
    if(strcmp(argv[1], "json")==0){
        Validator v(inputFile);
        v.readFile();
        if(!v.validate()){
            cerr << "Invalid XML file" << endl;
            return 0;
        }
        else cout << "Valid XML file" << endl;
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
}