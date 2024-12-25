#include "graph.h"
#include <set>

using namespace std;    

pair<User*,vector<User*>> Graph::suggestFollowersAll() {
    pair<User*,vector<User>> result;
    for (User vertex : vertices) {
        vector<int> followers = suggestFollowers(vertex.id);
        if (followers.size() > result.second.size()) {
            result.first = &vertex;
            result.second.clear();
            for (int follower : followers) {
                result.second.push_back(vertices[vertexIndex(follower)]);
            }
        }
    }
}

vector<int> Graph::suggestFollowers(int id) {
    set<int> result;
    int index = vertexIndex(id);
    if (index == -1) {
        cout << "No vertex with value: " << id << endl;
        return result;
    }
    queue<int> vertexQue;
    vertexQue.push(index);
    while (!vertexQue.empty()) {
        int currentVertex = vertexQue.front();
        vertexQue.pop();
        if (!isMarked(currentVertex)) {
            markvertex(currentVertex);
            getNextVertices(currentVertex, vertexQue);
            if (vertices[currentVertex]->id != id) {
                result.push_back(vertices[currentVertex]->id);
            }
        }
    }
    clearMarks();
    return vector<int>(result.begin(), result.end());
}