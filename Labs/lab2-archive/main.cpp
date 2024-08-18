#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include "ArgumentManager.h"

using namespace std;

struct node {
    string data;
    node *next;
    node() {
        data = "";
        next = nullptr;
    }
    node(string x) {
        data = x;
        next = nullptr;
    }
    node(string x, node *n) {
        data = x;
        next = n;
    }
};

class linkedList {
private:
    node *head;
public:
    linkedList() { head = nullptr;}
    node* getHead() { return head;}
    int getSize(node*);
    void insertAtHead(node*);
    void insertAtPos(node*, int);
    void insertAtTail(node*);
    void removeAtHead();
    void removeAtPos(int);
    void removeAtTail();
    //void print(node*); // for debugging
    string printHead();
    string printAtPos(int);
    string printTail();
};
int linkedList::getSize(node* head) {
    if(head == nullptr) {
        return 0;
    }
    return getSize(head->next)+1;
}

void linkedList::insertAtHead(node *n) {
    if(head == nullptr) {
        head = n;
        head->next = nullptr;
    }
    else {
        n->next = head;
        head = n;
    }
}

void linkedList::insertAtPos(node* n, int pos) {
    node *current = head;
    node *previous = nullptr;

    for(int i = 0; i<pos; i++) {
        previous = current;
        current = current->next;
    }

    previous->next = n;
    n->next = current;
}

void linkedList::insertAtTail(node* n) {
    node *current = head;
    
    while(current->next != nullptr) {
        current = current->next;
    }
    current->next = n;
}

void linkedList::removeAtHead() {
    node* deleteNode = head;
    head = head->next;
    delete deleteNode;
}

void linkedList::removeAtPos(int pos) {
    node *current = head;
    node *previous = nullptr;

    for(int i = 0; i<pos; i++) {
        previous = current;
        current = current->next;
    }

    previous->next = current->next;
    delete current;
}

void linkedList::removeAtTail() {
    node *current = head;
    node *previous = nullptr;

    while(current->next != nullptr) {
        previous = current;
        current = current->next;
    }

    previous->next = nullptr;
    delete current;
}

/*void linkedList::print(node *current) {
    if(current == nullptr) {
        return;
    }
    
    cout << current->data << endl;
    print(current->next);
}*/

string linkedList::printHead() {
    return (head->data);
}

string linkedList::printAtPos(int pos) {
    node *current = head;
    
    for(int i = 0; i<pos; i++) {
        current = current->next;
    }

    return (current->data);
}

string linkedList::printTail() {
    node *current = head;
    
    while(current->next != nullptr) {
        current = current->next;
    }

    return (current->data);
}

int main(int argc, char *argv[]) {

    ArgumentManager am(argc, argv);
    string input = am.get("input");
    string output = am.get("output");
    ifstream ifs(input);
    ofstream ofs(output);

    // ifstream ifs("input3.txt");
    // ofstream ofs("output.txt");
    string inputLine, temp;
    int index;
    linkedList list;

    if(!ifs.is_open()) {
        cout << "Could not open file\n";
    }
    
    while(getline(ifs, inputLine)) {
        //cout << inputLine << endl;
        //cout << list.getSize(list.getHead()) << endl;
        inputLine.erase(remove(inputLine.begin(), inputLine.end(), '\n'), inputLine.end());
        inputLine.erase(remove(inputLine.begin(), inputLine.end(), '\r'), inputLine.end());
        
        if(inputLine.find("Insert") == 0) { // insert operator
            if(inputLine.find("Head") == 7) { // indicates we want to insert at the head
                temp = inputLine.substr(12);
                node *n = new node(temp, list.getHead());
                list.insertAtHead(n);
            }
            else if(inputLine[7] == '0') { // indicates we want to insert at the head (via index 0)
                temp = inputLine.substr(9);
                node *n = new node(temp, list.getHead());
                list.insertAtHead(n);
            }
            else if(inputLine.find("Tail") == 7) { // indicates we want to insert at the tail
                temp = inputLine.substr(12);
                node *n = new node(temp);
                list.insertAtTail(n);
            }
            else if(inputLine[7] != '0') { // indicates we want to add at an index
                if((inputLine[7]-'0' < list.getSize(list.getHead()))) {
                    index = inputLine[7] - '0';
                    temp = inputLine.substr(9);
                    node *n = new node(temp);
                    list.insertAtPos(n, index);
                }
            }
        }

        if(inputLine.find("Remove") == 0) { // remove operator
            if(inputLine.find("Head") == 7 || inputLine[7] == '0') { // indicates we want to remove the head
                list.removeAtHead();
            }
            else if(inputLine.find("Tail") == 7) { // indicates we want to remove the tail
                list.removeAtTail();
            }
            else if(inputLine[7] != '0') { // indicates we want to remove at a pos ***index is always size-1***
                index = inputLine[7]-'0';
                if(index == list.getSize(list.getHead())-1) {
                    list.removeAtTail();
                }
                else if(index < list.getSize(list.getHead())-1) {
                    list.removeAtPos(index);
                }
                else if(index > list.getSize(list.getHead())-1) {
                    continue;
                }
            }

        }

        if(inputLine.find("Print") == 0) { // print operator
            if(inputLine.find("Head") != string::npos || inputLine[7] == '0') { // indicates we want to print the head
                ofs << list.printHead() << endl;
            }
            else if(inputLine.find("Tail") != string::npos) { // indicates we want to print the tail
                ofs << list.printTail() << endl;
            }
            else if(inputLine[7] != '0') {
                index = inputLine[7]-'0';
                if(index == list.getSize(list.getHead())-1) { 
                    ofs << list.printTail() << endl;
                }
                else if(index < list.getSize(list.getHead())-1) {
                    ofs << list.printAtPos(index) << endl;
                }
                else if(index > list.getSize(list.getHead())-1) {
                    continue;
                }
            }
            
        }
    }

    ifs.close();
    ofs.close();

    return 0;
}