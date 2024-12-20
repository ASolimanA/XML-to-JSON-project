#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <vector>
#include <queue>

class User {
private:
	int id;
	std::string name;
	std::vector<std::string> topics;
	std::vector<int> followers;
public:
	User(int id);
	friend class Graph;
};

class Graph {
private:
	std::vector<User*> vertices;
	std::vector<bool> marked;
	std::vector<std::vector<int>> edges;
public:
	~Graph();
	bool isEmpty();
	void print();
	int vertexIndex(int id);
	void addVertex(int id);
	void insertEdge(int fromVertex, int toVertex);
	void markvertex(int vertex);
	void clearMarks();
	bool isMarked(int vertex);
	void getNextVertices(int vertex, std::queue<int>& vertexQue);
};

#endif
