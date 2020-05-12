#include <fstream>
#include <string>
#include <sstream>
#include "phonebook.hpp"

using namespace std;

void PhoneBook::insert(const string& name, const string& number){

    Contact person(name, number);

    // Note that we are inserting in sorted order to avoid
    // sorting when print is called.
    if (data.isEmpty()){
        data.push_front(person);
    }
    else{
        Node<Contact>* p = data.first();
        if (name < p->getElement().getName()){
            data.push_front(person);
        }
        else{
            while (p->getNext()){
                if (name > p->getNext()->getElement().getName()){
                    p = p->getNext();
                }
                else{
                    break;
                }
            }
            data.insert(person, p);
        }
    }
}

void PhoneBook::remove(const string& name){

    Node<Contact>* p = data.first();
    while (p){
        if (p->getElement().getName() == name){
            // Remove the first matching contact
            data.remove(p);
            break;
        }
        p = p->getNext();
    }
}

void PhoneBook::call(const string& name){

    Node<Contact>* p = data.first();
    while (p){
        if (p->getElement().getName() == name){
            
            Contact c = p->getElement();
            c.incCallCount();
            p->setElement(c);
            
            /*
            p->getElementPtr()->incCallCount();
            */
        }
        p = p->getNext();
    }
}

void PhoneBook::print() const{

    const Node<Contact>* p = data.first();
    cout << endl;
    while (p){
        cout << p->getElement().toString() << endl;
        p = p->getNext();
    }
}

void PhoneBook::save(const string& filename) const{

    ofstream outStream;
    outStream.open(filename.c_str());

    const Node<Contact>* p = data.first();
    while (p){
        outStream << p->getElement().toString() << endl;
        p = p->getNext();
    }
    outStream.close();
}

void PhoneBook::load(const string& filename){

    ifstream inStream;
    inStream.open(filename.c_str());

    if (!inStream.good()){
        cout << endl << "Unable to open the given file" << endl;
        return;
    }

    string name, number;
    int callCount;

    data.makeEmpty();
    while (inStream >> name >> number >> callCount){
        data.push_back(Contact(name, number, callCount));
    }
}
