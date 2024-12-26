#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

class linkedListNode {
private:
    int id;
    linkedListNode* next;
public:
    linkedListNode(int id);
    friend class LinkedList;
    friend class Graph;
};

class LinkedList {
private:
    linkedListNode* head;
public:
    LinkedList();
    bool empty();
    int length();
    void push_front(int id);
    void pop_front();
    void clear();
    ~LinkedList();
    friend class Graph;
};

#endif