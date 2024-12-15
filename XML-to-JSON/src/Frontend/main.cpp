////#include "mainwindow.h"
//
////#include <QApplication>
#include "../Backend/Tree.h"
#include "../Backend/validation.cpp"
#include "../Backend/prettierfunc.cpp"
#include <iostream>
#include <unistd.h>

using namespace std;

bool filePath_vaild(string filePath) {
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
//    if(argv[0]!= "XML-to-JSON.exe"){
//        cout<<"Invalid command"<<endl;
//        return 0;
//    }

    string inputFile, outputFile;
    while(char opt = getopt(argc, argv, "i:o:")) {
        switch (opt) {
            case 'i':
                inputFile = optarg;
                cout << "Input file: " << optarg << endl;
                break;
            case 'o':
                outputFile = optarg;
                cout << "Output file: " << optarg << endl;
                break;
            default:
                cout << "Invalid command" << endl;
                return 0;
        }
    }

    if(!filePath_vaild(inputFile)) {
        cerr << "Invalid file path" << endl;
        return 0;
    }
    if(!filePath_vaild(outputFile)) {
        cerr << "Invalid file path" << endl;
        return 0;
    }

    if(strcmp(argv[1], "verify")==0){

        Validator v(inputFile);
        if(!v.validate()) {
            vector<array<int, 2>> vec = v.getVec();
            for (auto i: vec) {
                cout << i[0] + 1 << " " << i[1] << endl;
            }
        }
        else cout<<"Valid XML"<<endl;
    }
    if(strcmp(argv[1], "format")==0){
        prettierfunction("../sample.xml");
    }
    if(strcmp(argv[1], "json")==0){
        Validator v(inputFile);
        if(!v.validate()){
            cerr << "Invalid XML file" << endl;
            return 0;
        }
        fstream file(outputFile, ios::out);
        Tree t;
        file << t.to_json(inputFile);
    }

//    if(strcmp(argv[1], "mini")==0){
//
//    }

//    if(strcmp(argv[1], "compress")==0){
//    }
//
//    if(strcmp(argv[1], "decompress")==0){}
////    QApplication a(argc, argv);
////    MainWindow w;
////    w.show();
////    return a.exec();
}
