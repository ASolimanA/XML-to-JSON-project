#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <vector>
#include <queue>

struct Post {
	std::string body;
	std::vector<std::string> topics;
};

class User {
private:
	int id;
	bool marked;
	std::string name;
	std::vector<Post*> posts;
public:
	User();
	friend class Graph;
	friend class Tree;
};

class Graph {
private:
	std::vector<User*> vertices;
	std::vector<std::vector<int>> followers;
    void wordSearch(const std::string& word, std::vector<Post*>& posts, std::vector<std::string> &matchedPosts);
public:
	~Graph();
	bool isEmpty();
	int userIndex(int id);
	void addVertex(User* vertex);
	void markVertex(User* vertex);
	void clearMarks();
	void getNextVertices(int id, std::queue<int>& vertexQue);
    std::vector<std::string> wordSearch(const std::string& word);
	void print();
	friend class Tree;
};

#endif
