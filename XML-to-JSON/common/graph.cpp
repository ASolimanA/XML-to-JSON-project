#include "graph.h"
#include <iostream>

#define NULL_EDGE 0

using namespace std;

User::User(int id) {
	this->id = id;
}

Graph::~Graph() {
	for (auto user : vertices)
		delete user;
}

bool Graph::isEmpty() {
	return vertices.size() == 0;
}
void Graph::print() {
	for (int i = 0; i < edges.size(); i++) {
		for (int j = 0; j < edges[i].size(); j++) {
			cout << edges[i][j] << ' ';
		}
		cout << endl;
	}
}
int Graph::vertexIndex(int id) {
	for (int i = 0; i < vertices.size(); i++)
		if (vertices[i]->id == id)
			return i;
	return -1;
}
void Graph::addVertex(int id) {
	User* new_user = new User(id);
	vertices.push_back(new_user);
	marked.push_back(false);
	for (int i = 0; i < edges.size(); i++) {
		edges[i].push_back(NULL_EDGE);
	}
	edges.push_back(vector<int>(vertices.size(), NULL_EDGE));
}
void Graph::insertEdge(int fromVertex, int toVertex) {
	int row, col;
	row = vertexIndex(fromVertex);
	col = vertexIndex(toVertex);
	if (row == -1) {
		cout << "No vertex with value: " << fromVertex << endl;
		return;
	}
	if (col == -1) {
		cout << "No vertex with value: " << toVertex << endl;
		return;
	}
	edges[row][col] = 1;
}
void Graph::markvertex(int vertex) {
	int index = vertexIndex(vertex);
	if (index != -1)
		marked[index] = true;
}
void Graph::clearMarks() {
	for (int i = 0; i < marked.size(); i++) {
		marked[i] = false;
	}
}
bool Graph::isMarked(int vertex) {
	int index = vertexIndex(vertex);
	if (index != -1)
		return marked[index];
	else {
		cout << "Invalid Vertex" << endl;
		return false;
	}
}
void Graph::getNextVertices(int vertex, queue<int>& vertexQue) {
	int index = vertexIndex(vertex);
	if (index == -1) {
		cout << "Invalid Vertex" << endl;
		return;
	}
	for (int i = 0; i < edges[index].size(); i++) {
		if (edges[index][i] != NULL_EDGE) {
			vertexQue.push(vertices[i]->id);
		}
	}
}