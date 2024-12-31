#include "graph.h"
#include <iostream>
#include <regex>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <unordered_map>

using namespace std;

User::User() {
	marked = false;
}

int User::getId() {
    return id;
};

string User::getName() { 
    return name; 
};

vector<Post*> User::getPosts() { 
    return posts;
}

Graph::~Graph() {
	for (auto user : vertices)
		delete user;
}

User* Graph::getUser(int id) {
	for (int i = 0; i < vertices.size(); i++) {
		if (vertices[i]->id == id)
			return vertices[i];
	}
	return NULL;
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

void Graph::wordSearch(const std::string& word, std::vector<Post*>& posts, std::vector<Post*>& matchedPosts){
        for(Post* post: posts){
            string body = post->body;
    

            regex re("\\b" + word + "\\b");
            smatch match;

            if(regex_search(body, match, re))
                matchedPosts.push_back(post);

        }
}
std::vector<Post*> Graph::searchTopics(const std::string& topic) {
    std::vector<Post*> matchedPosts; // Vector to hold pointers to matching posts

    // Iterate over all users in the graph
    for (User* user : vertices) {
        // Iterate over all posts of the current user
        for (Post* post : user->posts) {
            // Check if the topic exists in the post's topics vector
            for (const std::string& postTopic : post->topics) {
                if (postTopic == topic) {
                    matchedPosts.push_back(post); // Add matching post to result
                    break; // Stop searching further topics for this post
                }
            }
        }
    }

    return matchedPosts; // Return vector of matching posts
}



vector<Post*> Graph::postBodySearch(const string& word){
    vector<Post*> matchedPosts;

    for(User* user: vertices)
        wordSearch(word, user->posts, matchedPosts);

    return matchedPosts;
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

    // Mark the current user to avoid suggesting themselves
    markVertex(vertices[user_index]);

    // Mark all the followers of the user
    for (int i = 0; i < followers[user_index].size(); i++) {
        int followerIndex = followers[user_index][i];
        markVertex(vertices[followerIndex]);
    }

    // Prepare a container for suggested new followers
    vector<User*> suggestedFollowers;

    // For each follower, look at the users they follow
    for (int i = 0; i < followers[user_index].size(); i++) {
        int followerIndex = followers[user_index][i];

        // Check each followee of this follower
        for (int j = 0; j < followers[followerIndex].size(); j++) {
            int suggestedIndex = followers[followerIndex][j];

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

void Graph::dotFile(const std::string& infile){
	std::ofstream file(infile);
	if (!std::filesystem::exists(infile)) {
        std::ofstream ofs(infile);
    }
	file << "digraph G {\n";
	for (int i = 0; i <vertices.size(); i++) {
		for(int j = 0; j < followers[i].size(); j++){
			string user = to_string(vertices[i]->id);
			string follower = to_string(vertices[followers[i][j]]->id);
			file <<"	" + follower + " -> " + user + "\n";
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
        std::filesystem::remove(dotfile);
    } else {
        std::cerr << "Error: Graphviz command failed.\n";
    }
}

User* Graph::mostActive() {
    int maxFollowers = -1;

    vector<int> followingCount(vertices.size(), 0);

    for (int i = 0; i < vertices.size(); i++) {
        for (int j = 0; j < followers[i].size(); j++) {
            followingCount[followers[i][j]]++;
        }
    }

    User* mostActiveUser = NULL;

    for (int i = 0; i < vertices.size(); i++) {
        int currentConnectCount = followers[i].size() + followingCount[i]; // Count the number of followers
        if (currentConnectCount > maxFollowers) {
            maxFollowers = currentConnectCount;
            mostActiveUser = vertices[i];
        }
    }
    return mostActiveUser;
}

vector<User*> Graph::findMutualFollowers(const vector<int>& userIds) {
    unordered_map<int, int> followerCount;

    // Populate the follower count map
    for (int userId : userIds) {
        int index = userIndex(userId);
        if (index == -1) {
            return {}; // Return empty vector if any user ID is not found
        }
        for (int followerIndex : followers[index]) {
            followerCount[followerIndex]++;
        }
    }

    // Collect mutual followers
    vector<User*> mutualFollowers;
    for (const auto& pair : followerCount) {
        if (pair.second == userIds.size()) {
            mutualFollowers.push_back(vertices[pair.first]);
        }
    }

    return mutualFollowers;
}
User* Graph:: MostInfluencer(){
    unordered_map <int/*user index*/,int/*number of followers*/> UserFollowers;

    User *mostInfluencer = NULL;
    int maxFollowers = 0;
    for(int i=0; i<vertices.size(); i++){
        if(followers[i].size() > maxFollowers){
            maxFollowers = followers[i].size();
            mostInfluencer = vertices[i];
        }
    }
    return mostInfluencer;
}