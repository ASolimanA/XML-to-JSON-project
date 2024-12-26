#include <iostream>
#include "LinkedList.h"

using namespace std;

linkedListNode::linkedListNode(int id) {
    this->id = id;
    this->next = NULL;
}

LinkedList::LinkedList() {
    head = NULL;
}
bool LinkedList::empty() {
    return head == NULL;
}
int LinkedList::length() {
    linkedListNode* current_Ptr = head;
    int count = 0;
    while (current_Ptr != NULL) {
        count++;
        current_Ptr = current_Ptr->next;
    }
    return count;
}
void LinkedList::push_front(int id) {
    linkedListNode* newNode = new linkedListNode(id);
    newNode->next = head;
    head = newNode;
}
void LinkedList::pop_front() {
    linkedListNode* front_node = head;
    if (front_node != NULL) {
        head = front_node->next;
        delete front_node;
    }
}

void LinkedList::clear() {
    while (!this->empty()) {
        pop_front();
    }
}

LinkedList::~LinkedList() {
    this->clear();
}