#include "arraylist.h"

ArrayList::ArrayList()
{
    size = 0;
}

void ArrayList::CreateFirstNode(Books val)
{
    size++;
    nodes = new Node[size];
    nodes[0].book=val;
    nodes[0].prev=nullptr;
    nodes[0].next=nullptr;
    head = tail = &nodes[0];
}

void ArrayList::RemoveOneNode()
{
    size--;
    Books nul;
    nodes[0].book = nul;
}

void ArrayList::PushBack(Books val)
{
    Node* arrDop = new Node[size];
    for(int i=0;i<size;i++)
    {
        arrDop[i]=nodes[i];
    }
    size++;
    nodes = new Node[size];
    for(int i=0;i<size-1;i++)
    {
        nodes[i]=arrDop[i];
    }
    nodes[size-1].book = val;
    nodes[size-1].prev = &nodes[size-2];
    nodes[size-2].next = &nodes[size-1];
    nodes[size-1].next = nullptr;
    tail = &nodes[size-1];
    delete[] arrDop;
}

void ArrayList::PushFront(Books val)
{
    Node* arrDop = new Node[size];
    for(int i=0;i<size;i++)
    {
        arrDop[i]=nodes[i];
    }
    size++;
    nodes = new Node[size];
    nodes[0].book = val;
    for(int i=1, j=0;i<size && j<size-1;i++,j++)
    {
        nodes[i] = arrDop[j];
    }
    nodes[0].prev = nullptr;
    nodes[0].next = &nodes[1];
    nodes[1].prev = &nodes[0];
    head = &nodes[0];
    delete[] arrDop;
}

void ArrayList::RemoveBack()
{
    Node* arrDop = new Node[size-1];
    for(int i=0;i<size-1;i++)
    {
        arrDop[i]=nodes[i];
    }
    size--;
    nodes = new Node[size];
    for(int i=0;i<size;i++)
    {
        nodes[i] = arrDop[i];
    }
    nodes[size-1].next = nullptr;
    tail = &nodes[size-1];
    delete[] arrDop;
}

void ArrayList::RemoveFront()
{
    Node* arrDop = new Node[size-1];
    for(int i=1, j=0;i<size && j<size-1;i++, j++)
    {
        arrDop[j]=nodes[i];
    }
    size--;
    nodes = new Node[size];
    for(int i=0;i<size;i++)
    {
        nodes[i] = arrDop[i];
    }
    nodes[0].prev = nullptr;
    head = &nodes[0];
    delete[] arrDop;
}

Books ArrayList::NodeSearchNumber(QString num)
{
    for(int i=0;i<size;i++)
    {
        if(nodes[i].book.GetNumber()==num)
        {
            return nodes[i].book;
        }
    }
    Books nul;
    return nul;
}

bool ArrayList::NodeSearchNameYear(QString name, QString date)
{
    bool is_here = false;
    for(int i=0;i<size;i++)
    {
        if(nodes[i].book.GetName()==name)
        {
            if(nodes[i].book.GetDate()==date)
            {
                is_here = true;
            }
        }
    }
    return is_here;
}

Books ArrayList::NodeSearchAuthor(QString author)
{
    Books nul;
    for(int i=0;i<size;i++)
    {
        if(nodes[i].book.GetAuthor()==author)
        {
            return nodes[i].book;
        }
    }
    return nul;
}

int ArrayList::RemoveNumber(QString num)
{
    int del = -1;
    for(int i=0;i<size;i++)
    {
        if(nodes[i].book.GetNumber()==num)
        {

            if(size==1)
            {
                return -4;
            }
            if(i==0)
            {
                return -2;
            }
            if(i==size-1)
            {
                return -3;
            }

            Node* arrDop = new Node[size-1];
            for(int i=0, j = 0;i<size-1 && j<size;i++, j++)
            {
                arrDop[i]=nodes[j];
                if(nodes[i].book.GetNumber()==num)
                {
                    del = i;
                    arrDop[i].next = &nodes[j+2];
                    nodes[j+2].prev = &arrDop[i];
                    i--;
                    continue;
                }
            }
            size--;
            nodes = new Node[size];
            for(int i=0;i<size;i++)
            {
                nodes[i] = arrDop[i];
            }
        }
    }
    return del;
}

ArrayList::~ArrayList()
{
    delete[] nodes;
}







