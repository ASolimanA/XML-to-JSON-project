#include "graph.h"
#include <iostream>

#define NULL_EDGE 0

using namespace std;

User::User(int id) {
	this->id = id;
	marked = false;
}

Graph::~Graph() {
	for (auto user : vertices)
		delete user;
}

bool Graph::isEmpty() {
	return vertices.size() == 0;
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

void Graph::getNextVertices(User* vertex, queue<User*>& vertexQue) {
	for (int i = 0; i < vertex->followers.size(); i++) {
		vertexQue.push(vertex->followers[i]);
	}
}
