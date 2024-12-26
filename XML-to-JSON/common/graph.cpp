#include "graph.h"
#include <iostream>

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