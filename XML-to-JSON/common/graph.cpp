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

/**
 * @brief Suggests potential new followers for a given user.
 *
 * This function inspects all of the user’s followers, then gathers 
 * the accounts followed by those followers. Any account not yet 
 * marked (indicating it's unknown to the user or not the user’s own 
 * account) is added to the returned suggestions list.
 *
 * @param id The user ID for whom to suggest new followers.
 * @return A vector of pointers to User objects that could be suggested as followers.
 * @throws invalid_argument If the user is not found.
 */
vector<User*> Graph::suggestFollowers(int id) {
    // Find the index of the user by ID
    int user_index = userIndex(id);
    if (user_index == -1) {
        throw invalid_argument("User not found"); // Throw if user doesn't exist
    }

    // Retrieve mapping of user IDs to their indices
    unordered_map<int, int> idToIndex = getIdToIndexMap();

    // Mark the current user to avoid suggesting themselves
    markVertex(vertices[user_index]);

    // Mark all the followers of the user
    for (int i = 0; i < followers[user_index].size(); i++) {
        int followerIndex = idToIndex[followers[user_index][i]];
        markVertex(vertices[followerIndex]);
    }

    // Prepare a container for suggested new followers
    vector<User*> suggestedFollowers;

    // For each follower, look at the users they follow
    for (int i = 0; i < followers[user_index].size(); i++) {
        int followerIndex = idToIndex[followers[user_index][i]];

        // Check each followee of this follower
        for (int j = 0; j < followers[followerIndex].size(); j++) {
            int suggestedIndex = idToIndex[followers[followerIndex][j]];

            // Add the new user if it's not yet marked
            if (!vertices[suggestedIndex]->marked) {
                suggestedFollowers.push_back(vertices[suggestedIndex]);
                markVertex(vertices[suggestedIndex]); // Mark so it's not added again
            }
        }
    }

    // Clear marks so future calls aren't affected
    clearMarks();

    return suggestedFollowers; // Return the final list of potential new followers
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

void Graph::mostActive(int& mostActiveId, string& mostActiveName, int& followerCount) {
    int maxFollowers = -1;

    mostActiveId = -1;     // if no active user is found
    mostActiveName = "";   // default username
    followerCount = 0;     // default number of followers

    for (int i = 0; i < vertices.size(); i++) {
        int currentFollowerCount = followers[i].size(); // Count the number of followers
        if (currentFollowerCount > maxFollowers) {
            maxFollowers = currentFollowerCount;
            mostActiveId = vertices[i]->id; // Set the most active user's ID
            mostActiveName = vertices[i]->name; // Set the most active user's name
            followerCount = currentFollowerCount; // Update the follower count for the most active user
        }
    }
}