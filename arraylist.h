#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include "books.h"

struct Node
{
    Books book;
    Node* next;
    Node* prev;
};

class ArrayList
{
private:
    Node* head;
    Node* tail;
    int size;
    Node* nodes;
public:
    ArrayList();
    ~ArrayList();
    void CreateFirstNode(Books val);
    void RemoveOneNode();
    void PushBack(Books val);
    void PushFront(Books val);
    void RemoveBack();
    void RemoveFront();
    int RemoveNumber(QString num);
    Books NodeSearchNumber(QString num);
    bool NodeSearchNameYear(QString name, QString date);
    Books NodeSearchAuthor(QString author);
};

#endif // ARRAYLIST_H
