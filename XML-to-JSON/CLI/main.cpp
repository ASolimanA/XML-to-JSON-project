#include <iostream>
#include <getopt.h>
#include <cstring>
#include "Tree.h"
#include "validation.h"
#include "graph.h"
#include "compress-decompress.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RESET "\033[0m"
using namespace std;

vector<int> get_ids(const string& s){
    vector<int> ids;
    stringstream ss(s);
    string temp;
    while(getline(ss, temp, ',')){
        ids.push_back(stoi(temp));
    }
    return ids;
}

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

Graph *XML_to_graph(const string& XML){
    Tree t;
    t.Read_XML(XML);
    return t.convert_to_graph();
}

template <typename T>
ostream& operator <<(ostream& os, const vector<T>& vec) {
    for (const auto& i: vec)
        os << i << endl;
    return os;
}

ostream& operator <<(ostream& os, const Post* post) {
        os << GREEN << "Post topics: \n" << RESET << post->topics;
        os << BLUE << "Post body: " <<  RESET << post->body << endl;
    return os;
}

ostream& operator <<(ostream& os, User* user){
    os << "User Name: " << user->getName() << endl;
    os << "User ID: " << user->getId() << endl;
    return os;
}

int main(int argc, char *argv[])
{
    if(argc<3) {
        cout << "Invalid command\ncommand should be in the form cli_app.exe <process> -options" << endl;
        return 0;
    }

    string inputFilePath, outputFilePath, wordToSearch, topicToSearch;
    vector<int> ids;
    char fixFlag = 0;

    int opt;
    optind = 2;
    static struct option long_options[] = {
            {"ids", 1, nullptr, 'd'},
            {"id", 1, nullptr, 'd'},
            {0, 0, 0, 0}
    };

    int option_index = 0;
    while((opt = getopt_long_only(argc, argv, ":i:o:w:t:f", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'i':
                inputFilePath = optarg;
                cout << "Input file: " << optarg << endl;
                break;
            case 'o':
                outputFilePath = optarg;
                cout << "Output file: " << optarg << endl;
                break;
            case 'f':
                fixFlag = 1;
                break;
            case 'w':
                wordToSearch = optarg;
                cout << "Word to search: " << optarg << endl;
                break;
            case 't':
                topicToSearch = optarg;
                cout << "Topic to search: " << optarg << endl;
                break;
            case 'd':
                ids = get_ids(optarg);
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


    if(strcmp(argv[1], "verify")==0){
        Validator v(inputFilePath);
        v.readFile();

        if(!v.validate()) {
            vector<array<int, 2>> vec = v.get_error_places();

            cout << "Invalid XML" << endl;
            cout << "There are " << vec.size() << (vec.size() <= 1 ? " error" : " errors") << " in the XML file" << endl;
            v.print_errors();

            if(fixFlag){
                v.fix();
                v.writeFile(outputFilePath);
            }
        }
        else cout<<"Valid XML"<<endl;
        return 0;
    }

    //convert the xml file into a string;
    string XML = file_to_string(inputFilePath);

    if(strcmp(argv[1], "mini")==0){
        ofstream outputFile(outputFilePath);

        Tree t;
        t.Read_XML(XML);

        outputFile <<  minify(XML);
        outputFile.close();
    }

    if(strcmp(argv[1], "compress")==0){
        compress(XML, outputFilePath);
        return 0;
    }

    if(strcmp(argv[1], "decompress")==0){
        string decompressed = decompress(inputFilePath);

        ofstream outputFile(outputFilePath, ios::binary);
        outputFile << decompressed;
        outputFile.close();

        return 0;
    }

    //check if it's a valid XML file before proceeding
    //if not valid then stop execution
    if(checkXML_valid(inputFilePath) == false)
        return 0;

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
        t.Read_XML(XML);

        outputFile <<  t.to_json();
        outputFile.close();
    }



    else if(strcmp(argv[1], "draw")==0){
        Graph *g = XML_to_graph(XML);
        g->dotFile("graph.dot");
        g->graphImage("graph.dot", outputFilePath);
    }



    else if(strcmp(argv[1], "search")==0){
        Graph* g = XML_to_graph(XML);
        vector<Post*> posts;

        if(!wordToSearch.empty()) {
            posts = g->postBodySearch(wordToSearch);
        }
        else if(!topicToSearch.empty()){
            posts = g->searchTopics(topicToSearch);
        }

        if(posts.empty()) cout << "There are no posts with this search criteria\n" << endl;
        else cout << posts;
    }

    else if(strcmp(argv[1], "most_active")==0){
        Graph* g = XML_to_graph(XML);
        User* user = g->mostActive();

        if (user != nullptr) {
            cout << "The most active user:" << endl;
            cout << "Name: " << user->getName() << endl;
            cout << "ID: " << user->getId() << endl;
        } else {
            cout << "No active users found." << endl;
        }
    }

    else if(strcmp(argv[1], "most_influencer")==0)   {
        Graph *g = XML_to_graph(XML);
        User *user = g->MostInfluencer();

        if (user != nullptr) {
            cout << "The most influencing user:" << endl;
            cout << "Name:" <<  user->getName() << endl;
            cout << "ID:" <<  user->getId() << endl;
        }
        else{
            cout << "No influencing users found." << endl;
        }
    }

    else if(strcmp(argv[1], "suggest")==0){
        if(ids.empty()){
            cerr << "No user ID provided" << endl;
            return 0;
        }
        Graph *g = XML_to_graph(XML);
        vector<User*> users = g->suggestFollowers(ids[0]);

        if(users.empty()) cout << "No suggested followers found" << endl;
        else cout << "The suggested users are:\n" << users;
    }


    else if(strcmp(argv[1], "mutual")==0){
        if(ids.empty()){
            cerr << "No user ID provided" << endl;
            return 0;
        }

        Graph *g = XML_to_graph(XML);
        vector<User*> mutualFollowers = g->findMutualFollowers(ids);

        if(mutualFollowers.empty()) cout << "No mutual mutual followers found" << endl;
        else cout << "The mutual mutual followers between the users are:\n" << mutualFollowers;
    }

    return 0;
}
