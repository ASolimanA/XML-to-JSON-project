#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
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

string inputFile, outputFile;
    if(argv[1] == "format"){
    }
    if(argv[1] == "json"){

    }
    if(argv[1] == "mini"){}
    if(argv[1] == "compress"){}
    if(argv[1] == "decompress"){}
    if(argv[1] == "xml_editor"){}
}