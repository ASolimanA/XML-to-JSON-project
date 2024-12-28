#include <iostream>
#include "Tree.h"
#include <regex>
#include <fstream>
#include <stack>
#include <functional>
#include <sstream>

using namespace std;

string trim(const std::string& source) {
    std::string s(source);
    s.erase(0, s.find_first_not_of(" \n\r\t"));
    s.erase(s.find_last_not_of(" \n\r\t") + 1);
    return s;
}

Node::Node(string data) {
    tagName = data;
    tagValue = "";
}

Tree::Tree() {
    root = NULL;
}

Node *Tree::getRoot() {
    return root;
}

void Tree::preorder_traversal(Node* node) {
    if (node == NULL)
        return;
    cout << node->tagName << ' ' << node->tagValue << endl;
    for (int i = 0; i < node->branches.size(); i++)
        preorder_traversal(node->branches[i]);
}

void Tree::preorder_traversal() {
    preorder_traversal(root);
}

std::string Tree::fileToString(const std::string& filePath) {
    std::ifstream file(filePath); // Open the file
    if (!file) {
        throw std::ios_base::failure("Error opening file");
    }
    std::ostringstream buffer;
    buffer << file.rdbuf(); // Read the file's content into a stream
    return buffer.str();    // Convert the stream to a string
}

void Tree::Read_XML(const string& xml) {
    string temp1, temp2;
    // regex to find tag or a tag value
    regex regexSet("\\<([^>]+)\\>|[^<]+");
    smatch matches;
    stack<Node*> st;
    string::const_iterator it(xml.cbegin());
    while (regex_search(it, xml.cend(), matches, regexSet)) {
            // inc. iterator to index after the finded regex
            it = matches.suffix().first;
            // temp1 contains founded tag name with brackets "< and >"
            // if founded value is a tag's value: temp1 will contain the value and temp2 will be false
            temp1 = trim(matches[0]);
            // temp1 contains founded tag name without brackets
            temp2 = matches[1];
            // if the string is empty -> skip
            if (temp1.empty())
                continue;
            // if not a tag(value) => assign that value to the tag in the top of the stack
            else if(temp1[0] != '<'){
                st.top()->tagValue = temp1;
            }
            // if it's an open tag => push it to the stack
            else if (temp2[0] != '/') {
                Node* attr = new Node(matches[1]);
                if (root == NULL) {
                    root = attr;
                }
                // before pushing to the stack => assign that tag as a children to the tag in the stack's top
                else if (!st.empty()) {
                    st.top()->branches.push_back(attr);
                }
                st.push(attr);
            }
            // if it's a closing tag => pop the tag from the stack
            else if (!st.empty()) {
                if (st.top()->tagName == temp2.substr(1))
                    st.pop();
            }
    }
}

string Tree::prettierFunction() {
    ostringstream output;
//    if (!output.is_open()) {
//        cerr << "Error: Cannot open file for writing: " << outputPath << endl;
//        return;
//    }

    // Start recursive formatting from the root node and write formatted XML from the tree
    function<void(Node*, ostringstream&, int)> formatTree = [&](Node* node, ostringstream& output, int indentLevel) {
        if (node == nullptr)
            return;

        string indent(indentLevel * 4, ' ');

        // the opening tag
        output << indent << "<" << node->tagName << ">" << endl;

        // node's text value, if it exists
        if (!node->tagValue.empty()) {
            output << indent << "  " << node->tagValue << endl;
        }

        // Recursively process all child nodes
        for (Node* child : node->branches) {
            formatTree(child, output, indentLevel + 1);
        }

        // Write the closing tag
        output << indent << "</" << node->tagName << ">" << endl;
    };

    //  processing the tree from the root node
    formatTree(root, output, 0);

    return output.str();
}

std::string Tree::to_json(Node* rootNode, std::string tabs, bool arr, bool obj) {
    if (!rootNode) return "{}"; // Base case: return empty JSON object for null nodes

    std::string json;
    if(rootNode == getRoot())json = "{\n";

    if(rootNode->branches.empty()) return tabs + '"' + rootNode->tagName + '"' + " : " + '"' + rootNode->tagValue + '"';
    else{

        //start an array
        if(arr) {
            json += tabs + '"' + rootNode->tagName + '"' + ":[\n";

            //print all array values if they have the same key
            if(!rootNode->branches[0]->tagValue.empty()){
                tabs += "    ";
                for(int i=0; i < rootNode->branches.size(); i++) {
                    json += tabs + '"' + rootNode->branches[i]->tagValue + "\"";
                    if(i != rootNode->branches.size() - 1) json += ",";
                    json += "\n";
                }
                json += tabs.substr(0, tabs.size() - 4) + ']';
                return json;
            }
            obj = false;
        }
        if(obj && rootNode != getRoot()) json += tabs + "{\n";
        unsigned long long numBranches = rootNode->branches.size();

        for(int i=0; i < numBranches; i++) {

            json += to_json(rootNode->branches[i], tabs + "    ", !arr, !obj);
            if(i != numBranches-1) json += ",";
            json += "\n";
        }

        if(obj && rootNode != getRoot()) json += tabs + "}";

        if(arr) json += tabs.substr(0, tabs.size()-1) + "]";


    }

    if(rootNode == getRoot())json += "}\n";
    return json;
}

std::string Tree::to_json() {
    bool arr = true, obj = false;

    if(!root->branches.empty()) {
        string tagName = root->branches[0]->tagName;
        for (Node *child: root->branches) {
            if (child->tagName != tagName) {
                arr = false;
                obj = true;
                break;
            }
        }
    }
    else return "{\n    \""  + root->tagName + "\" : \""  + root->tagValue + "\"\n}";
    return to_json(root, arr ? "    " : "" , arr, obj);
}

Graph* Tree::convert_to_graph() {
    Graph* new_graph = new Graph();
    for (int i = 0; i < root->branches.size(); i++) {
        if (root->branches[i]->tagName == "user")
            new_graph->addVertex(convert_user(root->branches[i], new_graph));
    }
    return new_graph;
}

User* Tree::convert_user(Node* user_node, Graph* current_graph) {
    User* new_user = new User();
    for (int i = 0; i < user_node->branches.size(); i++) {
        if (user_node->branches[i]->tagName == "id")
            new_user->id = stoi(user_node->branches[i]->tagValue);
        else if (user_node->branches[i]->tagName == "name")
            new_user->name = user_node->branches[i]->tagValue;
        else if (user_node->branches[i]->tagName == "posts")
            add_posts(new_user, user_node->branches[i]);
        else if (user_node->branches[i]->tagName == "followers")
            add_followers(new_user, user_node->branches[i], current_graph);
    }
    return new_user;
}

void Tree::add_posts(User* current_user, Node* posts_node) {
    Node* post_node;
    for (int i = 0; i < posts_node->branches.size(); i++) {
        if (posts_node->branches[i]->tagName == "post") {
            post_node = posts_node->branches[i];
            Post* current_post = new Post();
            for (int j = 0; j < post_node->branches.size(); j++) {
                if (post_node->branches[j]->tagName == "body")
                    current_post->body = post_node->branches[i]->tagValue;
                if (post_node->branches[j]->tagName == "topics")
                    add_topics(current_post, post_node->branches[j]);
            }
            current_user->posts.push_back(current_post);
        }
    }
}

void Tree::add_topics(Post* current_post, Node* topics_node) {
    for (int i = 0; i < topics_node->branches.size(); i++) {
        if (topics_node->branches[i]->tagName == "topic")
            current_post->topics.push_back(topics_node->branches[i]->tagValue);
    }
}

void Tree::add_followers(User* current_user, Node* followers_node, Graph* current_graph) {
    vector<int> follows;
    for (int i = 0; i < followers_node->branches.size(); i++) {
        if (followers_node->branches[i]->tagName == "follower" &&
            followers_node->branches[i]->branches[0]->tagName == "id")
            follows.push_back(stoi(followers_node->branches[i]->branches[0]->tagValue));
    }
    current_graph->followers.push_back(follows);
}
