#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <vector>
#include <queue>

class User {
private:
	int id;
	bool marked;
	std::string name;
	std::vector<std::string> topics;
	std::vector<User*> followers;
public:
	User(int id);
	friend class Graph;
};

class Graph {
private:
	std::vector<User*> vertices;
public:
	~Graph();
	bool isEmpty();
	void addVertex(User* vertex);
	void markVertex(User* vertex);
	void clearMarks();
	void getNextVertices(User* vertex, std::queue<User*>& vertexQue);
};

#endif
