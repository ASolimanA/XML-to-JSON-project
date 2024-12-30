#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <vector>
#include <queue>
#include <stdexcept>

struct Post {
	std::string body;
	std::vector<std::string> topics;
};

class User {
public:
	int id;
	bool marked;
	std::string name;
	std::vector<Post*> posts;
	User();
	int getId();
	std::string getName();
	std::vector<Post*> getPosts();
	friend class Graph;
	friend class Tree;
};

class Graph {
public:
	std::vector<User*> vertices;
	std::vector<std::vector<int>> followers;
	void wordSearch(const std::string& word, std::vector<Post*>& posts, std::vector<Post*>& matchedPosts);
	~Graph();
	bool isEmpty();
	int  userIndex(int id);
	void addVertex(User* vertex);
	void markVertex(User* vertex);
	void clearMarks();
	User* getUser(int id);
    std::vector<Post*> postBodySearch(const std::string& word);
	void dotFile(const std::string& infile);
	void graphImage(const std::string& dotfile , const std::string& outfile);
    User* mostActive();
	std::vector<int> findMutualFollowers(const std::vector<int>& userIds);
	User* MostInfluencer();
	std::vector<User*> suggestFollowers(int id);
	std::vector<Post*> searchTopics(const std::string& topic);
	friend class Tree;

	
};

#endif
