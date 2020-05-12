#ifndef LINKEDLIST_HPP
#define	LINKEDLIST_HPP

#include <iostream>
#include "Node.hpp"

using namespace std;

/*....DO NOT EDIT BELOW....*/
template <class T>
class LinkedList {
private:
    Node<T>* head; 
    int length;  
public:

    LinkedList();
    LinkedList(const LinkedList<T>& ll);
    LinkedList<T>& operator=(const LinkedList<T>& ll);
    ~LinkedList();


    Node<T>* getHead() const;
    Node<T>* first() const;
    Node<T>* findPrev(const T& data) const;
    Node<T>* findNode(const T& data) const;
    void insertNode(Node<T>* prev, const T& data); 
    void deleteNode(Node<T>* prevNode);
    void clear();
    size_t getLength() const;
    void print() const;
    void swap(int index1, int index2);
};

template <class T>
void LinkedList<T>::print() const {
    const Node<T>* node = first();
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout << std::endl;
}

/*....DO NOT EDIT ABOVE....*/

/* TO-DO: method implementations below */


template <class T>
LinkedList<T>::LinkedList()
{
    head= new Node<T>;
    length=0;
}
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& ll)
{
    head=new Node<T>;
    *this=ll;
}
template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll)
{
    if (this != &ll){
        clear();
        const Node<T>* rhead=ll.first();
        Node<T>* lhead=getHead();
        while(rhead)
        {
            insertNode(lhead,rhead->getData());
            rhead=rhead->getNext();
            lhead=lhead->getNext();
        }
    }
    return *this;

}
template <class T>
LinkedList<T>::~LinkedList()
{
    clear();
    delete head;
}


template <class T>
Node<T>* LinkedList<T>::getHead() const
{
    return head;
}
template <class T>
Node<T>* LinkedList<T>::first() const
{
    return head->getNext();
}
template <class T>
Node<T>* LinkedList<T>::findPrev(const T& data) const
{
    Node<T>* temp=getHead();
    while(temp->getNext())
    {
        if(temp->getNext()->getData() == data) 
        {
            return temp;
        }
        temp=temp->getNext();        
    }
    return NULL;
}
template <class T>
Node<T>* LinkedList<T>::findNode(const T& data) const
{
    Node<T>* temp=findPrev(data);
    if(temp==NULL) return NULL;
    return temp->getNext();
}
template <class T>
void  LinkedList<T>::insertNode(Node<T>* prev, const T& data)
{
    if(prev)
    {
        Node<T>* newNode=new Node<T>(data);
        newNode->setNext(prev->getNext());
        prev->setNext(newNode);
    }
    length++;
}
template <class T>
void LinkedList<T>::deleteNode(Node<T>* prevNode)
{
    if(prevNode)
    {
        Node<T>* temp=prevNode->getNext();
        prevNode->setNext(temp->getNext());
        delete temp;
    }
    length--;
}
template <class T>
void LinkedList<T>::clear()
{
    Node<T>* temp=getHead();
    Node<T>* temp2;
    while(temp->getNext())
    {
        temp2=temp->getNext();
        temp->setNext(temp2->getNext());
        delete temp2;
    }
    length=0;

}
template <class T>
size_t LinkedList<T>::getLength() const
{
    return length;
}
template <class T>
void LinkedList<T>::swap(int index1, int index2)
{   
    Node<T>* p1Prev=getHead();
    Node<T>* p2Prev=getHead();
    Node<T>* p1;
    Node<T>* p2;
    Node<T>* p1Next;
    for(int i=0;i<index1;i++)
    {
        p1Prev=p1Prev->getNext();
    }
    for(int j=0;j<index2;j++)
    {
        p2Prev=p2Prev->getNext();
    }
    p1=p1Prev->getNext();
    p2=p2Prev->getNext();
    p1Next=p1->getNext();
    p1Prev->setNext(p2);
    p2Prev->setNext(p1);
    p1->setNext(p2->getNext());
    p2->setNext(p1Next);
}
/* end of your implementations*/
#endif	

