#include "graph.h"
#include <iostream>
#include <regex>
#include <fstream>
#include <cstdlib>
#include <string>
#include <filesystem>

#define NULL_EDGE 0

using namespace std;

User::User() {
	marked = false;
}

Graph::~Graph() {
	for (auto user : vertices)
		delete user;
}

bool Graph::isEmpty() {
	return vertices.size() == 0;
}

int Graph::userIndex(int id) {
	for (int i = 0; i < vertices.size(); i++)
		if (vertices[i]->id == id)
			return i;
	return -1;
}


void Graph::addVertex(User* vertex) {
	vertices.push_back(vertex);
}

void Graph::markVertex(User* vertex) {
	vertex->marked = true;
}

void Graph::clearMarks() {
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i]->marked = false;
	}
}

void Graph::getNextVertices(int id, queue<int>& vertexQue) {
	int index = userIndex(id);
	if (index == -1) {
		cout << "Invalid Vertex" << endl;
		return;
	}
	for (int i = 0; i < followers[index].size(); i++) {
		vertexQue.push(followers[index][i]);
	}
}

void Graph::wordSearch(const std::string& word, std::vector<Post*>& posts, std::vector<string>& matchedPosts){
        for(Post* post: posts){
            string body = post->body;

            regex re(word);
            smatch match;

            if(regex_search(body, match, re))
                matchedPosts.push_back(body);

        }
}

std::vector<std::string> Graph::wordSearch(const std::string& word){
    std::vector<std::string> matchedPosts;

    for(User* user: vertices)
        wordSearch(word, user->posts, matchedPosts);

    return matchedPosts;
}

void Graph::print() {
	for (int i = 0; i < vertices.size(); i++) {
		cout << "User: " << vertices[i]->name << " With id: " << vertices[i]->id << endl;
	}
	for (int i = 0; i < followers.size(); i++) {
		cout << vertices[i]->name << " Follows: ";
		for (int j = 0; j < followers[i].size(); j++) {
			cout << followers[i][j] << ", ";
		}
		cout << endl;
	}
}

unordered_map<int, int> Graph::getIdToIndexMap() {
	unordered_map<int, int> idToIndex;
	for (int i = 0; i < vertices.size(); i++) {
		idToIndex[vertices[i]->id] = i;
	}
	return idToIndex;
}

//@overload
// string to_string(int i){
// 	return vertices[i]->name;
// }

void Graph::dotFile(const std::string& infile){
	std::ofstream file(infile);
	if (!std::filesystem::exists(infile)) {
        std::ofstream ofs(infile);
    }
	file << "digraph G {\n";
	for (int i = 0; i <vertices.size(); i++) {
		for(int j = 0; j < followers[i].size(); j++){
			string user = to_string(vertices[i]->id);
			string follower = to_string(followers[i][j]);
			file <<"	" + user + " -> " + follower + "\n";
			cout << "in the make file.dot function"<<endl;
		}
	}
	file<< "}\n";
	file.close();
}

void Graph::graphImage(const std::string& dotfile , const std::string& outfile){
	// Command to generate a .jpg image using Graphviz
    std::string command = "dot.exe -Tjpg " + dotfile + " -o " + outfile;

    // Execute the command
    int result = system(command.c_str());
    if (result == 0) {
        std::cout << "Graph rendered successfully: " << outfile << "\n";
    } else {
        std::cerr << "Error: Graphviz command failed.\n";
    }
}